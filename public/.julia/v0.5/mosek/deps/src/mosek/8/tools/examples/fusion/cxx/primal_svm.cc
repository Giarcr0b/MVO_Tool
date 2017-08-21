#include <random>
#include <memory>
#include <iostream>
#include <iterator>
#include <iomanip>

#include "fusion.h"

using namespace mosek::fusion;
using namespace monty;

int main(int argc, char ** argv)
{
  //TAG:begin-svm-random-data
  int m = 50 ;
  int n = 3;
  int nc =10;

  int nump= m/2;
  int numm= m - nump;

  auto y = new_array_ptr<double,1> (m);
  std::fill( y->begin(), y->begin()+nump,1.);
  std::fill( y->begin()+nump, y->end(),-1.);
  
  double mean = 1.;
  double var = 1.;

  auto X= std::shared_ptr< ndarray<double,2> > (  new ndarray<double,2> ( shape_t<2>(m,n) ) );

  std::mt19937 e2(0);
  
  for(int i=0;i<nump;i++)
  {
    auto ram = std::bind(std::normal_distribution<>(mean, var), e2);
    for( int j=0; j< n;j++)
      (*X)(i,j) = ram();
  }

  std::cout<< "Number of data    : " << m<< std::endl;
  std::cout<< "Number of features: " << n<< std::endl;
  //TAG:end-svm-random-data
  //TAG:begin-svm-code
  //TAG:begin-svm-model
  Model::t M = new Model("primal SVM"); auto _M = finally([&]() { M->dispose(); });
  //TAG:end-svm-model

  //TAG:begin-svm-vars
  Variable::t w  =  M->variable( n, Domain::unbounded());
  Variable::t t  =  M->variable( 1, Domain::unbounded());
  Variable::t b  =  M->variable( 1, Domain::unbounded());
  Variable::t xi =  M->variable( m, Domain::greaterThan(0.));
  //TAG:end-svm-vars

  //TAG:begin-svm-classification-constr 
  auto ex = Expr::sub( Expr::mul(X,w), Var::repeat(b,m) );
  M->constraint( Expr::add(Expr::mulElm( y, ex ), xi ) , Domain::greaterThan( 1. ) );
  //TAG:end-svm-classification-constr

  //TAG:begin-svm-cone
  M->constraint( Expr::vstack( 1., t, w) , Domain::inRotatedQCone());
  //TAG:end-svm-cone
  M->acceptedSolutionStatus(AccSolutionStatus::NearOptimal);


  //TAG:begin-svm-obj-fun-loop
  std::cout<< "   c   | b      | w\n";
  for(int i=0; i<nc;i++)
  {
    double c= 500.0 *i;
    //TAG:begin-svm-obj-fun
    M->objective(ObjectiveSense::Minimize, Expr::add( t, Expr::mul(c, Expr::sum(xi) ) ) );
    //TAG:end-svm-obj-fun
    M->solve();
    
    try
    {
      std::cout<< std::setw(6)<<c<< " | "<< std::setw(8)<< (*(b->level())) [0]<<" | ";
      std::cout.width(8);
      auto wlev = w->level();
      std::copy( wlev->begin(), wlev->end() , std::ostream_iterator<double>(std::cout," ") );
      std::cout<<"\n";
    }
    catch(...){}
               
  }
  //TAG:end-svm-obj-fun-loop
  //TAG:end-svm-code
  return 0;
}


