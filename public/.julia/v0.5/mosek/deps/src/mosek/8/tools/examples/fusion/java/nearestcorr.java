package com.mosek.fusion.examples;
/*
   Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
 
   File:      nearestcorr.java
 
   Purpose: 
   Solves the nearest correlation matrix problem
  
     minimize   || A - X ||_F   s.t.  diag(X) = e, X is PSD
 
   as the equivalent conic program
 
     minimize     t
    
     subject to   (t, vec(A-X)) in Q
                  diag(X) = e
                  X >= 0
     where
                  vec : M(n x n) -> R^(n*(n+1)/2)
                  vec(M)_k = M_ij           for k = i * (i+1) / 2 + j, and i == j
                           | sqrt(2) * M_ij for k = i * (i+1) / 2, i < j
*/
import mosek.*;
import mosek.fusion.*;

public class nearestcorr 
{

  //TAG:begin-nearestcorr-vec
  /** Assuming that e is an NxN expression, return the lower triangular part as a vector.
   */
  public static Expression vec(Expression e)
    {
      int N         = e.getShape().dim(0);
      int[] msubi   = new int[N*(N+1)/2];
      int[] msubj   = new int[N*(N+1)/2];
      double[] mcof = new double[N*(N+1)/2];
      
      for (int i = 0, k = 0; i < N; ++i)
        for (int j = 0; j < i+1; ++j, ++k)
        {
          msubi[k] = k;
          msubj[k] = i*N+j;
          if (i == j) mcof[k] = 1.0;
          else        mcof[k] = Math.sqrt(2);
          
        }
      
      Matrix S = Matrix.sparse(N * (N+1) / 2,N * N,msubi,msubj,mcof);
      
      return Expr.mul(S,Expr.reshape( e, N * N ));
    }
  //TAG:end-nearestcorr-vec

  private static String mattostr(double[] a, int n)
    {
      StringBuilder b = new StringBuilder();
      java.util.Formatter f = new java.util.Formatter(b, java.util.Locale.US);

      if( a.length == 1)
      {
        f.format("%f\n", a[0]);
        return b.toString();
      }

      for (int i = 0; i < a.length; ++i) 
      {
        if(  i  % n == 0 )
          b.append("[");
        f.format(" %.3e ", a[i]);
        if( ( i+1 ) % n == 0 )
          b.append("]\n");
      }
      return b.toString();
    }

  //TAG:begin-nearestcorr-nucnorm-code
  private static void nearestcorr_nn(Matrix A, double[] gammas, double[] res, int[] rank)
    throws SolutionError
    {
      int N = A.numRows();
      Model M = new Model("NucNorm");
      try
      {
        // Setup variables
        Variable t = M.variable("t", 1, Domain.unbounded());
        Variable X = M.variable("X", N, Domain.inPSDCone());
        Variable w = M.variable("w", N, Domain.greaterThan(0.0));

        // (t, vec (X + diag(w) - A)) in Q
        Expression D = Expr.mulElm( Matrix.eye(N), Var.repeat(w,1,N) );
                            
        M.constraint( Expr.vstack( t, vec(Expr.sub(Expr.add(X, D), A)) ), Domain.inQCone() );

        //M.setLogHandler(new java.io.PrintWriter(System.out));

        Expression TX = Expr.sum(X.diag());

        double[] d = new double[N];
        for (int k = 0; k < gammas.length; ++k)
        {
          // Objective: Minimize t + gamma*Tr(X)
          M.objective(ObjectiveSense.Minimize, Expr.add(t, Expr.mul(gammas[k],TX)));
          M.solve();

          double[] Xl = X.level();
          double[] wl = w.level();

          double r_sqr = 0.0;
          for (int j = 0; j < N; ++j)
            for (int i = j+1; i < N; ++i)
              r_sqr += 2*(A.get(j,i) - Xl[i+j*N])*(A.get(j,i) - Xl[i+j*N]);
          for (int i = 0; i < N; ++i)
            r_sqr += (A.get(i,i) - Xl[i+i*N] - wl[i])*(A.get(i,i) - Xl[i+i*N] - wl[i]);
                          
          LinAlg.syeig(mosek.uplo.lo,N, X.level(), d);

          int rnk = 0; for (int i = 0; i < d.length; ++i) if (d[i] > 1e-6) ++rnk;
          
          res[k] = Math.sqrt(r_sqr);
          rank[k] = rnk;
        }
      }
      finally
      {
        M.dispose();
      }
    }
  //TAG:end-nearestcorr-nucnorm-code

  //TAG:begin-nearestcorr-code
  private static void nearestcorr(Matrix A)
    throws SolutionError
    {
      int N = A.numRows();

      Model M = new Model("NearestCorrelation");    
      try
      {
        // Setting up the variables
        Variable X = M.variable("X", Domain.inPSDCone(N));
        Variable t = M.variable("t", 1, Domain.unbounded());

        // (t, vec (A-X)) \in Q
        M.constraint( Expr.vstack(t, vec(Expr.sub( A,X))), Domain.inQCone() );

        // diag(X) = e
        M.constraint(X.diag(), Domain.equalsTo(1.0));

        // Objective: Minimize t
        M.objective(ObjectiveSense.Minimize, t);
                        
        // Solve the problem
        M.solve();

        // Get the solution values
        System.out.println("X = \n" + mattostr(X.level(), N));
        System.out.println("t = \n" + mattostr(t.level(), N));
        
      } 
      finally
      {
        M.dispose();
      }
    }
  //TAG:end-nearestcorr-code

  public static void main(String[] argv)
    throws SolutionError
    {
      int N = 5;
      Matrix A = Matrix.dense(N,N,
                              new double[] { 0.0,  0.5,  -0.1,  -0.2,   0.5,
                                             0.5,  1.25, -0.05, -0.1,   0.25,
                                             -0.1, -0.05,  0.51,  0.02, -0.05,
                                             -0.2, -0.1,   0.02,  0.54, -0.1,
                                             0.5,  0.25, -0.05, -0.1,   1.25 });
      double[] gammas = range(0.0, 2.0, 0.1);
      double[] res    = new double[gammas.length];
      int[]    rank   = new int[gammas.length];
      
      
      nearestcorr(A);
      
      nearestcorr_nn(A, gammas, res, rank);
      
      for (int i = 0; i < gammas.length; ++i)
        System.out.printf("gamma = %.1f, res=%.3e, rank = %d\n", gammas[i], res[i],rank[i]);
    }


  private static double[] range (double start, double stop, double step)
    {
      int len;
      if (start < stop && step > 0.0)
        len = 1+ (int)((stop-start-1) / step);
      else if (stop < start && step < 0)
        len = 1 + (int)((start-stop-1) / (- step));
      else
        len = 0;
      double[] res = new double[len];
      double v = start;
      for (int i = 0; i < len; ++i, v += step) 
        res[i] = v;
      return res;
    }

  
}
