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



#ifndef __DQGMRES__
#define __DQGMRES__

#include <math.h>
#include <stdlib.h>
#include "MatrizBandDisp.hpp"

#define NMAXITER 50000

class DQGMRES 
{
protected:

   int n;             // vector size
   int k;             // # vectors to save
   int k1;
   int maxIter;       // maximum number of interations
   int nIter;         // current iteration
   //~ ArrayInt ind;         // Index array to p, Q
   //~ int index;
   double gm;         // gamma(m)
   double gm1;        // gamma(m + 1)
   double **p;      // [k + 1][n]
   double **cs;     // [k + 1][2] cosine, sine array for rotation
   double **h;      // Hessenberg
   double **q;      // quasi orthogonal vectors [k + 1][n]
   double *v;        // scratch
   double eps;
   int nMaxIter;

   /// Matriz Bandada o Dispersa
   MatrizBandDisp *M;


public:

   //~ DQGMRES(MultOp &mult, int k)
   //~ {
      //~ /* n = vector size, k = number of previous vectors to be saved & orthogonalized  */
      //~ this->eps = 1.0e-8;
      //~ this->nMaxIter = NMAXITER;
      //~ this->mult = &mult;
      //~ this->n = mult.getSize();
      //~ this->k = k;
      //~ inicializa();
   //~ }

   //~ DQGMRES(void)
   //~ {
      //~ this->eps = 1.0e-8;
      //~ this->nMaxIter = NMAXITER;
   //~ }

   /// Constructor de la clase
   DQGMRES(int n, MatrizBandDisp *M, int k) 
   {
      
      this->M = M;      
      this->n = n;
      this->k = k;
      this->eps = 1.0e-8;
      this->nMaxIter = NMAXITER;
      inicializa();
   }

   // Destructor de la clase
   ~DQGMRES()
   {
      delete M;
      libera();
   }
   
   /// vector size
   int getSize(void)
   {
      return n;
   }

   
   // Se quita pues genera un error en las referencias a MultOp
   //~ DQGMRES(MultOp &mult)
   //~ {
   //~ int n = (int) sqrt(mult.getSize());
   //~ DQGMRES(mult, n);
   //~ }

   void inicializa(void);

   void libera(void)
   {
      int i;
      for (i = 0; i < k1; i++)
      {
         delete []p[i];
         p[i] = NULL;
      }
      delete []p;
      p=NULL;

      for (i = 0; i < (k1+1); i++)
      {
         delete []q[i];
         q[i] = NULL;
      }
      delete []q;
      q=NULL;

      for (i = 0; i < k1; i++)
      {
         delete []cs[i];
         cs[i] = NULL;
      }
      delete []cs;
      cs=NULL;

      for (i = 0; i < (k1+1); i++)
      {
         delete []h[i];
         h[i] = NULL;
      }
      delete []h;
      h=NULL;

      delete []v;
   }

   void applyOmega(int m);

   void solve(Vector *x, Vector *b);

   int getIter(void)
   {
      return nIter;
   }

   void setMaxIter(int nmi)
   {
      nMaxIter = nmi;
   }

   void setEpsilon(double ep)
   {
      eps = ep;
   }

};

#endif
