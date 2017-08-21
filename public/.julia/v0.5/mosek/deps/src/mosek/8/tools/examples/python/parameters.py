##
#  Copyright : Copyright (c) MOSEK ApS, Denmark. All rights reserved.
#
#  File :      parameters.py
#
#  Purpose :   Demonstrates a very simple example about how to get/set
#              parameters with MOSEK Python API
##
import mosek

# Create the mosek environment. 
with mosek.Env () as env:

  # Create the mosek environment. 
  with env.Task() as task:

    print ('Test MOSEK parameter get/set functions')

    param=  task.getintparam(mosek.iparam.log)
    print ('default value for parameter mosek.ipar.log= ',param)

    print (' setting to 1 using putintparam...')
    task.putintparam(mosek.iparam.log,1)


    try:
        print ('setting to -1 using putintparam...')
        task.putintparam(mosek.iparam.log,-1)
    except mosek.Error as e:
        print ('-1 rejected as not a valid value')

    print ('setting to 2 using putparam...')
    task.putparam('MSK_IPAR_LOG','2')

    print ('setting to 3 using putnaintparam...')
    task.putnaintparam('MSK_IPAR_LOG',3)

    print ('selecting the dual simplex algorithm...')
    task.putintparam(mosek.iparam.optimizer,mosek.optimizertype.dual_simplex)

