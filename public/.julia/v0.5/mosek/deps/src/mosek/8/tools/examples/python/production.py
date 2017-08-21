##
#  Copyright : Copyright (c) MOSEK ApS, Denmark. All rights reserved.
#
#  File :      production.py
#
#  Purpose :   To demonstrates how to solve small linear
#              optimization problem using the MOSEK Python API.
##
import sys
import mosek

# Since the actual value of Infinity is ignores, we define it solely
# for symbolic purposes:
inf = 0.0

# Define a stream printer to grab output from MOSEK
def streamprinter(text):
    sys.stdout.write(text)
    sys.stdout.flush()


# We might write everything directly as a script, but it looks nicer
# to create a function.
def main ():
    # Create a MOSEK environment
    with mosek.Env () as env:

      # Create a task
      with env.Task(0,0) as task:
        # Attach a printer to the task
        task.set_Stream (mosek.streamtype.log, streamprinter)
 
        # Bound keys for constraints
        bkc = [mosek.boundkey.up,
               mosek.boundkey.up,
               mosek.boundkey.up]
        # Bound values for constraints
        blc = [-inf, -inf, -inf]
        buc = [100000.0 , 50000.0, 60000.0]
    
        # Bound keys for variables
        bkx = [mosek.boundkey.lo,
               mosek.boundkey.lo,
               mosek.boundkey.lo]
        # Bound values for variables
        blx = [ 0.0,  0.0,  0.0]
        bux = [+inf, +inf, +inf]

        # Objective coefficients
        csub = [   0,   1,   2 ]
        cval = [ 1.5, 2.5, 3.0 ]

        # We input the A matrix column-wise
        # asub contains row indexes
        asub = [ 0, 1, 2,
                 0, 1, 2,
                 0, 1, 2]
        # acof contains coefficients
        acof = [ 2.0, 3.0, 2.0,
                 4.0, 2.0, 3.0,
                 3.0, 3.0, 2.0 ]
        # aptrb and aptre contains the offsets into asub and acof where
        # columns start and end respectively
        aptrb = [ 0, 3, 6 ]
        aptre = [ 3, 6, 9 ]
        
        numvar = len(bkx)
        numcon = len(bkc)
        
        # Append the constraints
        task.appendcons(numcon)
    
        # Append the variables.
        task.appendvars(numvar)
    
        # Input objective
        task.putcfix(0.0)
        task.putclist(csub,cval)

        # Put constraint bounds
        task.putconboundslice(0, numcon, bkc, blc, buc)

        # Put variable bounds
        task.putvarboundslice(0, numvar,bkx, blx, bux)
        
        # Input A non-zeros by columns
        for j in range(numvar):
            ptrb,ptre = aptrb[j],aptre[j]
            task.putacol(j,
                         asub[ptrb:ptre],
                         acof[ptrb:ptre])
                   
        # Input the objective sense (minimize/maximize)
        task.putobjsense(mosek.objsense.maximize)
    
    
        # Optimize the task
        task.optimize()

        # Output a solution
        xx = [0.]*numvar
        task.getsolutionslice(mosek.soltype.bas,
                              mosek.solitem.xx, 
                              0,numvar,          
                              xx)
        print ("xx =", xx)


        # Make a change to the A matrix 
        task.putaij(0, 0, 3.0)
        task.optimize()
        # Append a new varaible x_3 to the problem */
        task.appendvars(1)
    
        # Set bounds on new varaible 
        task.putbound(mosek.accmode.var,
                      task.getnumvar()-1,
                      mosek.boundkey.lo,
                      0,       
                      +inf)
    
        # Change objective 
        task.putcj(task.getnumvar()-1,1.0)

        # Put new values in the A matrix 
        acolsub =   [0,   2]
        acolval =   [4.0, 1.0]
    
        task.putacol(task.getnumvar()-1, # column index 
                     acolsub,
                     acolval)
        # Change optimizer to simplex free and reoptimize 
        task.putintparam(mosek.iparam.optimizer,mosek.optimizertype.free_simplex)
        task.optimize() 
        # Append a new constraint 
        task.appendcons(1)
    
        # Set bounds on new constraint 
        task.putconbound( task.getnumcon()-1, mosek.boundkey.up,-inf, 30000)
                  
        # Put new values in the A matrix 

        arowsub = [0,   1,   2,   3  ]
        arowval = [1.0, 2.0, 1.0, 1.0]
   
        task.putarow(task.getnumcon()-1, # row index 
                     arowsub,
                     arowval) 
  
        task.optimize()
 
# call the main function
try:
    main ()
except mosek.Exception as e:
    print ("ERROR: %s" % str(e.code))
    if msg is not None:
        print ("\t%s" % msg)
    sys.exit(1)
except:
    import traceback
    traceback.print_exc()
    sys.exit(1)
