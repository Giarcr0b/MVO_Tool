/*
  Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.

  File:      parameters.c

 Purpose: Demonstrates a very simple example about how to get/set
 parameters with MOSEK C API
*/

#include "mosek.h"
#include "stdio.h"

int main()
{

  MSKenv_t env = NULL;  
  MSKtask_t task = NULL;  
  MSKrescodee res;  

  int param=0;
  
  /* Create an environment */  
  res = MSK_makeenv(&env, NULL);  
  
  if (res == MSK_RES_OK)  
  {
      /* Create a task */  
    res = MSK_maketask(env, 0,0, &task);  
    
    if( res == MSK_RES_OK)
    {
      puts("Test MOSEK parameter get/set functions");

      res = MSK_getintparam(task, MSK_IPAR_LOG, &param);
      printf("Default value for parameter MSK_IPAR_LOG= %d\n", param);
    
      puts(" setting to 1 using putintparam...");
      res = MSK_putintparam(task, MSK_IPAR_LOG,1);
    
      puts(" setting to -1 using putintparam...");
      res = MSK_putintparam(task, MSK_IPAR_LOG, -1);
      if( res != MSK_RES_OK) puts(" -1 rejected: not a valid value!"); 
    
      puts(" setting to 2 using putparam...");
      res = MSK_putparam(task,"MSK_IPAR_LOG","2");
      
      puts(" setting to 3 using putnaintparam...");
      MSK_putnaintparam(task,"MSK_IPAR_LOG",3);

      puts(" selecting the dual simplex algorithm...");
      res = MSK_putintparam(task, MSK_IPAR_OPTIMIZER, MSK_OPTIMIZER_DUAL_SIMPLEX);

      MSK_deletetask(&task);  
    }
    MSK_deleteenv(&env);  
  }
  return 0;
}
