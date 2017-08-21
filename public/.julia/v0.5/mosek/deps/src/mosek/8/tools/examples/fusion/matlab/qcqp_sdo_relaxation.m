function qcqp_sdo_relaxation()

% problem data
%n = 50  ;
%m = 2*n ;

%A = randn([m*n,1]);
%xs= rand( [n,1] );

%P= zeros([n,n]);
%q= zeros([n,1]);


%mosek.LinAlg.syrk(mosek.uplo.lo,mosek.transpose.no,n,m,1.0, A, 0., ...
%                 P)

%must fill P upper triangular                                                                                                                                                                                                                                                                                           
%for j = 1:n
%       for i= j+1:n
            %P(j*n+i) = P(i*n+j)
            % end
        % end
    %q = -P xs                                                                                                                                                                                                                                                                                            
%mosek.LinAlg.gemv(mosek.transpose.no, n, n, -1.0,P,xs, 0., q)

import mosek.fusion.*;

% problem dimensions
n = 50  ;
m = 2*n ;

A = randn([m,n]);
P = A' * A;
q = - P* rand( [n,1] );


M =Model();

Z = M.variable(n+1, Domain.inPSDCone());

X= Z.slice([1,1],[n+1,n+1]);
x= Z.slice([1,n+1],[n+1,n+2]);
M.constraint( Expr.sub(X.diag(),x), Domain.greaterThan(0.) );
    
M.constraint( Z.index(n+1,n+1), Domain.equalsTo(1.));

M.objective( ObjectiveSense.Minimize, Expr.add( Expr.sum(Expr.mulElm( Matrix.dense(P), X ) ), Expr.mul(2.0, Expr.dot( x, q) ) ) );
        
M.solve();

end
