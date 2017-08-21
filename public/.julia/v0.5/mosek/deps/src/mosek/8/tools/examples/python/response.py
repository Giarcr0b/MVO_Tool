##
#  Copyright : Copyright (c) MOSEK ApS, Denmark. All rights reserved.
#
#  File :      response.py
#
#  Purpose :   This examples demonstrates proper response handling.
# 
##
import mosek
import sys

def streamprinter(text):
    sys.stdout.write(text)
    sys.stdout.flush()

def main(args):
  if len(args) < 1:
    print ("No input file specified")
    return
  else:
    print ("Inputfile: %s" % args[0])

  try:
    with mosek.Env() as env:
      with env.Task(0,0) as task:
        task.set_Stream (mosek.streamtype.log, streamprinter)
      
        task.readdata(args[0])

        trmcode = task.optimize()
      
        solsta = task.getsolsta(mosek.soltype.itr)

        if solsta in [ mosek.solsta.optimal,
                       mosek.solsta.near_optimal ]:
            print ("An optimal basic solution is located.")
            task.solutionsummary(mosek.streamtype.log)
        elif solsta in [ mosek.solsta.dual_infeas_cer,
                         mosek.solsta.near_dual_infeas_cer ]:
            print ("Dual infeasibility certificate found.")
        elif solsta in [ mosek.solsta.prim_infeas_cerl,
                         mosek.solsta.near_prim_infeas_cer ]:
            print("Primal infeasibility certificate found.\n");
        elif solsta == mosek.solsta.sta_unknown:
            # The solutions status is unknown. The termination code 
            # indicating why the optimizer terminated prematurely. 
            print ("The solution status is unknown.")
            print ("Termination code: %s" % str(trmcode))
        else:
            print ("An unexpected solution status is obtained.")
    
  except mosek.MosekException as err:
    print ("Generic error:")
    print (err)

if __name__ == '__main__':
  import sys
  main(sys.argv[1:])
