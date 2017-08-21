##
# Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
#
# File:      qcqp_sdo_relaxation.py
#
# Purpose:   Demonstrate how to use SDP to solve
#            convex relaxation of a mixed-integer QCQP 
##

import mosek
from mosek.fusion import *
import sys
import random


def miqcqp_sdo_relaxation(n,P,q):
    with Model() as M:

        Z = M.variable(n+1, Domain.inPSDCone())

        X= Z.slice([0,0],[n,n])
        x= Z.slice([0,n],[n,n+1])

        M.constraint( Expr.sub(X.diag(),x), Domain.greaterThan(0.) )
    
        M.constraint( Z.index(n,n), Domain.equalsTo(1.))

        M.objective( ObjectiveSense.Minimize, Expr.add( 
            Expr.sum( Expr.mulElm( Matrix.dense(n,n,P), X ) ), 
            Expr.mul(2.0, Expr.dot( x, q) ) 
        ) )

        M.solve()


# problem dimensions
n = 50
m = 2*n

# problem data
A =  [random.gauss(0., 1.0) for i in range(n*m)]
xs = [random.uniform(0., 1.0)  for i in range(n)]

P =[0.]*(n*n)
q =[0.]*n

mosek.LinAlg.syrk(
    mosek.uplo.lo,
    mosek.transpose.no,
    n,m,
    1.0, A, 0., P)

#must fill P upper triangular                                                                                                                                                                                                                                                                                           
for j in range(n):
    for i in range(j+1,n):
        P[j*n+i] = P[i*n+j]

#q = -P xs                                                                                                                                                                                                                                                                                                             
mosek.LinAlg.gemv(
    mosek.transpose.no,
    n,
    n,
    -1.0,
    P,
    xs,
    0.,
    q)

miqcqp_sdo_relaxation(n,P,q)
