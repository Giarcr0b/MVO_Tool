/* 
   Copyright : Copyright (c) MOSEK ApS, Denmark. All rights reserved.

   File :      case_portfolio_1.java

   Purpose :   Implements a basic portfolio optimization model.
*/
package com.mosek.example;

public class case_portfolio_1
{
    static final int n = 3;

    public static void main (String[] args)
    {
        // Since the value infinity is never used, we define
        // 'infinity' symbolic purposes only
        double infinity = 0;
        double gamma = 0.05;
        double[]   mu = {0.1073,  0.0737,  0.0627};
        double[][] GT={
            {0.1667,  0.0232,  0.0013},
            {0.0000,  0.1033, -0.0022},
            {0.0000,  0.0000,  0.0338}
        };
        double[] x0 = {0.0, 0.0, 0.0};
        double   w = 1.0;

        int numvar = 2*n +1;
        int numcon = n+1;


        //Offset of variables into the API variable.  
        int offsetx = 0;
        int offsets = n;
        int offsett = n+1;
        
        try ( mosek.Env env   = new mosek.Env ();          
              mosek.Task task = new mosek.Task (env, 0, 0) )
            {
                // Directs the log task stream to the user specified
                // method task_msg_obj.stream
                task.set_Stream(
                                mosek.streamtype.log,
                                new mosek.Stream() 
                                { public void stream(String msg) { System.out.print(msg); }});


                //Constraints.
                task.appendcons(numcon);
                for( int i=1; i<=n; ++i)
                    {
                        w+=x0[i-1];
                        task.putconbound(i, mosek.boundkey.fx, 0.,0.);
                        task.putconname(i,"GT["+i+"]");
                    }
                task.putconbound(0, mosek.boundkey.fx,w,w);
                task.putconname(0,"budget");

                //Variables.
                task.appendvars(numvar);

                int[] xindx={offsetx+0,offsetx+1,offsetx+2};
                task.putclist(xindx,mu);

                for( int i=0; i<n; ++i)
                    {
                        for( int j=i; j<n;++j)
                            task.putaij(i+1,offsetx+j, GT[i][j]); 

                        task.putaij(i+1, offsett+i,-1.0);

                        task.putvarbound(offsetx+i, mosek.boundkey.lo,0.,0.);

                        task.putvarname(offsetx+i,"x["+(i+1)+"]");
                        task.putvarname(offsett+i,"t["+(i+1)+"]");
                        task.putvarbound(offsett+i, mosek.boundkey.fr,0.,0.);
                    }
                task.putvarbound(offsets, mosek.boundkey.fx,gamma,gamma);
                task.putvarname(offsets,"s");

                double[] e={1.0,1.0,1.0};
                task.putarow(0,xindx,e);

                //Cones.
                int[] csub = {offsets,offsett+0,offsett+1,offsett+2};
                task.appendcone( mosek.conetype.quad, 
                                 0.0, /* For future use only, can be set to 0.0 */
                                 csub);
                task.putconename(0,"stddev");

                /* A maximization problem */ 
                task.putobjsense(mosek.objsense.maximize);

                //task.solutionsummary(mosek.streamtype.log);

                //task.writedata("dump.opf");

                /* Solve the problem */
                try
                    {

                        task.optimize();


                        double expret=0.0,stddev=0.0;
                        double[] xx = new double[numvar];

                        task.getxx(mosek.soltype.itr,xx);

                        for(int j=0; j<n; ++j)  
                            expret += mu[j]*xx[j+offsetx];

                        System.out.printf("\nExpected return %e for gamma %e\n",expret, xx[offsets]); 
    
                    }
                catch (mosek.Warning mw)
                    {
                        System.out.println (" Mosek warning:");
                        System.out.println (mw.toString ());
                    }
            }
        catch( mosek.Exception e)
            {
                System.out.println ("An error/warning was encountered"); 
                System.out.println (e.toString ());
                throw e;
            }
    }
}
