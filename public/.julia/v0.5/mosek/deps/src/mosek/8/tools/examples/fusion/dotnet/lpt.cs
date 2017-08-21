//
// Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
//
//  File:      lpt.cs
//
// Purpose: demonstrates how to feed the MIP solver with some initial solution.
//

using System;
using System.Collections.Generic;

using mosek.fusion;


namespace mosek
{
  namespace fusion
  {
    namespace example
    {

        public class lpt
        {

            public static void Main(string [] args)
            {
              
              double lb = 1.0;
              int m = 4;
              int n= 15;
              int seed= 0;
              double ub = 5.0;
              
              double[] T= new double[n]; 

              Random gen = new Random(seed);
              for(int i=0;i<n;i++)
                T[i] = gen.NextDouble()*(ub-lb)+lb;

              Array.Sort<double>(T); 
      
              //TAG:begin-model
              Model M= new Model("Multi-processor scheduling");

              Variable x= M.Variable("x", new int[]{m, n}, Domain.Binary());

              Variable t= M.Variable("t",1, Domain.Unbounded());

              M.Constraint( Expr.Sum(x,0), Domain.EqualsTo(1.0));

              //TAG:begin-repeat
              M.Constraint( Expr.Sub( Var.Repeat(t,m), Expr.Mul(x,T)) , Domain.GreaterThan(0.0));
              //TAG:end-repeat

              M.Objective( ObjectiveSense.Minimize, t );
              //TAG:end-model

              //TAG:begin-lpt
              double [] init    = new double[n*m];
              double [] schedule= new double[m];
        
        
              for(int i=0;i<n;i++)
              {
                int next=0;
                for(int j=1;j<m;j++)
                  if(schedule[j]<schedule[next]) next=j;
          
                  schedule[next] += T[i];
                  init[next*n + i] = 1;
              }
              //TAG:end-lpt
      
              M.SetLogHandler(Console.Out);

              M.WriteTask("dump.opf");
                    
              M.SetSolverParam("mioTolRelGap", .01);
              M.Solve();

              try
              {
                  Console.WriteLine("\n\nInitial solution: ");
                  for (int i = 0; i < m; i++)
                  {
                      Console.Write("M {0} [", i);
                      for (int y = 0; y < n; y++)
                          Console.Write(init[i * n + y] + ", ");
                      Console.WriteLine("]");
                  }
                  //TAG:begin-sol-input    
                  x.SetLevel(init);
                  //TAG:end-sol-input    


                 Console.WriteLine("\n\nMOSEK solution:");
                 for (int i = 0; i < m; i++)
                 {
                   Console.Write("M {0} [",i);
                   for(int y=0; y<n;y++)
                   {
                      double value = x.Index(i,y).Level()[0];
                       Console.Write( "{0}, ", (int)value);
                   }
                   Console.WriteLine("]");
                 }
              }
              catch(SolutionError e)
              {
                //must do something about....
              }
            }
      
        }

    }
  }
}
