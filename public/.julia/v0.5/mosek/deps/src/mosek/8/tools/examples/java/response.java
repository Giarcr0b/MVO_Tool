/* 
   Copyright : Copyright (c) MOSEK ApS, Denmark. All rights reserved.

   File :      response.java

   Purpose :   This examples demonstrates proper response handling.
*/
package com.mosek.example;
import mosek.*;

public class response
{
  public static void main(String[] argv)
  {
    if (argv.length < 1)
    {
      System.out.println("No input file specified");
    }
    else
    {

      try (Env  env  = new Env();
           Task task = new Task(env,0,0))
      {
        // Directs the log task stream to the user specified
        // method task_msg_obj.stream
        task.set_Stream(
          streamtype.log,
          new mosek.Stream() 
            { public void stream(String msg) { System.out.print(msg); }});

        task.readdata(argv[0]);

        rescode trm = task.optimize();

        solsta[] solsta = new solsta[1]; task.getsolsta(soltype.itr,solsta);
        switch( solsta[0] )
        {
          case optimal:   
          case near_optimal:
            System.out.println("An optimal basic solution is located.");

            task.solutionsummary(streamtype.msg);
            break;
          case dual_infeas_cer:
          case near_dual_infeas_cer:
            System.out.println("Dual infeasibility certificate found.");
            break;
          case prim_infeas_cer:
          case near_prim_infeas_cer:
            System.out.println("Primal infeasibility certificate found.");
            break;
          case unknown:
          {
            StringBuffer symname = new StringBuffer();
            StringBuffer desc = new StringBuffer();

            /* The solutions status is unknown. The termination code 
               indicating why the optimizer terminated prematurely. */

            System.out.println("The solution status is unknown.");
            /* No system failure e.g. an iteration limit is reached.  */

            Env.getcodedesc(trm,symname,desc);
            System.out.printf("  Termination code: %s\n",symname);
            break;
          }
          default:
            System.out.println("An unexpected solution status is obtained.");
            break;
        }
      }
    }
  }
}

