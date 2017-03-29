//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para resolver un sistema lineal usando factorizacion Choleski                      //
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


#include "ResuelveFactorizacionCholeskiBandDisp.hpp"
#include <math.h>


// Factoriza la matriz A en L dejandolo en la misma matriz
void ResuelveFactorizacionCholeskiBandDisp::factoriza(void)
{
#ifdef DEPURAR
   if (!M->matrizCuadrada())
   {
      printf("\nError al factorizar por Choleski, matriz no cuadrada\n\n");
      exit(1);
   }
#endif

   int i, j, k, xcol1, ind1, nr = M->renglones()-1;
   ldouble m, n, t;

   //~ // S hace ceros la matriz triangular superior
   //~ for (i = 0; i <= nr; i++)
   //~ {
   //~ xcol1 = M->retornaNumeroColumnasBanda(i);
   //~ for (ind1 = 0; ind1 < xcol1; ind1++)
   //~ {
   //~ j = M->retornaNumeroColumna(i,ind1);
   //~ if (j < i+1) continue;
   //~ M->asigna(i, j, 0.0);
   //~ }
   //~ }

   m = sqrt(M->retorna(0,0));
#ifdef DEPURAR
   if (m == 0.0)
   {
      printf("\nError al factorizar el sistema en L\n");
      exit(1);
   }
#endif
   M->asigna(0,0,m);
   for (j = 1; j <= nr; j++) M->asigna(j, 0, M->retorna(j,0) / m);
   for (i = 1; i < nr; i++)
   {
      m = 0.0;

      xcol1 = M->retornaNumeroColumnasBanda(i);
      for (ind1 = 0; ind1 < xcol1; ind1++)
      {
         j = M->retornaNumeroColumna(i,ind1);
         if (j > i-1) continue;
         t = M->retornaValorColumna(i,ind1);
         m += t * t;
      }
      n = sqrt(M->retorna(i,i) - m);
      M->asigna(i,i,n);

      for (j = i+1; j <= nr; j++)
      {
         m = 0.0;
         xcol1 = M->retornaNumeroColumnasBanda(j);
         for (ind1 = 0; ind1 < xcol1; ind1++)
         {
            k = M->retornaNumeroColumna(j,ind1);
            if (k > i-1) continue;
            m += (M->retornaValorColumna(j,ind1) * M->retorna(i,k));
         }
#ifdef DEPURAR
         if (M->retorna(i,i) == 0.0)
         {
            printf("\nError al factorizar el sistema en L\n");
            exit(1);
         }
#endif
         n = (M->retorna(j,i) - m) / M->retorna(i,i);
         M->asigna(j,i,n);
      }
   }
   m = 0.0;
   for (k = 0; k < nr; k++)
   {
      t = M->retorna(nr,k);
      m += t * t;
   }
   n = sqrt(M->retorna(nr,nr) - m);
   M->asigna(nr,nr,n);

   // Si se requiere puede llenarse la L traspuesta
   //~ for (i = 0; i <= nr; i++)
   //~ {
   //~ for (j = i+1; j <= nr; j++) M->asigna(i, j, M->retorna(j,i));
   //~ }

   MatrizFactorizada = true;
}

// Resuelve el sistema lineal
void ResuelveFactorizacionCholeskiBandDisp::resuelve(void)
{
   if (!MatrizFactorizada) factoriza();

   int i, j, n, ind, xcol;
   ldouble t, s;
   n = M->renglones();

   Vector *y = new Vector(n);
   t = B->retorna(0) / M->retorna(0,0);
   y->asigna(0, t);
   for (i = 1; i < n; i++)
   {
      t = 0.0;
      xcol = M->retornaNumeroColumnasBanda(i);
      for (ind = 0; ind < xcol ; ind++)
      {
         j = M->retornaNumeroColumna(i,ind);
         if (j >= i) continue;
         t += M->retornaValorColumna(i,ind) * y->retorna(j);
      }
      s = (B->retorna(i) - t) / M->retorna(i,i);
      y->asigna(i,s);
   }
   t = y->retorna(n-1) / M->retorna(n-1,n-1);
   X->asigna(n-1,t);
   for (i = n-2; i >= 0; i--)
   {
      t = 0.0;
      for (j = i+1; j < n; j++)
      {
         t += M->retorna(j,i) * X->retorna(j);
      }
      s = (y->retorna(i) - t) / M->retorna(i,i);
      X->asigna(i,s);
   }
   delete y;
}
