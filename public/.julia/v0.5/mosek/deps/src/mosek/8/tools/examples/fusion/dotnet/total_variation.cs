using System;
using mosek.fusion;

namespace mosek
{
    namespace fusion
    {
        namespace example
        {
            public class total_variation
            {

                public static void Main(string[] args)
                {
                    int ncols = 50;
                    int nrows = 50;
                    int seed  =  0;
                    double sigma = 1.0;

                    int ncells = nrows * ncols;

                    Random gen = new Random(seed);

                    double[] f = new double[ncells];

                    for (int i = 0; i < ncells; i++)
                    {
                      double xx = Math.Sqrt(-2.0 * Math.Log(gen.NextDouble()));
                      double yy = Math.Sin(2.0 * Math.PI * gen.NextDouble());
                      f[i] = Math.Max(Math.Min(1.0, xx*yy) , .0);
                    }
                    
                    //TAG:begin-tv-code

                    //TAG:begin-tv-init
                    Model M = new Model("TV");
                    try
                    {

                      Variable u = M.Variable(new int[]{ nrows + 1, ncols + 1}, 
                                              Domain.InRange(0.0, 1.0));
                      Variable t = M.Variable(new int[]{nrows , ncols }, Domain.Unbounded());
                      //TAG:end-tv-init

                      //TAG:begin-tv-core-grid
                      Variable ucore = u.Slice(new int[] { 0, 0 }, new int[] { nrows, ncols });
                      //TAG:end-tv-core-grid

                      //TAG:begin-tv-deltas
                      Expression deltax = Expr.Sub(u.Slice(new int[] { 1, 0 }, 
                                                           new int[] { nrows + 1, ncols }), 
                                                   ucore);
                      Expression deltay = Expr.Sub(u.Slice(new int[] { 0, 1 },
                                                           new int[] { nrows, ncols + 1 }), 
                                                   ucore);
                      //TAG:end-tv-deltas

                      //TAG:begin-tv-norms
                      M.Constraint(Expr.Stack(2, t, deltax, deltay), Domain.InQCone().Axis(2));
                      //TAG:end-tv-norms

                      //TAG:begin-tv-sigma
                      Matrix mat_f = Matrix.Dense(nrows,ncols,f);
                      M.Constraint(Expr.Vstack( sigma, Expr.Flatten( Expr.Sub(ucore, mat_f)) ),
                                   Domain.InQCone());
                      //TAG:end-tv-sigma

                      /*
                        boundary conditions are not actually needed
                        M.constraint( Expr.sub( u.slice( [n-1,0] ,[n,m] ), u.slice([n,0],[n+1,m]) ), 
                        Domain.equalsTo(0.));
                        M.constraint( Expr.sub( u.slice( [0,n-1] ,[n,m] ), u.slice([0,n],[n,m+1]) ), 
                        Domain.equalsTo(0.));
                      */

                      M.SetLogHandler(Console.Out);

                      //TAG:begin-tv-obj-fun
                      M.Objective(ObjectiveSense.Minimize, Expr.Sum(t));
                      //TAG:end-tv-obj-fun			

                      M.Solve();
                    }
                    finally
                    {
                        M.Dispose();
                    }
                    //TAG:end-tv-code
                }
            }
        }
    }
  
}
