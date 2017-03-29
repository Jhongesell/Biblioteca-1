//////////////////////////////////////////////////////////////////////////////////////////////
// Programa para usar la clase de matriz bandada                                            //
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
#include "MatrizDispersaComp.hpp"



int main(void)
{
   int i, j, inc = 100000;
   ldouble a=0;             // Inicio dominio
   ldouble c=1;             // Fin dominio

   for (i=inc; i <= inc*30; i+=inc)
   {
      printf("\n\nMatriz de %dx%d\n",i,i);
      MatrizDispersaComp *A = new MatrizDispersaComp(i,i,3,"A");
      
      ldouble h=(c-a)/(i-1);   // Incremento en la malla
      ldouble P=2/(h*h);
      ldouble Q=-1/(h*h)+1/(2*h);
      ldouble R=-1/(h*h)-1/(2*h);
      
      // LLena la matriz
      A->asigna(0,0,P);
      A->asigna(0,1,Q);
      for(j=1;j < i-1;j++) 
      {
        A->asigna(j,j-1,R);
        A->asigna(j,j,P);
        A->asigna(j,j+1,Q);
      }
      A->asigna(i-1,i-2,R);
      A->asigna(i-1,i-1,P);
      //A->visualizaMatricesInternas();
      //A->visualiza(0);
      
      delete A;
   }
   
   
   return 0;
}
