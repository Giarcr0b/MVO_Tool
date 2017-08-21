/* 
   Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.

   File:      sparsecholesky.c

   Purpose: 

 */
#include <stdio.h>

#include "mosek.h" 


 static MSKrescodee sparsecholesky(MSKenv_t        env,
                                   const MSKint32t n,
                                   const MSKint32t anzc[],
                                   const MSKint32t asubc[],
                                   const MSKint64t aptrc[],
                                   const MSKrealt  avalc[],
                                   MSKint32t       **perm,
                                   MSKrealt        **diag, 
                                   MSKint32t       **lnzc,
                                   MSKint64t       **lptrc,
                                   MSKint64t       *lensubnval,
                                   MSKint32t       **lsubc,
                                   MSKrealt        **lvalc)
{
  MSKrescodee r;

  r = MSK_computesparsecholesky(env,
                                0,         /* Diasble multithreading 
                                              since the problems are small. */
                                1,         /* Permute/reorder to save computational 
                                              work. */ 
                                1.0e-14,
                                n,
                                anzc,
                                aptrc,
                                asubc,
                                avalc,
                                perm,
                                diag,
                                lnzc,
                                lptrc,
                                lensubnval,
                                lsubc,
                                lvalc);

  if ( r==MSK_RES_OK )
  {
    MSKint32t i,s;

    printf("L and D. Length=%d\n", (int) lensubnval[0]);
    for(i=0; i<n; ++i)
    {
      printf("%d perm=%d diag=%.4e :",i,perm[0][i],diag[0][i]);
      for(s=0; s<lnzc[0][i]; ++s)
        printf(" %.4e[%d]",lvalc[0][lptrc[0][i]+s],lsubc[0][lptrc[0][i]+s]);

      printf("\n");
    }
  }

  return ( r );
} /* sparsecholesky */

int main(int argc, const char *argv[])
{
  MSKenv_t        env;
  MSKrescodee     r;

  printf("Sparse Cholesky computation.\n");
  
  /* Create the mosek environment. */
  r = MSK_makeenv(&env,NULL);

  if ( r==MSK_RES_OK )
  { 
    const MSKint32t n       = 4;
    const MSKint32t anzc[]  = {4, 1, 1, 1},
                    asubc[] = {0, 1, 2, 3, 1, 2, 3};
    const MSKint64t aptrc[] = {0, 4, 5, 6};
    const MSKrealt  avalc[] = {4.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                    b[]     = {13.0, 3.0, 4.0, 5.0};
    MSKint32t       *perm=NULL,*lnzc=NULL,*lsubc=NULL;
    MSKint64t       lensubnval,*lptrc=NULL;
    MSKrealt        *diag=NULL,*lvalc=NULL;  

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

    printf("\nFirst example with a definite A.\n");

    r = sparsecholesky(env,n,anzc,asubc,aptrc,avalc,
                       &perm,&diag,&lnzc,&lptrc,&lensubnval,&lsubc,&lvalc);

    if ( r==MSK_RES_OK )
    {
      MSKint32t i;
      MSKrealt  *x;

      x = MSK_callocenv(env,n,sizeof(MSKrealt));
      if ( x )
      {
        /* Permuted b is stored as x. */
        for(i=0; i<n; ++i)
          x[i] = b[perm[i]];

        /* Compute  x = inv(L)*x. */
        r = MSK_sparsetriangularsolvedense(env,MSK_TRANSPOSE_NO,n,
                                           lnzc,lptrc,lensubnval,lsubc,lvalc,x);
       
        if ( r==MSK_RES_OK )
        {
          /* Compute  x = inv(L^T)*x. */ 
          r = MSK_sparsetriangularsolvedense(env,MSK_TRANSPOSE_YES,n,
                                             lnzc,lptrc,lensubnval,lsubc,lvalc,x);
        }

        printf("\nSolution A x = b\n");
        for(i=0; i<n; ++i) 
          printf("x[%d]: %.2e\n",perm[i],x[i]);

        MSK_freeenv(env,x);
      }
      else
        printf("Out of space while creating x.\n");
    }
    else
      printf("Cholesky computation failed: %d\n",(int) r);

    MSK_freeenv(env,perm);
    MSK_freeenv(env,lnzc);
    MSK_freeenv(env,lsubc);
    MSK_freeenv(env,lptrc);
    MSK_freeenv(env,diag);
    MSK_freeenv(env,lvalc);
  }

  if ( r==MSK_RES_OK )
  { 
    const MSKint32t n=3;
    const MSKint32t anzc[]  = {3, 2, 1},
                    asubc[] = {0, 1, 2, 1, 2, 2};
    const MSKint64t aptrc[] = {0, 3, 5};
    const MSKrealt  avalc[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    MSKint32t       *perm=NULL,*lnzc=NULL,*lsubc=NULL;
    MSKint64t       lensubnval,*lptrc=NULL;
    MSKrealt        *diag=NULL,*lvalc=NULL;  

    /* Let A be

           [1.0 1.0 1.0]   
           [1.0 1.0 1.0] 
           [1.0 1.0 1.0]   

       then compute a sparse Cholesky factorization A. Observe A is NOT
       positive definite.
     
     */

    printf("\nSecond example with a semidefinite A.\n");

    r = sparsecholesky(env,n,anzc,asubc,aptrc,avalc,
                       &perm,&diag,&lnzc,&lptrc,&lensubnval,&lsubc,&lvalc);

    MSK_freeenv(env,perm);
    MSK_freeenv(env,lnzc);
    MSK_freeenv(env,lsubc);
    MSK_freeenv(env,lptrc);
    MSK_freeenv(env,diag);
    MSK_freeenv(env,lvalc);
  }

  MSK_deleteenv(&env);

  return ( r );
} /* main */
