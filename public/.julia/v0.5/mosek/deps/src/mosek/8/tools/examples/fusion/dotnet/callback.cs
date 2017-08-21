//
//   Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
//
//   File:      callback.cs
//
//   Purpose:   To demonstrate how to use the progress 
//              callback. 
//
//              Use this script as follows:
//              callback psim
//              callback dsim
//              callback intpnt
//
//              The first argument tells which optimizer to use
//              i.e. psim is primal simplex, dsim is dual simplex
//              and intpnt is interior-point. 
//

using System;
using mosek.fusion;

namespace mosek
{
  namespace fusion
  {
    namespace example
    {
      /*TAG:begin-callback*/                      
      class myCallback : mosek.DataCallback
      {
        double maxtime;
        Model M;

        public myCallback( double maxtime_,
                           Model M_)
          {
            maxtime = maxtime_;
            M = M_;
          }
        
        public override int callback( callbackcode caller, 
                                      double[]     douinf,
                                      int[]        intinf,
                                      long[]       lintinf )
          {
            double opttime = 0.0;
            int itrn;
            double pobj, dobj, stime;
  /*TAG:begin-callback-switch*/             
            switch (caller)
            {
            case callbackcode.begin_intpnt:
              Console.WriteLine("Starting interior-point optimizer");
              break;
            case callbackcode.intpnt:
              itrn    = intinf[(int) iinfitem.intpnt_iter      ];
              pobj    = douinf[(int) dinfitem.intpnt_primal_obj];
              dobj    = douinf[(int) dinfitem.intpnt_dual_obj  ];
              stime   = douinf[(int) dinfitem.intpnt_time      ];
              opttime = douinf[(int) dinfitem.optimizer_time   ];
            
              Console.WriteLine("Iterations: {0,-3}",itrn);
              Console.WriteLine("  Elapsed: Time: {0,6:F2}({1:F2})",opttime,stime);
              Console.WriteLine("  Primal obj.: {0,-18:E6}  Dual obj.: {1,018:E6}e",pobj,dobj);
              break;
            case callbackcode.end_intpnt:
              Console.WriteLine("Interior-point optimizer finished.");
              break;
            case callbackcode.begin_primal_simplex:
              Console.WriteLine("Primal simplex optimizer started.");
              break;
            case callbackcode.update_primal_simplex:
              itrn    = intinf[(int) iinfitem.sim_primal_iter  ];
              pobj    = douinf[(int) dinfitem.sim_obj          ];
              stime   = douinf[(int) dinfitem.sim_time         ];
              opttime = douinf[(int) dinfitem.optimizer_time   ];
            
              Console.WriteLine("Iterations: {0,-3}}", itrn);
              Console.WriteLine("  Elapsed time: {0,6:F2}({1:F2})",opttime,stime);
              Console.WriteLine("  Obj.: {0,-18:E6}", pobj );
              break;
            case callbackcode.end_primal_simplex:
              Console.WriteLine("Primal simplex optimizer finished.");
              break;
            case callbackcode.begin_dual_simplex:
              Console.WriteLine("Dual simplex optimizer started.");
              break;
            case callbackcode.update_dual_simplex:
              itrn    = intinf[(int) iinfitem.sim_dual_iter    ];
              pobj    = douinf[(int) dinfitem.sim_obj          ];
              stime   = douinf[(int) dinfitem.sim_time         ];
              opttime = douinf[(int) dinfitem.optimizer_time   ];
              Console.WriteLine("Iterations: {0,-3}}", itrn);
              Console.WriteLine("  Elapsed time: {0,6:F2}({1:F2})",opttime,stime);
              Console.WriteLine("  Obj.: {0,-18:E6}", pobj );
              break;
            case callbackcode.end_dual_simplex:
              Console.WriteLine("Dual simplex optimizer finished.");
              break;
            case callbackcode.begin_bi:
              Console.WriteLine("Basis identification started.");
              break;
            case  callbackcode.end_bi:
              Console.WriteLine("Basis identification finished.");
              break;
            default:
              break;
            }
  /*TAG:end-callback-switch*/ 
            if (opttime >= maxtime)
            {
              Console.WriteLine("MOSEK is spending too much time. Terminate it.");
              M.BreakSolver();
            }
            return 0;
          }
      }

  /*TAG:end-callback*/                      

      public class callback
      {
        public static void Main(string[] args)
          {
            
            string slvr     = "intpnt";
            
            if (args.Length < 1)
            {
              Console.WriteLine("Usage: callback ( psim | dsim | intpnt )");
            }

            if (args.Length >= 1) slvr = args[0];

            double[][] A =
              { new double[] { 3.0, 2.0, 0.0, 1.0 },
                new double[] { 2.0, 3.0, 1.0, 1.0 },
                new double[] { 0.0, 0.0, 3.0, 2.0 } };
            double[] c = { 3.0, 5.0, 1.0, 1.0  };

            double maxtime = 0.01;
            
            Model M = new Model("callback");
            
            Variable x = M.Variable("x", 3, Domain.GreaterThan(0.0));
            Variable y = M.Variable("y", 1, Domain.InRange(0.0, 10.0));
            Variable z = Var.Vstack(x,y);
            
            M.Constraint("c1", Expr.Dot(A[0], z), Domain.EqualsTo(30.0));
            M.Constraint("c2", Expr.Dot(A[1], z), Domain.GreaterThan(15.0));
            M.Constraint("c3", Expr.Dot(A[2], z), Domain.LessThan(25.0));
            
            M.Objective("obj", ObjectiveSense.Maximize, Expr.Dot(c, z));
            
                     
            if( slvr == "psim") 
              M.SetSolverParam("optimizer", "primal_simplex");
            else if( slvr == "dsim")
              M.SetSolverParam("optimizer", "dual_simplex");
            else if( slvr == "intpnt")
              M.SetSolverParam("optimizer", "intpnt");

            /*TAG:begin-callback-handler*/                            
            M.SetCallbackHandler( new myCallback(maxtime, M) );
            /*TAG:end-callback-handler*/                
            M.SetSolverParam("log", 0);
            
            M.Solve();
            
          }
      }
    }
  }
}
