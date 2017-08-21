##
#   Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
#   File:      callback.py
#
#   Purpose:   To demonstrate how to use the progress 
#              callback. 
#
#
#              callback psim
#              callback dsim
#              callback intpnt
#              The first argument tells which optimizer to use
#              i.e. psim is primal simplex, dsim is dual simplex
#              and intpnt is interior-point. 
##
import sys
from mosek.fusion import *

def makeUserCallback(maxtime):
    def userCallback(caller,
                     douinf,
                     intinf,
                     lintinf):
        opttime = 0.0
        ##TAG:begin-callback-switch
        if caller == callbackcode.begin_intpnt:
            print ("Starting interior-point optimizer")
        elif caller == callbackcode.intpnt:
            itrn    = intinf[iinfitem.intpnt_iter      ]
            pobj    = douinf[dinfitem.intpnt_primal_obj]
            dobj    = douinf[dinfitem.intpnt_dual_obj  ]
            stime   = douinf[dinfitem.intpnt_time      ]
            opttime = douinf[dinfitem.optimizer_time   ]

            print ("Iterations: %-3d" % itrn)
            print ("  Elapsed time: %6.2f(%.2f) " % (opttime,stime))
            print ("  Primal obj.: %-18.6e  Dual obj.: %-18.6e" % (pobj,dobj))
        elif caller == callbackcode.end_intpnt:
            print ("Interior-point optimizer finished.")
        elif caller == callbackcode.begin_primal_simplex:
            print ("Primal simplex optimizer started.")
        elif caller == callbackcode.update_primal_simplex:
            itrn    = intinf[iinfitem.sim_primal_iter  ]
            pobj    = douinf[dinfitem.sim_obj          ]
            stime   = douinf[dinfitem.sim_time         ]
            opttime = douinf[dinfitem.optimizer_time   ]
            
            print ("Iterations: %-3d" % itrn)
            print ("  Elapsed time: %6.2f(%.2f)" % (opttime,stime))
            print ("  Obj.: %-18.6e" % pobj )
        elif caller == callbackcode.end_primal_simplex:
            print ("Primal simplex optimizer finished.")
        elif caller == callbackcode.begin_dual_simplex:
            print ("Dual simplex optimizer started.")
        elif caller == callbackcode.update_dual_simplex:
            itrn    = intinf[iinfitem.sim_dual_iter    ]
            pobj    = douinf[dinfitem.sim_obj          ]
            stime   = douinf[dinfitem.sim_time         ]
            opttime = douinf[dinfitem.optimizer_time   ]
            print ("Iterations: %-3d" % itrn)
            print ("  Elapsed time: %6.2f(%.2f)" % (opttime,stime))
            print ("  Obj.: %-18.6e" % pobj)
        elif caller == callbackcode.end_dual_simplex:
            print ("Dual simplex optimizer finished.")
        elif caller == callbackcode.begin_bi:
            print ("Basis identification started.")
        elif caller == callbackcode.end_bi:
            print ("Basis identification finished.")
        else:
            pass
        ##TAG:end-callback-switch
        if opttime >= maxtime:
            # mosek is spending too much time. Terminate it.
            return 1
      
        return 0

    return userCallback

def main(slvr):

    if slvr not in ['psim','dsim','intpnt']: return

    A = [ [ 3.0, 2.0, 0.0, 1.0 ],
          [ 2.0, 3.0, 1.0, 1.0 ],
          [ 0.0, 0.0, 3.0, 2.0 ] ]
    c = [ 3.0, 5.0, 1.0, 1.0  ]

    with Model() as M:
        x = M.variable("x", 3, Domain.greaterThan(0.0))
        y = M.variable("y", 1, Domain.inRange(0.0, 10.0))
        z = Var.vstack(x,y)
        M.constraint("c1", Expr.dot(A[0], z), Domain.equalsTo(30.0))
        M.constraint("c2", Expr.dot(A[1], z), Domain.greaterThan(15.0))
        M.constraint("c3", Expr.dot(A[2], z), Domain.lessThan(25.0))
        M.objective("obj", ObjectiveSense.Maximize, Expr.dot(c, z))
        
        if slvr == 'psim':
            M.setSolverParam('optimizer', 'primal_simplex')
        elif slvr == 'dsim':
            M.setSolverParam('optimizer', 'dual_simplex')
        else:
            M.setSolverParam('optimizer', 'intpnt')

        usrcallback =  makeUserCallback(maxtime = 3600) 
        M.setCallbackHandler( usrcallback )
        M.setSolverParam('log', 0)
        
        M.solve()




if __name__ == '__main__':
    main(sys.argv[1] if len(sys.argv)>1 else 'intpnt')
