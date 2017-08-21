## 
#  Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
#
#  File:      sparsecholesky.py
#
#  Purpose:   
##

import sys
import mosek

def sparsecholesky(env,
                   n,
                   anzc,
                   asubc,
                   aptrc,
                   avalc):

  multiworker = 0        # Diasble multithreading since the problems are small. 
  order_meth  = 1        # Permute/reorder to save computational work
  tolsingular = 1.0e-14

  try:
    perm,diag,lnzc,lptrc,lensubnval,lsubc,lvalc = env.computesparsecholesky(multiworker,
                                                                            order_meth,
                                                                            tolsingular,
                                                                            anzc,
                                                                            aptrc,
                                                                            asubc,
                                                                            avalc)

    print("L and D. Length=%d\n"% lensubnval);
    for i in range(n):
    
      print ( ' '.join( [ "%d perm=%d diag=%.4e :" % (i, perm[i], diag[i])] +
                        [ " %.4e[%d]" % (lvalc[lptrc[i]+s],lsubc[lptrc[i]+s]) for s in range(lnzc[i]) ]
                      ) 
            )
    
  except:
    raise

  return perm,diag,lnzc,lptrc,lensubnval,lsubc,lvalc


print("Sparse Cholesky computation.")
  
# Create the mosek environment.
with mosek.Env() as env:
    with env.Task(0,0) as task:
  
      # Let A be
      #
      #     [4.0  1.0 1.0 1.0]  
      #     [1.0  1.0        ]
      #     [1.0      1.0    ] 
      #     [1.0          1.0]
      #
      # then
      #
      #    a. Compute a sparse Cholesky factorization A.
      #    b. Solve the linear system A x = b using the Cholesky factor
      #
      # Observe that anzc, aptrc, asubc and avalc only specify the lower triangular part.

      n     = 4
      anzc  = [4, 1, 1, 1]
      asubc = [0, 1, 2, 3, 1, 2, 3]
      aptrc = [0, 4, 5, 6]
      avalc = [4.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]
      b     = [13.0, 3.0, 4.0, 5.0]
     
     

      print("First example with a definite A.")

      
      perm, diag, lnzc, lptrc, lensubnval, lsubc, lvalc = sparsecholesky(env,
                                                                         n,
                                                                         anzc,
                                                                         asubc,
                                                                         aptrc,
                                                                         avalc)
      

      # Permuted b is stored as x.
      x = [ b[p] for p in perm ]

      # Compute  x = inv(L)*x.
      env.sparsetriangularsolvedense(mosek.transpose.no,
                                     lnzc,
                                     lptrc,
                                     lsubc,
                                     lvalc, 
                                     x)
                                     
       
      # Compute  x = inv(L^T)*x. 
      env.sparsetriangularsolvedense(mosek.transpose.yes,
                                     lnzc,
                                     lptrc,
                                     lsubc,
                                     lvalc,
                                     x)
      

      print("\n\nSolution A x = b")
      print('\n'.join([ "x[%d]: %.2e"% (pp,xx) for pp,xx in zip(perm,x) ] ) )

      n     = 3
      anzc  = [3, 2, 1]
      asubc = [0, 1, 2, 1, 2, 2]
      aptrc = [0, 3, 5]
      avalc = [1.0, 1.0, 1.0, 1.0, 1.0, 1.0]
      
      # Let A be
      #
      # [1.0 1.0 1.0]   
      # [1.0 1.0 1.0] 
      # [1.0 1.0 1.0]   
      #
      # then compute a sparse Cholesky factorization A. Observe A is NOT
      # positive definite.
      #
     

      print("Second example with a semidefinite A.")
      
      perm, diag, lnzc, lptrc, lensubnval, lsubc, lvalc = sparsecholesky(env,
                                                                         n,
                                                                         anzc,
                                                                         asubc,
                                                                         aptrc,
                                                                         avalc)      
      
