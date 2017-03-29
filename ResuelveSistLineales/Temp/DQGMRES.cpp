//////////////////////////////////////////////////////////////////////////////////////////////
// Clase implementar DQGMRES con matrices bandadas o dispersas                              //
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




#include "DQGMRES.hpp"
#include <math.h>
#include <stdlib.h>


void DQGMRES::inicializa(void)
{
   int i,j;
   k1 = k + 1;

   p = new double *[k1];
   if (p == NULL)
   {
      printf("\nError al solicitar memoria\n");
      exit(1);
   }
   for (i = 0; i < k1; i++)
   {
      p[i] = new double[n];
      if (p[i] == NULL)
      {
         printf("\nError al solicitar memoria\n");
         exit(1);
      }
   }
   for (i = 0; i < k1; i++)
      for (j = 0; j < n; j++) p[i][j] = 0.0;


   cs = new double *[k1];
   if (cs == NULL)
   {
      printf("\nError al solicitar memoria\n");
      exit(1);
   }
   for (i = 0; i < k1; i++)
   {
      cs[i] = new double[2];
      if (cs[i] == NULL)
      {
         printf("\nError al solicitar memoria\n");
         exit(1);
      }
   }
   for (i = 0; i < k1; i++)
      for (j = 0; j < 2; j++) cs[i][j] = 0.0;

   h = new double *[k1+1];
   if (h == NULL)
   {
      printf("\nError al solicitar memoria\n");
      exit(1);
   }
   for (i = 0; i < (k1+1); i++)
   {
      h[i] = new double[k1];
      if (h[i] == NULL)
      {
         printf("\nError al solicitar memoria\n");
         exit(1);
      }
   }
   for (i = 0; i < (k1+1); i++)
      for (j = 0; j < k1; j++) h[i][j] = 0.0;

   q = new double *[k1+1];
   if (q == NULL)
   {
      printf("\nError al solicitar memoria\n");
      exit(1);
   }
   for (i = 0; i < (k1+1); i++)
   {
      q[i] = new double[n];
      if (q[i] == NULL)
      {
         printf("\nError al solicitar memoria\n");
         exit(1);
      }
   }
   for (i = 0; i < (k1+1); i++)
      for (j = 0; j < n; j++) q[i][j] = 0.0;

   v = new double [n];
   for (i = 0; i < n; i++) v[i] = 0.0;
}


void DQGMRES::applyOmega(int m)
{
   int i, i1, m1 = m % k1;
   double z1, z2;
   for (i = (m - k < 0 ? 0 : m - k); i < m; i++)
   {
      i1 = i % k1;
      z1 = cs[i1][0]*h[i1][m1] + cs[i1][1]*h[i1 + 1][m1];
      z2 = -cs[i1][1]*h[i1][m1] + cs[i1][0]*h[i1 + 1][m1];
      h[i1][m1] = z1;
      h[i1 + 1][m1] = z2;
   }
}



void DQGMRES::solve(Vector *x, Vector *b)
{
   int i, i1, j, j1, m, m1=0;
   double val;
   gm = 0.0;
   for (i = 0; i < n; i++)
   {
      x[i] = 0.0;
      gm += b[i]*b[i];
   } 
   if (gm == 0.0) return;
   gm = sqrt(gm);
   for (i = 0; i < n; i++) q[0][i] = b[i]/gm;
   nIter = 0;
   for (m = 0; m < nMaxIter; m++)
   {
      nIter++;
      m1 = m % k1;
      M->multiplica(q[m1], v);
      for (i = (m - k + 1 < 0 ? 0 : m - k + 1); i <= m; i++)
      {
         i1 = i % k1;
         val = 0.0;
         for (j = 0; j < n; j++) val += v[j]*q[i1][j];
         h[i1][m1] = val;
         for (j = 0; j < n; j++) v[j] = v[j] - val*q[i1][j];
      }
      val = 0.0;
      for (j = 0; j < n; j++) val += v[j]*v[j];
      val = sqrt(val);
      h[m1 + 1][m1] = val;
      for (j = 0; j < n; j++) q[m1 + 1][j]  = v[j] / val;
      applyOmega(m);
      val = sqrt(h[m1][m1]*h[m1][m1] + h[m1 + 1][m1]*h[m1 + 1][m1]);
      cs[m1][0] = h[m1][m1]/val;
      cs[m1][1] = h[m1 + 1][m1]/val;
      gm1 = -cs[m1][1]*gm;
      gm = cs[m1][0]*gm;
      h[m1][m1] = cs[m1][0]*h[m1][m1] + cs[m1][1]*h[m1 + 1][m1];
      for (i = 0; i < n; i++)
      {
         val = q[m1][i];
         for (j = (m - k < 0 ? 0 : m - k); j < m; j++)
         {
            j1 = j % k1;
            val -= h[j1][m1]*p[j1][i];
         }
         p[m1][i] = val / h[m1][m1];
         x[i] += gm*p[m1][i];
      }
      val = (gm1 < 0.0 ? -gm1 : gm1);
      gm = gm1;
      if (val < eps) break;
   }
}

