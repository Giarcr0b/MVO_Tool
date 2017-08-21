package com.mosek.fusion.examples;

import java.util.*;
import java.lang.*;
import java.lang.Math.*;
import java.io.*;

import mosek.*;
import mosek.fusion.*;

public class qcqp_sdo_relaxation
{
  public static void main(String [] args)
    {
      //problem dimensions
      int n = 50;
      int m= 2*n;

      Random rnd = new Random();

      // problem data
      double []A  = new double[m*n];
      double []xs = new double[n];

      for(int j=0;j<n;j++)
      {
        for(int i=0;i<m;i++)
          A[i*n +j] = rnd.nextGaussian();
        xs[j]= rnd.nextDouble();
      }
      
      double [] P = new double[n*n];
      double [] q = new double[n];

      //P = A^T A
      LinAlg.syrk(
        mosek.uplo.lo,
        mosek.transpose.no,
        n,m,
        1.0, A, 0., P);

      //must fill P upper triangular
      for(int j=0;j<n;j++)
        for(int i=j+1;i<n;i++)
          P[j*n+i] = P[i*n+j];
      
      // q = -P xs
      LinAlg.gemv(  
        mosek.transpose.no,  
        n,  
        n,  
        -1.0,  
        P,  
        xs,  
        0.,  
        q);
    
      solve(n,P,q);
    }

  //TAG:begin-code
  static void solve(int n, double[] P, double[] q)
    {
      Model M = new Model();

      Variable Z = M.variable(n+1, Domain.inPSDCone());
      
      Variable X= Z.slice(new int[]{0,0},new int[]{n,n});
      Variable x= Z.slice(new int[]{0,n},new int[]{n,n+1});
      M.constraint( Expr.sub(X.diag(),x), Domain.greaterThan(0.) );
      
      M.constraint( Z.index(n,n), Domain.equalsTo(1.));
      Expression TrPX = Expr.sum(Expr.mulElm( Matrix.dense(n,n,P), X ) );
      Expression qtx  = Expr.mul(2.0, Expr.dot( q, x) );
      M.objective( ObjectiveSense.Minimize, Expr.add( TrPX, qtx ) );

      M.setLogHandler(new PrintWriter(System.out));

      M.solve();

      System.out.printf("solution status= %s",M.getPrimalSolutionStatus());

    }
}

