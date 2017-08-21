##
#  Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
#
#  File:      nearestcorr.py
#
#  Purpose: 
#  Solves the nearest correlation matrix problem
# 
#    minimize   || A - X ||_F   s.t.  diag(X) = e, X is PSD
#
#  as the equivalent conic program
#
#    minimize     t
#   
#    subject to   (t, vec(A-X)) in Q
#                 diag(X) = e
#                 X >= 0
#    where
#                 vec : M(n x n) -> R^(n*(n+1)/2)
#                 vec(M)_k = M_ij           for k = i * (i+1) / 2 + j, and i == j
#                          | sqrt(2) * M_ij for k = i * (i+1) / 2, i < j
##

import sys
import mosek
import mosek.fusion
from   mosek.fusion import *
from   mosek import LinAlg
from   math import sqrt

def vec(e):
    """
    Assuming that e is an NxN expression, return the lower triangular part as a vector.
    """
    N = e.getShape().dim(0)
    
    rows = [i for i in range(N) for j in range(i,N)]
    cols = [j for i in range(N) for j in range(i,N)]
    vals = [ 2.0**0.5  if i!=j else 1.0 for i in range(N)  for j in range(i,N)]

    return Expr.flatten(Expr.mulElm(e, Matrix.sparse(N,N,rows,cols,vals)))

def nearestcorr(A):

    N = A.numRows()

    # Create a model with the name 'NearestCorrelation

    with Model("NearestCorrelation") as M:

      # Setting up the variables
      X = M.variable("X", Domain.inPSDCone(N))
      t = M.variable("t", 1, Domain.unbounded())


      # (t, vec (A-X)) \in Q
      v = vec( Expr.sub(A,X) )
      M.constraint("C1", Expr.vstack(t, v ), Domain.inQCone() )

      # diag(X) = e
      M.constraint("C2",X.diag(), Domain.equalsTo(1.0))
#      M.setLogHandler(sys.stdout)
      # Objective: Minimize t
      M.objective(ObjectiveSense.Minimize, t)
                        
      # Solve the problem
      M.solve()
     
      return X.level(),t.level()

##
#
#  Purpose:
#  A variation of the nearest correlation matrix, where we estimate a
#  correlation matrix X >= 0, where X - diag(w) >= 0 has low rank
#  induced by a nuclear-norm penalty, and w >= 0.
#
#  We solve the problem
#
#    minimize     || X + diag(w) - A ||_F + gamma*Tr(X)
#
#    subject to   X >= 0, w >= 0
#
#  as the equivalent conic program
#
#    minimize     t + gamma*Tr(X)
#
#    subject to   (t, vec (X + diag(w) - A)) in Q
#                 X >= 0, w >= 0
#    where
#                 vec : M(n x n) -> R^(n*(n+1)/2)
#                 vec(M)_k = M_ij           for k = i * (i+1) / 2 + j, and i == j
#                          | sqrt(2) * M_ij for k = i * (i+1) / 2, i < j
def nearestcorr_nucnorm(A,gammas):
    N = A.numRows()
    with Model("NucNorm") as M:
      # Setup variables
      t = M.variable("t", 1, Domain.unbounded())
      X = M.variable("X", N, Domain.inPSDCone())
      w = M.variable("w", N, Domain.greaterThan(0.0))

      # D = diag(w)
      D =   Expr.mulElm( Matrix.eye(N), Var.repeat(w,1,N) )
      # (t, vec (X + D - A)) in Q
      M.constraint( Expr.vstack( t, vec(Expr.sub(Expr.add(X, D), A)) ),
                    Domain.inQCone() )

      #M.setLogHandler(sys.stdout)

      d = [0.0]*int(N)
      result = []

      for g in gammas:

          # Objective: Minimize t + gamma*Tr(X)
          M.objective(ObjectiveSense.Minimize, Expr.add(t, Expr.mul(g, Expr.sum(X.diag()) ) ))
          M.solve()

          Xl = X.level()
          wl = w.level()
          r = ([ 2*(A.get(j,i) - Xl[i+j*N])*(A.get(j,i) - Xl[i+j*N])
                for j in range(N) for i in range(j+1,N) ] +
               [(A.get(i,i) - Xl[i+i*N] - wl[i])*(A.get(i,i) - Xl[i+i*N] - wl[i]) 
                for i in range(N)])

          LinAlg.syeig(mosek.uplo.lo,N, X.level(), d)
        
          result.append((g, sqrt(sum(r)), sum([d[i]>1e-6 for i in range(N)]), X.level() ))

      return result


if __name__ == '__main__':

    N = 5
    A = Matrix.dense(N,N,[ 0.0,  0.5,  -0.1,  -0.2,   0.5,
                          0.5,  1.25, -0.05, -0.1,   0.25,
                         -0.1, -0.05,  0.51,  0.02, -0.05,
                         -0.2, -0.1,   0.02,  0.54, -0.1,
                          0.5,  0.25, -0.05, -0.1,   1.25])

    gammas = [ 0.1 * i for i in range(11) ]

    X,t = nearestcorr(A)

    print("--- Nearest Correlation ---")
    print("X = ")
    print(X.reshape((N,N)))
    print("t = ",t)
    
    print("--- Nearest Correlation with Nuclear Norm---")
    for g,res,rank,X in nearestcorr_nucnorm(A,gammas):
      print("gamma=%f, res=%e, rank=%d" % (g, res,rank))
