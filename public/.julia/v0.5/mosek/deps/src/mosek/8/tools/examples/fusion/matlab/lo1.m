%%
% Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
%
% File:      lo1.m
%
% Purpose: Demonstrates how to solve the problem
%
% minimize 3*x1 + 5*x2 + x3 + x4
% such that
%          3*x1 + 2*x2        +   x4 = 30,
%          2*x1 + 3*x2 +   x3 +   x4 > 15,
%                      + 3*x3 + 2*x4 < 25
% and
%          x1,x2,x3 > 0,
%          0 < x4 < 10
%
function lo1()
import mosek.fusion.*;

c = [3.0, 1.0, 5.0, 1.0];

A = [ 3.0, 2.0, 0.0, 1.0 ; ...
      2.0, 3.0, 1.0, 1.0 ; ...
      0.0, 0.0, 3.0, 2.0 ];
 
% Create a model with the name 'lo1'
M = Model();

% Create variable 'x' of length 4
x = M.variable('x', 4, Domain.greaterThan(0.0));

% Create three constraints
M.constraint('c1', Expr.dot(A(1,:), x), Domain.equalsTo(30.0));
M.constraint('c2', Expr.dot(A(2,:), x), Domain.greaterThan(15.0));
M.constraint('c3', Expr.dot(A(3,:), x), Domain.lessThan(25.0));

% Set the objective function to (c^t * x)
M.objective('obj', ObjectiveSense.Maximize, Expr.dot(c, x));


% Solve the problem
M.solve();

% Get the solution values
sol = x.level();
disp(['[x1 x2 x3 x4] = ' mat2str(sol',7)]);
%%TAG:end-lo1