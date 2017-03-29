//////////////////////////////////////////////////////////////////////////////////////////////
// Programa para usar la clase de matriz densa                                              //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.igeofcu.unam.mx                                                    //
// Página:   http://www.mmc.igeofcu.unam.mx/acl                                             //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los términos de la Licencia Pública General de GNU según es                         //
// publicada por la Free Software Foundation, bien de la versión 2 de                       //
// dicha Licencia o bien (según su elección) de cualquier versión                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea útil, pero SIN                   //
// NINGUNA GARANTÍA, incluso sin la garantía MERCANTIL implícita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROPÓSITO PARTICULAR. Véase la                        //
// Licencia Pública General de GNU para más detalles.                                       //
//                                                                                          //
// Debería haber recibido una copia de la Licencia Pública General junto                    //
// con este programa. Si no ha sido así, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////



#include "Definiciones.hpp"
#include "MatrizDensa.hpp"


int main(void)
{
   int i;

   const int TAM = 5;
   ldouble A[][TAM] = {
     {0.2,0.1,1.0,1.0,0.0},
     {0.1,4.0,-1.0,1.0, -1.0},
     {1.0,-1.0,60.0,0.0,-2.0},
     {1.0,1.0,0.0,8.0,4.0},
     {0.0,-1.0,-2.0,4.0,700.0}
   }; 

   MatrizDensa b(100,100,"B");
   
   MatrizDensa *a = new MatrizDensa(TAM,TAM,"A");
   for (i = 0; i < TAM; i++) a->convierte(A[i],i,TAM);
   a->visualiza(0);
   
   b.redimensiona(TAM,TAM);
   a->copia(&b);
   b.visualiza(0);
   
   printf("\n%lf\n",b(0,0));
   
   MatrizDensa c(b);
   c.visualiza(0);
   
   delete a;

   return 0;
}
