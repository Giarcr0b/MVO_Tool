/*
   Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.

   File:      blas_lapack.cs

   Purpose: To demonstrate how to call BLAS/LAPACK routines for whose MOSEK provides simplified interfaces.
*/

using System;
 
public class blas_lapack
{
         
  public static void Main ()
  {
    const int n=3,m=2,k=2;

    double alpha=2.0,beta=0.5;
    double[] x={1.0,1.0,1.0};
    double[] y={1.0,2.0,3.0};
    double[] z={1.0,1.0};

    /*A has m=2 rows and k=3 cols*/
    double[] A={1.0,1.0,2.0,2.0,3.0,3.0};
    /*B has k=3 rows and n=3 cols*/
    double[] B={1.0,1.0,1.0,
                1.0,1.0,1.0,
                1.0,1.0,1.0};
    double[] C={1.0,2.0,3.0,
                4.0,5.0,6.0};

    double[] D={1.0,1.0,1.0,1.0};
    double[] Q={1.0,0.0,0.0,2.0};  
    double[] v= new double[2];
      
    double xy;
    

    using (mosek.Env env = new mosek.Env())
    {
      /* BLAS routines */
      
      try
      {
      
        /*TAG:begin-dot*/
        env.dot(n, x, y, out xy);
        /*TAG:end-dot*/
        
        /*TAG:begin-axpy*/
        env.axpy(n, alpha,x,y);
        /*TAG:end-axpy*/

        /*TAG:begin-gemv*/
        env.gemv(mosek.transpose.no, m, n, alpha, A, x, beta,z);
        /*TAG:end-gemv*/

        /*TAG:begin-gemm*/
        env.gemm(mosek.transpose.no,mosek.transpose.no,m,n,k,alpha,A,B,beta,C);
        /*TAG:end-gemm*/

        /*TAG:begin-syrk*/
        env.syrk(mosek.uplo.lo,mosek.transpose.no,m,k,alpha, A, beta,D);
        /*TAG:end-syrk*/

        /* LAPACK routines*/

        /*TAG:begin-potrf*/
        env.potrf(mosek.uplo.lo,m,Q);
        /*TAG:end-potrf*/

        /*TAG:begin-syeig*/
        env.syeig(mosek.uplo.lo,m,Q,v);
        /*TAG:end-syeig*/

        /*TAG:begin-syevd*/
        env.syevd(mosek.uplo.lo,m,Q,v);
        /*TAG:end-syevd*/
      }
      catch (mosek.Exception e)
      {
        Console.WriteLine (e.Code);
        Console.WriteLine (e);
      }
      finally
      {
        if (env  != null)  env.Dispose ();
      }
    }
  }
}
