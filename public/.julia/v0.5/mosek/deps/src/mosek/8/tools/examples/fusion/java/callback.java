package com.mosek.fusion.examples;
/* 
   Copyright : Copyright (c) MOSEK ApS, Denmark. All rights reserved.

   File :      callback.java

   Purpose :   To demonstrate how to use the progress 
               callback. 

               Use this script as follows:
               
               callback psim  
               callback dsim  
               callback intpnt

               The first argument tells which optimizer to use
               i.e. psim is primal simplex, dsim is dual simplex
               and intpnt is interior-point. 
*/

import mosek.*;
import mosek.fusion.*;
import java.util.Formatter;

public class callback
{
  /*TAG:begin-callback*/                
  private static DataCallback makeUserCallback(final double maxtime,
                                               final Model mod)
    {
      return new DataCallback() {
          public int callback(callbackcode caller,
                              double[]     douinf,
                              int[]        intinf,
                              long[]       lintinf)
          {

            double opttime = 0.0;
            int itrn;
            double pobj, dobj, stime;

            Formatter f = new Formatter(System.out);
            /*TAG:begin-callback-switch*/                
            switch (caller)
            {
              case begin_intpnt:
                  f.format("Starting interior-point optimizer\n");
              case intpnt:
                  itrn    = intinf[iinfitem.intpnt_iter.value      ];
                  pobj    = douinf[dinfitem.intpnt_primal_obj.value];
                  dobj    = douinf[dinfitem.intpnt_dual_obj.value  ];
                  stime   = douinf[dinfitem.intpnt_time.value      ];
                  opttime = douinf[dinfitem.optimizer_time.value   ];
            /*TAG:end-callback-switch*/                
                  f.format("Iterations: %-3d\n",itrn);
                  f.format("  Time: %6.2f(%.2f) ",opttime,stime);
                  f.format("  Primal obj.: %-18.6e  Dual obj.: %-18.6e\n",pobj,dobj);
              case end_intpnt:
                  f.format("Interior-point optimizer finished.\n");
              case begin_primal_simplex:
                  f.format("Primal simplex optimizer started.\n");
              case update_primal_simplex:
                  itrn    = intinf[iinfitem.sim_primal_iter.value  ];
                  pobj    = douinf[dinfitem.sim_obj.value          ];
                  stime   = douinf[dinfitem.sim_time.value         ];
                  opttime = douinf[dinfitem.optimizer_time.value   ];
            
                  f.format("Iterations: %-3d\n", itrn);
                  f.format("  Elapsed time: %6.2f(%.2f\n",opttime,stime);
                  f.format("  Obj.: %-18.6e", pobj );
              case end_primal_simplex:
                  f.format("Primal simplex optimizer finished.\n");
              case begin_dual_simplex:
                  f.format("Dual simplex optimizer started.\n");
              case update_dual_simplex:
                  itrn    = intinf[iinfitem.sim_dual_iter.value    ];
                  pobj    = douinf[dinfitem.sim_obj.value          ];
                  stime   = douinf[dinfitem.sim_time.value         ];
                  opttime = douinf[dinfitem.optimizer_time.value   ];
                  f.format("Iterations: %-3d\n", itrn);
                  f.format("  Elapsed time: %6.2f(%.2f)\n",opttime,stime);
                  f.format("  Obj.: %-18.6e\n", pobj);
              case end_dual_simplex:
                  f.format("Dual simplex optimizer finished.\n");
              case begin_bi:
                  f.format("Basis identification started.\n");
              case end_bi:
                  f.format("Basis identification finished.\n");
              default:
            }
            System.out.flush();
            if (opttime >= maxtime)
            {
              f.format("MOSEK is spending too much time. Terminate it.\n");
              System.out.flush();
              mod.breakSolver();
            }
            return 0;
          }

      };
    }
  /*TAG:end-callback*/                
    public static void main(String[] args)
    {
      String slvr     = "intpnt";
      if (args.length < 1)
      {
        System.out.println("Usage: ( psim | dsim | intpnt ) ");
      }

      if (args.length >= 1) slvr     = args[0];

        double[][] A = 
            { { 3.0, 2.0, 0.0, 1.0 },
              { 2.0, 3.0, 1.0, 1.0 },
              { 0.0, 0.0, 3.0, 2.0 } };
        double[] c = { 3.0, 5.0, 1.0, 1.0  };
        
        double maxtime = 0.01;

        try(Model M = new Model("callback"))
        {
          Variable x = M.variable("x", 3, Domain.greaterThan(0.0));
          Variable y = M.variable("y", 1, Domain.inRange(0.0, 10.0));
          Variable z = Var.vstack(x,y);
          M.constraint("c1", Expr.dot(A[0], z), Domain.equalsTo(30.0));
          M.constraint("c2", Expr.dot(A[1], z), Domain.greaterThan(15.0));
          M.constraint("c3", Expr.dot(A[2], z), Domain.lessThan(25.0));

          M.objective("obj", ObjectiveSense.Maximize, Expr.dot(c, z));

          if( slvr == "psim") 
            M.setSolverParam("optimizer", "primal_simplex");
          else if( slvr == "dsim")
            M.setSolverParam("optimizer", "dual_simplex");
          else if( slvr == "intpnt")
            M.setSolverParam("optimizer", "intpnt");

          /*TAG:begin-callback-handler*/                
          M.setCallbackHandler( makeUserCallback(maxtime,M) );
          /*TAG:end-callback-handler*/                
          M.setSolverParam("log", 0);

          M.solve();

          }
      catch (mosek.Exception e)
      {
        System.out.println ("An error/warning was encountered");
        System.out.println (e.toString());
        throw e;
      }
   }
}
