#include <random>
#include <iostream>
#include "fusion.h"
#include "mosek.h"

using namespace mosek::fusion;
using namespace monty;

int main(int argc, char ** argv)
{       
  //TAG:begin-input-data
  // problem dimensions
  int n = 50;
  int m= 2*n;

  MSKenv_t env = NULL;

  if( MSK_makeenv(&env,NULL) != MSK_RES_OK) return -1;
   
  // problem data
  std::default_random_engine generator; 

  auto xs= std::shared_ptr<ndarray<double,1> >(new ndarray<double,1>(n) );

  std::uniform_real_distribution<double> unif_distr(0.,1.);
  std::generate(xs->begin(), xs->end(), std::bind(unif_distr, generator));

  auto A= std::shared_ptr<ndarray<double,1> >(new ndarray<double,1>(n*m) );

  std::normal_distribution<double> normal_distr;
  std::generate(A->begin(), A->end(), std::bind(normal_distr, generator));

  auto P= std::shared_ptr<ndarray<double,1> >(new ndarray<double,1>(n*n) );
    
  MSK_syrk(
    env,
    MSK_UPLO_LO,
    MSK_TRANSPOSE_NO,
    n,m,1.0, A->raw(), 0.0, P->raw());
  
  //must fill P upper triangular
  for(int j=0;j<n;j++)
    for(int i=j+1;i<n;i++)
      (*P)[j*n+i] = (*P)[i*n+j];

  auto q= std::shared_ptr<ndarray<double,1> >(new ndarray<double,1>(n) );
  MSK_gemv(  
    env,
    MSK_TRANSPOSE_NO,
    n, n,  
    -1.0,  
    (*P).raw(),  
    xs->raw(),  
    0.0,  
    (*q).raw());
  //TAG:end-input-data
  //TAG:begin-code
  //TAG:begin-model  
  Model::t M = new Model(); auto _M = finally([&]() {M->dispose();} );
  //TAG:end-model  

  //TAG:begin-vars
  auto Z = M->variable(n+1, Domain::inPSDCone());
      
  auto X= Z->slice(new_array_ptr<int,1>({0,0}),new_array_ptr<int,1>({n,n}) );
  auto x= Z->slice(new_array_ptr<int,1>({0,n}),new_array_ptr<int,1>({n,n+1}));
  //TAG:end-vars
  //TAG:begin-constr
  M->constraint( Expr::sub(X->diag(),x), Domain::greaterThan(0.0) );
      
  M->constraint( Z->index(n,n), Domain::equalsTo(1.0));
  //TAG:end-constr
  //TAG:begin-obj-fun
  M->objective( ObjectiveSense::Minimize, Expr::add( Expr::sum(Expr::mulDiag( Matrix::dense(n,n,P), X ) ), Expr::mul(2.0, Expr::dot( x, q) ) ) );
  //TAG:end-obj-fun
  
  M->solve();
  //TAG:end-code
  MSK_deleteenv(&env);
  
  return 0;
}

