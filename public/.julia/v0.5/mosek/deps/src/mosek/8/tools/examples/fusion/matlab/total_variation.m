function total_variation()

nrows = 50;
ncols = 50;
seed=0;
rng(seed);

sigma = 1.0;

f = min( ones(nrows,ncols), max(zeros(nrows,ncols) , rand(nrows,ncols) + randn(nrows,ncols))) ; 

u = total_var(nrows, ncols, f , sigma);

deltas= abs(u-f);

fprintf( 'max deltas= %f\n', max(max(deltas)) )
fprintf( 'min deltas= %f\n', min(min(deltas)) )

end

function ret = total_var(ncols,nrows,f,sigma)

import mosek.fusion.*

M = Model('TV');

u= M.variable( [ncols+1,nrows+1], Domain.inRange(0.,1.0));
t= M.variable( [ncols, nrows], Domain.unbounded());

ucore=  u.slice([1,1],[nrows+1,ncols+1]);

deltax= Expr.sub( u.slice( [2,1] ,[nrows+2,ncols+1] ), ucore);
deltay= Expr.sub( u.slice( [1,2] ,[nrows+1,ncols+2] ), ucore);

M.constraint( Expr.stack(2, t, deltax, deltay ), Domain.inQCone().axis(2) );

M.constraint(Expr.vstack(sigma, Expr.flatten( Expr.sub( f,  ucore ) )  ),  Domain.inQCone()  );

%boundary conditions are not actually needed
%print('boundary conditions u_n+1,* = u_n,*  ...')
%M.constraint( Expr.sub( u.slice( [n-1,0] ,[n,m] ), u.slice([n,0],[n+1,m]) ), Domain.equalsTo(0.))
%print('boundary conditions u_*,n+1 = u_*,n  ...')
%M.constraint( Expr.sub( u.slice( [0,n-1] ,[n,m] ), u.slice([0,n],[n,m+1]) ), Domain.equalsTo(0.))
        
M.objective(ObjectiveSense.Minimize, Expr.sum(t) );

M.solve()

ret= reshape( u.slice( [1,1] , [nrows+1,ncols+1] ).level() , ...
              [nrows,ncols] );

end
