%%
%  Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
%
%  File:      nearestcorr.m
%
%  Purpose: 
%  Solves the nearest correlation matrix problem
% 
%    minimize   || A - X ||_F   s.t.  diag(X) = e, X is PSD
%
%  as the equivalent conic program
%
%    minimize     t
%   
%    subject to   (t, vec(A-X)) in Q
%                 diag(X) = e
%                 X >= 0
%    where
%                 vec : M(n x n) -> R^(n*(n+1)/2)
%                 vec(M)_k = M_ij           for k = i * (i+1) / 2 + j, and i == j
%                          | sqrt(2) * M_ij for k = i * (i+1) / 2, i < j


function nearestcorr()
import mosek.fusion.*;
N = 5;
A = [  0.0,  0.5,  -0.1,  -0.2,   0.5;
       0.5,  1.25, -0.05, -0.1,   0.25;
       -0.1, -0.05,  0.51,  0.02, -0.05;
       -0.2, -0.1,   0.02,  0.54, -0.1;
       0.5,  0.25, -0.05, -0.1,   1.25 ];
nearestcorr_frobenius(A,N)

gammas = [0.0:0.1:2.0];

nearestcorr_nucnorm(A,N,gammas)

%%
%  Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
%
%  File:      nearestcorr.m
%
%  Purpose:
%  A variation of the nearest correlation matrix, where we estimate a
%  correlation matrix X >= 0, where X - diag(w) >= 0 has low rank
%  induced by a nuclear-norm penalty, and w >= 0.
%
%  We solve the problem
%
%    minimize     || X + diag(w) - A ||_F + gamma*Tr(X)
%
%    subject to   X >= 0, w >= 0
%
%  as the equivalent conic program
%
%    minimize     t + gamma*Tr(X)
%
%    subject to   (t, vec (X + diag(w) - A)) in Q
%                 X >= 0, w >= 0
%    where
%                 vec : M(n x n) -> R^(n*(n+1)/2)
%                 vec(M)_k = M_ij           for k = i * (i+1) / 2 + j, and i == j
%                          | sqrt(2) * M_ij for k = i * (i+1) / 2, i < j

function nearestcorr_nucnorm(A, N, gammas)

import mosek.fusion.*;


M = Model('NucNorm');

% Setup variables
t = M.variable('t', 1, Domain.unbounded());
X = M.variable('X', Domain.inPSDCone(N));
w = M.variable('w', N, Domain.greaterThan(0.0));

% (t, vec (X + diag(w) - A)) in Q
D = Expr.mulElm( Matrix.eye(N), Var.repeat(w,1,N) );

M.constraint( Expr.vstack( t, vec(Expr.sub(Expr.add(X, D), Matrix.dense(A))) ), ...
              Domain.inQCone() );


TX = Expr.sum(X.diag());

%M.setLogHandler(java.io.PrintWriter(java.lang.System.out));

for g=gammas

    % Objective: Minimize t + gamma*Tr(X)
    M.objective(ObjectiveSense.Minimize, Expr.add(t, Expr.mul(g,TX)));
    M.solve()

    Xl = reshape(X.level(),N,N);
    wl = w.level();

    d = eig(Xl);
    r = A - (Xl + diag(wl));

    disp(sprintf('gamma=%f, res=%e, rank=%d', g, norm(r,'fro'), sum(d>1e-6)))
end
M.dispose();

function nearestcorr_frobenius(A,N)

import  mosek.fusion.*;


% Create a model with the name NearestCorrelation
M = Model('NearestCorrelation');

% Setting up the variables
X = M.variable('X', Domain.inPSDCone(N));
t = M.variable('t', 1, Domain.unbounded());

% (t, vec (A-X)) \in Q
M.constraint( Expr.vstack(t, vec(Expr.sub(A,X))), Domain.inQCone() );

% diag(X) = e
M.constraint(X.diag(), Domain.equalsTo(1.0));


% Objective: minimize t
M.objective(ObjectiveSense.Minimize, t);

% Solve the problem
M.solve();

% Get the solution values
reshape( X.level(), N,N)
M.dispose();


function r = vec(e)
% Assuming that e is an NxN expression, return the lower triangular part as a vector.
import mosek.fusion.*;

N = e.getShape().dim(1);

subi = [1: N * (N+1) / 2];
subj = zeros(N*(N+1)/2,1);
val  = zeros(N*(N+1)/2,1);

k=1;
for j=1:N,
    for i=j:N,
        subj(k) = i+(j-1)*N;
        if (i==j),
            val(k) = 1;
        else
            val(k) = sqrt(2);
        end;
        k = k + 1;
    end        
end

S = Matrix.sparse(N * (N+1) / 2, N * N, subi, subj, val);
r = Expr.mul(S, Expr.reshape( e, N*N ));
