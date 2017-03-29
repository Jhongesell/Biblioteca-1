//////////////////////////////////////////////////////////////////////////////////////////////
// Programa para integrar una funcion mediante la cuadratura Gauss-Legendre usando de       //
// 2 a 10 puntos                                                                            //
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




#include <stdio.h>
#include "GaussQuad.hpp"
#include "Ctrl_vis.hpp"


// Funcion Principal para mostrar el uso de la integracion por cuadratura Gauss-Legendre
int main(void)
{
   //Se usan 8 puntos de cuadratura
   int k, PUNTOS_INTEGRAR = 8;
   ldouble PX[PUNTOS_INTEGRAR];
   ldouble FX[PUNTOS_INTEGRAR];

   GaussQuad integ(-1.0,1.0,PUNTOS_INTEGRAR,PX);
   Ctrl_visualizacion a;

   // Integral en una dimension
   for (k = 0; k < PUNTOS_INTEGRAR; k++) FX[k] = PX[k]*PX[k] + 3.0*PX[k] + 7.0;
   printf("El resultado es");
   a.visualiza_n(integ.integra(FX));
   printf(", debe de ser 14.666667\n");



   // Integral en dos dimensiones
   ldouble WX[PUNTOS_INTEGRAR];
   GaussQuad in(-1.0,1.0,PUNTOS_INTEGRAR,PX,WX);
   int j, i;
   ldouble x = 0.0;
   for (i = 0; i < PUNTOS_INTEGRAR; i++)
   {
      for (j = 0; j < PUNTOS_INTEGRAR; j++)
      {
         x += WX[i]*WX[j]*( (PX[j]*PX[j]*PX[j]-1.0)*((PX[i]-1.0)*(PX[i]-1.0)) );
      }
   }
   printf("el resultado es");
   a.visualiza_n(x);
   printf(", debe de ser -5.333333\n");




   // Integral en tres dimensiones
   x = 0.0;
   for (i = 0; i < PUNTOS_INTEGRAR; i++)
   {
      for (j = 0; j < PUNTOS_INTEGRAR; j++)
      {
         for (k = 0; k < PUNTOS_INTEGRAR; k++)
         {
            x += WX[i]*WX[j]*WX[k]*( (PX[k]*PX[k])*(PX[j]*PX[j]-1.0)*(PX[i]*PX[i]*PX[i]*PX[i]-2.0) );
         }
      }
   }


   printf("el resultado es");
   a.visualiza_n(x);
   printf(", debe de ser 3.2\n");

}
