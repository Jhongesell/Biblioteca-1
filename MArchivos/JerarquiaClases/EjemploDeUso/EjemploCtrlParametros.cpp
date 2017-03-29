#include <stdio.h>
#include "CtrlParametros.hpp"


int main(int argc, const char *args[]) 
{
   
   CtrlParametros parm(argc, args);
   parm.visualiza();
   
   int i;
   ldouble d;
   i = parm.intVal("m",3);
   d = parm.doubleVal("r",3.09);
   printf("\n int %d double %f",i,d);

   printf("\n Busca f encontro = %d",parm.busca("f"));

   
   i = parm.intVal("n");
   d = parm.doubleVal("r");
   printf("\n int %d double %f\n",i,d);
   
   return 0;
}
