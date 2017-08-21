/*
   Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.

   File:      sparsecholesky.cs

   Purpose:   
              
 */

using System;

public class Sparsecholesky
{  

  public static void Main ()
  {


    /* Create the mosek environment. */
    using (mosek.Env env = new mosek.Env())
    {
      {

        /* Let A be
           
           [4.0  1.0 1.0 1.0]  
           [1.0  1.0        ]
           [1.0      1.0    ] 
           [1.0          1.0]
           
           then
           
           a. Compute a sparse Cholesky factorization A.
           b. Solve the linear system A x = b using the Cholesky factor
           
           Observe that anzc, aptrc, asubc and avalc only specify the lower triangular part.
     
        */

   
        Console.WriteLine("First example with a definite A.");

        const int n           = 4;
        
        int[] anzc            = {4, 1, 1, 1};
        int[] asubc           = {0, 1, 2, 3, 1, 2, 3};
        long[] aptrc          = {0, 4, 5, 6};
        double[] avalc        = {4.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
        double[] b            = {13.0, 3.0, 4.0, 5.0};
                
        int[] perm     = new int[n];
        int[] lnzc     = new int[n*n];
        int[] lsubc    = new int[n*n];
        long lensubnval;
        double[] diag  = new double[n];
        long[] lptrc   = new long[1];
        double[] lvalc = new double[n*n];
        double[] x     = new double[n];
        
      
        doSparsecholesky(env,
                         n,
                         anzc, asubc, aptrc, avalc,
                         out perm, out diag, 
                         out lnzc, out lptrc, out lensubnval, out lsubc, out lvalc);
      

        /* Permuted b is stored as x. */
        for(int i=0; i<n; ++i)
          x[i] = b[perm[i]];

        /*Compute  x = inv(L)*x.*/
        env.sparsetriangularsolvedense(mosek.transpose.no,lnzc,lptrc,lsubc,lvalc,x);
        /*Compute  x = inv(L^T)*x.*/
        env.sparsetriangularsolvedense(mosek.transpose.yes,lnzc,lptrc,lsubc,lvalc,x);

        Console.WriteLine("\nSolution A x = b\n");
        for(int i=0; i<n; ++i)
          Console.WriteLine( "x[{0}]: {1}", perm[i], x[i]);
      }
      {
        /* Let A be
           
           [1.0 1.0 1.0]   
           [1.0 1.0 1.0] 
           [1.0 1.0 1.0]   
           
           then compute a sparse Cholesky factorization A. Observe A is NOT
           positive definite.
           
        */
        Console.WriteLine("Second example with a semidefinite A.");

        const int n           = 3;
        
        int[] anzc            = {3, 2, 1};
        int[] asubc           = {0, 1, 2, 1, 2, 2};
        long[] aptrc          = {0, 3, 5, };
        double[] avalc        = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
                
        int[] perm     = new int[n];
        int[] lnzc     = new int[n*n];
        int[] lsubc    = new int[n*n];
        long lensubnval;
        double[] diag  = new double[n];
        long[] lptrc   = new long[1];
        double[] lvalc = new double[n*n];
        double[] x     = new double[n];
        
        doSparsecholesky(env,
                         n,
                         anzc, asubc, aptrc, avalc,
                         out perm, out diag, 
                         out lnzc, out lptrc, out lensubnval, out lsubc, out lvalc);
        
      }
    }
  }


  static void doSparsecholesky(mosek.Env    env,
                               int          n,
                               int[]        anzc,
                               int[]        asubc,
                               long[]       aptrc,
                               double[]     avalc,
                               out int[]    perm,
                               out double[] diag,
                               out int[]    lnzc,
                               out long[]   lptrc,
                               out long     lensubnval,
                               out int[]    lsubc,
                               out double[] lvalc)                              
    {
    
    const int multiworker = 0;
    const int order_meth  = 1;
    double   tolsingular  = 1.0e-14;

    env.computesparsecholesky(multiworker,
                              order_meth,
                              tolsingular,
                              anzc,
                              aptrc,
                              asubc,
                              avalc,
                              out perm,
                              out diag,
                              out lnzc,
                              out lptrc,
                              out lensubnval,
                              out lsubc,
                              out lvalc);
    
    Console.WriteLine("L and D. Length={0}\n",lensubnval);
    for(int i=0; i<n; ++i)
    {
      Console.Write("{0} perm={1} diag={2}:",i,perm[i],diag[i]);
      for(int s=0; s<lnzc[i]; ++s)
        Console.Write(" {0}[{1}]",lvalc[lptrc[i]+s],lsubc[lptrc[i]+s]);
      Console.Write("\n");
    }

  }
  

} /* main */
