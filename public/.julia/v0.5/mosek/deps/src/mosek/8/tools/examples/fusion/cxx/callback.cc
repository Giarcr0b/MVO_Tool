/*
   Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.

   File:      callback.cc

   Purpose:   To demonstrate how to use the progress 
              callback. 

              Compile and link the file with MOSEK, then 
              use as follows:

              callback psim
              callback dsim
              callback intpnt

              The argument tells which optimizer to use
              i.e. psim is primal simplex, dsim is dual simplex
              and intpnt is interior-point. 
 */


#include <memory>
#include <iostream>
#include <string>

#include "mosek.h"
#include "fusion.h"

using namespace mosek::fusion;
using namespace monty;


/* Note: This function is declared using MSKAPI,
         so the correct calling convention is
         employed. */

static void MSKAPI usercallback( MSKcallbackcodee caller,
                                 const double   * douinf,
                                 const int32_t  * intinf,
                                 const int64_t  * lintinf,
                                 Model::t mod,
                                 const double maxtime)
{
  switch ( caller )
  {
    case MSK_CALLBACK_BEGIN_INTPNT:
      std::cerr<<"Starting interior-point optimizer\n";
      break;
    case MSK_CALLBACK_INTPNT:
      std::cerr<<"Iterations: "<< intinf[MSK_IINF_INTPNT_ITER];
      std::cerr<<" ("<<douinf[MSK_DINF_OPTIMIZER_TIME]<<"/";
      std::cerr<<douinf[MSK_DINF_INTPNT_TIME]<<")s. \n";
      std::cerr<<"Primal obj.: "<< douinf[MSK_DINF_INTPNT_PRIMAL_OBJ];
      std::cerr<<" Dual obj.: "<<  douinf[MSK_DINF_INTPNT_DUAL_OBJ]<<std::endl;
      break;
    case MSK_CALLBACK_END_INTPNT:
      std::cerr<<"Interior-point optimizer finished.\n";
      break;
    case MSK_CALLBACK_BEGIN_PRIMAL_SIMPLEX:
      std::cerr<<"Primal simplex optimizer started.\n";
      break;
    case MSK_CALLBACK_UPDATE_PRIMAL_SIMPLEX:
      std::cerr<<"Iterations: "<< intinf[MSK_IINF_SIM_PRIMAL_ITER];
      std::cerr<<"  Elapsed time: "<<douinf[MSK_DINF_OPTIMIZER_TIME];
      std::cerr<<"("<<douinf[MSK_DINF_SIM_TIME]<<")\n";
      std::cerr<<"Obj.: "<< douinf[MSK_DINF_SIM_OBJ]<<std::endl;
      break;
    case MSK_CALLBACK_END_PRIMAL_SIMPLEX:
      std::cerr<<"Primal simplex optimizer finished.\n";
      break;
    case MSK_CALLBACK_BEGIN_DUAL_SIMPLEX:
      std::cerr<<"Dual simplex optimizer started.\n";
      break;
    case MSK_CALLBACK_UPDATE_DUAL_SIMPLEX:
      std::cerr<<"Iterations: "<<intinf[MSK_IINF_SIM_DUAL_ITER];
      std::cerr<<"  Elapsed time: "<<douinf[MSK_DINF_OPTIMIZER_TIME];
      std::cerr<<"("<<douinf[MSK_DINF_SIM_TIME]<<")\n";
      std::cerr<<"Obj.: "<<douinf[MSK_DINF_SIM_OBJ]<<std::endl;
      break;
    case MSK_CALLBACK_END_DUAL_SIMPLEX:
      std::cerr<<"Dual simplex optimizer finished.\n";
      break;
    case MSK_CALLBACK_BEGIN_BI:
      std::cerr<<"Basis identification started.\n";
      break;
    case MSK_CALLBACK_END_BI:
      std::cerr<<"Basis identification finished.\n";
      break;
  default:
    break;
  }
  if ( douinf[MSK_DINF_OPTIMIZER_TIME]>=maxtime)
  {
    std::cerr<<"MOSEK is spending too much time.Terminate it.\n";
    mod->breakSolver();
  }
  
} /* usercallback */

int main(int argc, char ** argv)
{

  std::string slvr("intpnt");
  
  if (argc < 1)
  {
    std::cerr<< "Usage: ( psim | dsim | intpnt ) \n";
  }

  if (argc >= 1) slvr = argv[0];

  auto A1 = new_array_ptr<double,1>({ 3.0, 2.0, 0.0, 1.0 });
  auto A2 = new_array_ptr<double,1>({ 2.0, 3.0, 1.0, 1.0 });
  auto A3 = new_array_ptr<double,1>({ 0.0, 0.0, 3.0, 2.0 });
  auto c  = new_array_ptr<double,1>({ 3.0, 5.0, 1.0, 1.0 });

  Model::t M = new Model("lo1"); auto _M = finally([&]() { M->dispose(); });

  Variable::t x = M->variable("x", 3, Domain::greaterThan(0.0));
  Variable::t y = M->variable("y", 1, Domain::inRange(0.0, 10.0));
  Variable::t z = Var::vstack(x,y);
  M->constraint("c1", Expr::dot(A1, z), Domain::equalsTo(30.0));
  M->constraint("c2", Expr::dot(A2, z), Domain::greaterThan(15.0));
  M->constraint("c3", Expr::dot(A3, z), Domain::lessThan(25.0));

  M->objective("obj", ObjectiveSense::Maximize, Expr::dot(c, z));


  if( slvr == "psim") 
    M->setSolverParam("optimizer", "primal_simplex");
  else if( slvr == "dsim")
    M->setSolverParam("optimizer", "dual_simplex");
  else if( slvr == "intpnt")
    M->setSolverParam("optimizer", "intpnt");

  double maxtime = 0.01;

  //TAG:begin-callback-handler
  std::function<void (MSKcallbackcodee, const double *, const int32_t *, const int64_t*)> cllbck = [&]( MSKcallbackcodee caller,
                                                                                                        const double   * douinf,
                                                                                                        const int32_t  * intinf,
                                                                                                        const int64_t  * lintinf)
    {
      usercallback(caller,douinf,intinf,lintinf,M,maxtime);
    } ;
  
  
  M->setCallbackHandler(cllbck);

  //TAG:end-callback-handler

  M->setSolverParam("log", 0);
  
  M->solve();
}





