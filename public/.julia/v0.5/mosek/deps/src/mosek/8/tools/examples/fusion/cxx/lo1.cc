////
//  Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.
//
//  File:      lo1.cc
//
//  Purpose: Demonstrates how to solve the problem
//
//  minimize 3*x0 + 5*x1 + x2 + x3
//  such that
//           3*x0 + 2*x1        +   x3 = 30,
//           2*x0 + 3*x1 +   x2 +   x3 > 15,
//                       + 3*x2 + 2*x3 < 25
//  and
//           x0,x1,x2 > 0,
//           0 < x3 < 10
////

#include <memory>
#include <iostream>


#include "fusion.h"

using namespace mosek::fusion;
using namespace monty;

int main(int argc, char ** argv)
{
  auto A1 = new_array_ptr<double,1>({ 3.0, 2.0, 0.0, 1.0 });
  auto A2 = new_array_ptr<double,1>({ 2.0, 3.0, 1.0, 1.0 });
  auto A3 = new_array_ptr<double,1>({ 0.0, 0.0, 3.0, 2.0 });
  auto c  = new_array_ptr<double,1>({ 3.0, 5.0, 1.0, 1.0 });

  Model::t M = new Model("lo1"); auto _M = finally([&]() { M->dispose(); });

  M->setLogHandler([=](const std::string & msg) { std::cout << msg << std::flush; } );

  Variable::t x = M->variable("x", 4, Domain::greaterThan(0.0));

  M->constraint("c1", Expr::dot(A1, x), Domain::equalsTo(30.0));
  M->constraint("c2", Expr::dot(A2, x), Domain::greaterThan(15.0));
  M->constraint("c3", Expr::dot(A3, x), Domain::lessThan(25.0));

  M->objective("obj", ObjectiveSense::Maximize, Expr::dot(c, x));

  M->solve();

  auto sol = x->level();
  
  std::cout << "[x0,x1,x2,x3] = [" << (*sol)[0] << "," << (*sol)[1] << "," << (*sol)[2] << " ]\n";
}
