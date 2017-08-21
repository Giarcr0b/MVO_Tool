//
// Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.                          
//                                                 
//  File:      breaksolver.cs                            
//                                                 
//  Purpose: Show how to break a long-running task.
//
//  Requires a parameter defining a timeout in seconds.
//

   
using System;
using System.Threading;
using mosek.fusion;
using System.Diagnostics;
                         
namespace mosek
{
  namespace fusion
  {
    namespace example
    {
      public class Breaker
      {
        Model M; 
        long timeout;
        bool stop; 
        
        public Breaker(Model _M,long _timeout) { M = _M;  timeout = _timeout; stop = false; }
        public void stopThread() { stop = true; }
        public void run()
        {
          //TAG:begin-check-condition
          Stopwatch w = new Stopwatch(); w.Start();
          while (! stop)
            {
              if (w.ElapsedMilliseconds > timeout*1000)
                {
                  Console.WriteLine("Solver terminated due to timeout!");
                  M.BreakSolver();
                  break;
                }
            }
          //TAG:end-check-condition
        }
      }

      public class breaksolver
      {
        private static void nshuffle(Random R, int[] a, int n)
        {
          for (int i = 0; i < n; ++i)
            {
              int idx = R.Next(i,a.Length);
              int tmp = a[i]; a[i] = a[idx]; a[idx] = tmp;
            }
        }

        public static void Main(string[] args)
        {
          long timeout = 5;

          int n = 80;    // number of binary variables
          int m = n / 5; // number of constraints
          int p = n / 5; // Each constraint picks p variables and requires that half of them are 1
          Random R = new Random(1234);
          //TAG:begin-model
          using (Model M = new Model("SolveBinary"))
            {
              M.SetLogHandler(System.Console.Out);

              //Variable x = M.Variable("x", n, Domain.InRange(0,1));
              Variable x = M.Variable("x", n, Domain.Binary());
              M.Objective(ObjectiveSense.Minimize, Expr.Sum(x));              
              //M.SetSolverParam("numThreads",1);

              int[] idxs  = new int[n]; for (int i = 0; i < n; ++i) idxs[i] = i;
              int[] cidxs = new int[p];

              for (var i = 0; i < m; ++i)
                {
                  nshuffle(R,idxs,p);
                  Array.Copy(idxs,cidxs,p);
                  M.Constraint(Expr.Sum(x.Pick(cidxs)),Domain.EqualsTo(p / 2));
                }
                //TAG:end-model

              var B = new Breaker(M,timeout);

              //TAG:begin-create-thread
              var T = new Thread(new ThreadStart(B.run));
              T.Start();
              //TAG:end-create-thread
              M.Solve();
              B.stopThread();
              T.Join();              

              Console.WriteLine("End.");
            }
        }
      }
    }
  }
}
