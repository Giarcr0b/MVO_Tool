##
# Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
#
#  File:      breaksolver.py
#
#  Purpose: Show how to break a long-running task.
##
   
import sys
import mosek.fusion
from   mosek.fusion import *
import random
import threading
import time

def main():

    timeout = 5
    
    n = 200    # number of binary variables
    m = n // 5 # number of constraints
    p = n // 5 # Each constraint picks p variables and requires that exactly half of them are 1

    R = random.Random(1234)


    print("Build problem...")
    ##TAG:begin-model
    with Model('SolveBinary') as M:
        M.setLogHandler(sys.stdout)

        x = M.variable("x", n, Domain.binary())
        
        M.objective(ObjectiveSense.Minimize, Expr.sum(x))
        M.setLogHandler(sys.stdout)
        
        L = list(range(n))
        for i in range(m):
            R.shuffle(L)            
            M.constraint(Expr.sum(x.pick(L[:p])),Domain.equalsTo(p // 2))
    ##TAG:end-model
        print("Start thread...")
        ##TAG:begin-create-thread
        T = threading.Thread(target = M.solve)
        ##TAG:end-create-thread
        T0 = time.time()

        try:
            T.start() # optimization now running in background

            ##TAG:begin-check-condition
            # Loop until we get a solution or you run out of patience and press Ctrl-C
            while True:
                if not T.isAlive():
                    print("Solver terminated before anything happened!")
                    break
                elif time.time()-T0 > timeout:
                    print("Solver terminated due to timeout!")
                    M.breakSolver()            
                    break
        except KeyboardInterrupt:
            print("Signalling the solver that it can give up now!")
            M.breakSolver()            
            ##TAG:end-check-condition
            ##TAG:begin-check-return
        finally:
            try: 
                T.join() # wait for the solver to return
            except: 
                pass
            ##TAG:end-check-return
if __name__ == '__main__':
  main()
