/*
  Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.

  File:      parameters.cs

 Purpose: Demonstrates a very simple example about how to get/set
 parameters with MOSEK .NET API

*/

using System;
 
public class parameters
{

    public static void Main()
    {
        using (mosek.Env env = new mosek.Env())
        {

            using (mosek.Task task = new mosek.Task(env, 0, 0))
            {

                int param;

                Console.WriteLine("Test MOSEK parameter get/set functions");

                param = task.getintparam(mosek.iparam.log);
                Console.WriteLine("Default value for parameter task.ipar.log= " + param);

                Console.WriteLine(" setting to 1 using putintparam...");
                task.putintparam(mosek.iparam.log, 1);


                Console.WriteLine(" setting to -1 using putintparam...");
                try
                {
                    task.putintparam(mosek.iparam.log, -1);
                }
                catch (mosek.Error e)
                {
                    Console.WriteLine(" -1 rejected as not a valid value");
                }


                Console.WriteLine(" setting to 2 using putparam...");
                task.putparam("MSK_IPAR_LOG", "2");

                Console.WriteLine(" setting to 3 using putnaintparam...");
                task.putnaintparam("MSK_IPAR_LOG", 3);


                Console.WriteLine(" selecting the dual simplex algorithm...");
                task.putintparam(mosek.iparam.optimizer, mosek.optimizertype.dual_simplex);

            }
        }
    }
}
