//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema lineal mediante CGM                                       //
//                                                                                          //
// Análisis y Diseño y Programación:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.geofisica.unam.mx                                                  //
// Página:   http://www.mmc.geofisica.unam.mx/acl                                           //
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


#include <math.h>
#include "ResuelveCGMPrecondicionadoBandDisp.hpp"
#include "MatrizDensa.hpp"



// Resuelve el sistema lineal
void ResuelveCGMPrecondicionadoBandDisp::resuelve(void)
{
#ifdef DEPURAR
   if (!M->matrizCuadrada() || !C->matrizCuadrada())
   {
      printf("\nError al resolver por gradiente conjugado, matriz no cuadrada\n\n");
      exit(1);
   }
#endif

   int i,  col;
   ldouble alfa, gama, beta, t, s;

   // Numero de columnas
   col = M->columnas();

   // Revisa si el vector B es identicamente Cero, en ese caso X es identicamente Cero
   if (B->esVectorCero())
   {
      X->inicializa(0.0);
      return;
   }


   // Solicitud de matrices de trabajo
   Vector *r = new Vector(col);
   Vector *w = new Vector(col);
   Vector *v = new Vector(col);
   Vector *u = new Vector(col);
   Vector *xx = new Vector(col);
   if (!r || !w || !v || !v || !u || !xx)
   {
      printf("\nError resolver por Gradiente Conjugado, no hay memoria\n\n");
      exit(1);
   }

   // Precondicionador por omisión es la identidada
   MatrizDensa *CT = new MatrizDensa(i,i,"CT");
   if (!CT)
   {
      printf("\nError resolver por Gradiente Conjugado, no hay memoria\n\n");
      exit(1);
   }

   // C inversa transpuesta
   CT->transpuesta(C);


   // Calculo de r
   M->multiplica(X,xx);
   r->resta(B,xx);

   //~ w->Multiplica(C,r);
   C->multiplica(r,w);
   //~ v->Multiplica(CT,w);
   CT->multiplica(w,v);

   // Calculo de alfa
   alfa = w->productoPunto();

   // Iteracion para encontrar la solución
   for (NumIteraciones = 1; NumIteraciones < Iter; NumIteraciones++)
   {
      // Claculo de u
      M->multiplica(v,u);

      // Calculo de t
      gama = v->productoPunto(u);
      t = alfa / gama;

      // Calculo de x la solución
      v->copia(xx);
      xx->multiplica(t);
      X->suma(xx);
      //~ if (Visualiza != 0) X->Visualiza(1);

      // Calculo de r
      u->copia(xx);
      xx->multiplica(t);
      r->resta(xx);

      // Calculo de w
      C->multiplica(r,w);

      // Calculo de beta
      beta = w->productoPunto();
      s = beta / alfa;

      // Revisa si ya se tiene la tolerancia minima en beta y r para terminar las iteraciones
#ifdef __Double__
      if (fabs(beta) < Ep)
#else
      if (fabsl(beta) < Ep)
#endif
      {
         if (r->esCadaEntradaMasPequeno(Ep)) break;
      }

      // Calculo de v
      CT->multiplica(w,xx);
      v->multiplica(s);
      v->suma(xx);

      // Actualizacion de alfa
      alfa = beta;

      // Revisa si ya se tiene la tolerancia minima en v para terminar las iteraciones
      if (v->esCadaEntradaMasPequeno(Ep)) break;
   }

   // Borra las matrices de trabajo
   delete xx;
   delete u;
   delete v;
   delete w;
   delete r;
   delete CT;
}
