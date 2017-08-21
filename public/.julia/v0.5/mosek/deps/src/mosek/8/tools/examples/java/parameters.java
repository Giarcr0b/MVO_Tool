/* 
   Copyright : Copyright (c) MOSEK ApS, Denmark. All rights reserved.

   File :      parameters.java

   Purpose :   Demonstrates a very simple example about how to get/set
               parameters with MOSEK Java API
*/

package com.mosek.example;
import mosek.*;
 
public class parameters
{

  public static void main (String[] args)
    {
      try
      {
        mosek.Env  env = new Env(); 
        mosek.Task task = new Task(env,0,0);
        
        int param;
        
        System.out.println("Test MOSEK parameter get/set functions");
        
        param= task.getintparam(mosek.iparam.log);
        System.out.println("Default value for parameter task.ipar.log= "+ param);
      
        System.out.println(" setting to 1 using putintparam...");
        task.putintparam(mosek.iparam.log,1);

      
        System.out.println(" setting to -1 using putintparam...");
        try
        {
          task.putintparam(mosek.iparam.log, -1);
        }
        catch(mosek.Error e)
        {
            System.out.println(" -1 rejected as not a valid value"); 
        }
        
        
        System.out.println(" setting to 2 using putparam...");
        task.putparam("MSK_IPAR_LOG","2");
        
        System.out.println(" setting to 3 using putnaintparam...");
           task.putnaintparam("MSK_IPAR_LOG",3);

  
           System.out.println(" selecting the dual simplex algorithm...");
           task.putintparam( mosek.iparam.optimizer, mosek.optimizertype.dual_simplex.value);

           
      }
      catch (mosek.Exception e)
      {
        System.out.println ("An error/warning was encountered");
        System.out.println (e.toString());
        throw e;
      }
      
    }
}
