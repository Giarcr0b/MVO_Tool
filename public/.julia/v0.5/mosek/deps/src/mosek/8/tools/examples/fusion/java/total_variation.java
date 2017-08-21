package com.mosek.fusion.examples;
import java.util.Random;
import mosek.fusion.*;


public class total_variation
{


  public static void main(String[] args)
    throws SolutionError
    {
      int ncols = 50;
      int nrows = 50;
      int seed  =  0;
      double sigma = 1.0;

      int ncells = nrows*ncols;

      Random randGen = new Random(seed);

      double [] f= new double[ncells];

      for(int i=0;i<ncells;i++)
        f[i] = Math.max( Math.min(1.0, randGen.nextDouble() + randGen.nextGaussian()*sigma),.0);
	    
      //TAG:begin-tv-code
      
      //TAG:begin-tv-init
      Model M = new Model("TV");
      try
      {

        Variable u= M.variable(new int[]{nrows+1,ncols+1}, Domain.inRange(0.,1.0));
        Variable t= M.variable(new int[]{nrows,ncols}, Domain.unbounded());
        //TAG:end-tv-init
  
        //TAG:begin-tv-core-grid
        Variable ucore=  u.slice(new int[]{0,0}, new int[]{nrows,ncols});
        //TAG:end-tv-core-grid

        //TAG:begin-tv-deltas
        Expression deltax= Expr.sub( u.slice( new int[]{1,0} , new int[]{nrows+1,ncols} ), ucore );
        Expression deltay= Expr.sub( u.slice( new int[]{0,1} , new int[]{nrows,ncols+1} ), ucore );
        //TAG:end-tv-deltas

        //TAG:begin-tv-norms
        M.constraint( Expr.stack(2, t, deltax, deltay ), Domain.inQCone().axis(2) );
        //TAG:end-tv-norms

        //TAG:begin-tv-sigma
        M.constraint(Expr.vstack(sigma, Expr.flatten( Expr.sub( Matrix.dense(nrows,ncols,f),  ucore ) ) ),  
                     Domain.inQCone());
        //TAG:end-tv-sigma

        /* boundary conditions are not actually needed
           M.constraint( Expr.sub( u.slice( [n-1,0] ,[n,m] ), u.slice([n,0],[n+1,m]) ), Domain.equalsTo(0.));
           M.constraint( Expr.sub( u.slice( [0,n-1] ,[n,m] ), u.slice([0,n],[n,m+1]) ), Domain.equalsTo(0.));
        */

        //TAG:begin-tv-obj-fun
        M.objective(ObjectiveSense.Minimize, Expr.sum(t) );
        //TAG:end-tv-obj-fun
        
        M.setLogHandler(new java.io.PrintWriter(System.out));      
        M.solve();
      }
      finally
      {
        M.dispose();
      }
      //TAG:end-tv-code
    }
  
}
