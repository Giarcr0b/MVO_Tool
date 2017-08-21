##
# Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
#
# File:      total_variation.py
#
# Purpose:   Demonstrates how to solve a total 
#            variation problem using the 
#            Fusion API.
#
##
import sys
import mosek
from mosek.fusion import *
import numpy as np

def total_var(n,m,f,sigma):
    """
    2-dimensional model using sliding windows         
    """
    with Model('TV') as M:

        u= M.variable( [n+1,m+1], Domain.inRange(0.,1.0))
        t= M.variable( [n,m], Domain.unbounded())

        ucore=  u.slice([0,0],[n,m])

        deltax= Expr.sub( u.slice( [1,0] ,[n+1,m] ), ucore)
        deltay= Expr.sub( u.slice( [0,1] ,[n,m+1] ), ucore)

        M.constraint( Expr.stack(2, t, deltax, deltay ), Domain.inQCone().axis(2) )

        fmat = Matrix.dense(n,m,f)
        M.constraint(Expr.vstack(sigma, Expr.flatten( Expr.sub( fmat, ucore ) )  ),
                     Domain.inQCone() )

        #boundary conditions are not actually needed
        #print('boundary conditions u_n+1,* = u_n,*  ...')
        #M.constraint( Expr.sub( u.slice( [n-1,0] ,[n,m] ), u.slice([n,0],[n+1,m]) ),
        #Domain.equalsTo(0.))
        #print('boundary conditions u_*,n+1 = u_*,n  ...')
        #M.constraint( Expr.sub( u.slice( [0,n-1] ,[n,m] ), u.slice([0,n],[n,m+1]) ),
        #Domain.equalsTo(0.))
        
        M.objective(ObjectiveSense.Minimize, Expr.sum(t) )
        M.setLogHandler(sys.stdout)

        M.solve()

        try:
            return u.slice([0,0],[n,m]).level()
        except: 
            pass

    return None



if __name__ == '__main__':

    nrows = 50
    ncols = 50
    np.random.seed(0)
    ncells=  nrows*ncols
    sigma = 1.0

    #generate a random distribution among the grid
    u = np.random.uniform(0., 1., ncells)
    #add a gaussian noise
    f = u + np.random.normal(0., sigma, ncells)
    #trim spikes
    f= np.minimum( np.maximum(f, np.zeros( f.shape ) ), np.ones(f.shape) )
    
    u = total_var(nrows, ncols, f , sigma)

    deltas= [ abs(u[i]-f[i]) for i in range(ncells)]
    print( 'max deltas= ',max(deltas))
    print( 'min deltas= ',min(deltas))



