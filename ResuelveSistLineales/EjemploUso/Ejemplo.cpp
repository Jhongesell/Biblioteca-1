//////////////////////////////////////////////////////////////////////////////////////////////
// Ejemplo para resolver un sistema Ax=b                                                    //
// Revisión: 1 de Junio del 2006                                                            //
//                                                                                          //
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



#include "MatrizBandComp.hpp"
#include "ResuelveInversa.hpp"
#include "ResuelveCGMBandDisp.hpp"
#include "ResuelveGaussSeidelBandDisp.hpp"
#include "ResuelveJacobiBandDisp.hpp"
#include "ResuelveTridiagonal.hpp"
#include "ResuelveFactorizacionLUBandDisp.hpp"
#include "ResuelveFactorizacionCholeskiBandDisp.hpp"


// Ejemplo que muestra el uso de los distintos resolvedores del sistema lineal Ax=b
void Ejem1(void);
// Eejmplo que muestra la resolucion de una ecuacion diferencial parcial en 1D
void Ejem2(void);


int main(void)
{
   // Ejemplo que muestra el uso de los distintos resolvedores del sistema lineal Ax=b
   Ejem1();
   
   // Eejmplo que muestra la resolucion de una ecuacion diferencial parcial en 1D   
   Ejem2();

   return 0;
}



// Ejemplo que muestra el uso de los distintos resolvedores del sistema lineal Ax=b
void Ejem1(void)
{
   int i,j;

   // Definicion de una matriz de 4x4
   const int TAM = 3;
   ldouble B[TAM]= { 24,30,-24};
   ldouble A[][TAM] =
   {
      {4,3,0},
      {3,4,-1},
      {0,-1,4}
   };



   // Definicion de vectores auxiliares
   Vector *x = new Vector(TAM,"Solucion");
   Vector *y = new Vector(TAM);
   Vector *b = new Vector(TAM,"Lado derecho");

   // Convierte el *double en un vector
   b->convierte(B,TAM);


   // Llenado de la matriz
   MatrizBand *M2 = new MatrizBand(TAM,TAM,100,"M2");
   for (i = 0; i < TAM; i++) M2->convierte(A[i],i,TAM);

   

   // Definicion de los distintos sistemas lineales a usar en el ejemplo
   ResuelveCGMBandDisp                     jc1(M2,x,b);
   ResuelveGaussSeidelBandDisp             jc2(M2,x,b);
   ResuelveJacobiBandDisp                  jc3(M2,x,b);

   MatrizDispersa *M3 = new MatrizDispersa(TAM,TAM,TAM,"M3");
   M2->copia(M3);
   ResuelveFactorizacionLUBandDisp         jc4(M3,x,b);

   MatrizDispersa *M4 = new MatrizDispersa(TAM,TAM,TAM,"M4");
   M2->copia(M4);
   ResuelveTridiagonal    jc5(M4,x,b);

   MatrizDispersa *M5 = new MatrizDispersa(TAM,TAM,TAM,"M5");
   M2->copia(M5);
   ResuelveFactorizacionCholeskiBandDisp   jc6(M5,x,b);

   MatrizDispersa *M6 = new MatrizDispersa(TAM,TAM,TAM,"M6");
   M2->copia(M6);
   ResuelveInversa   jc7(M6,x,b);    

   // Se ponen cada uno de los solver en el arreglo
   ResuelveSistemaLineal *arr[7];
   arr[0] = &jc1;
   arr[1] = &jc2;
   arr[2] = &jc3;
   arr[3] = &jc4;
   arr[4] = &jc5;
   arr[5] = &jc6;
   arr[6] = &jc7;
   
   
   // Solucion y visualizacion del resultado
   for(i = 0; i < 7; i++)
   {
      x->inicializa(0.0);
      arr[i]->resuelve();
      arr[i]->informacionMetodo();
      x->visualiza(1,1);
   }


   // Borrado de los objetos generados con memoria dinamica
   delete M2;
   delete M3;
   delete M4;
   delete M5;
   delete M6;

   delete x;
   delete y;
   delete b;
}


// Eejmplo que muestra la resolucion de una ecuacion diferencial parcial en 1D
void Ejem2(void)
{

   int i, j, k, inc = 10;
   ldouble a = 0.0;           // Inicio dominio
   ldouble c = 1.0;           // Fin dominio
   ldouble Y0 = 0.0;          // Condición inicial en el inicio del dominio
   ldouble Y1 = 1.0;          // Condición inicial en el fin del dominio
   for (i = inc; i <= inc*30 ; i += inc)
   {
      printf("\n\nMatriz de %dx%d\n", i, i);
      MatrizBandComp *A = new MatrizBandComp(i, i, 3, "A");
      Vector *x = new Vector(i, "Solucion");
      Vector *b = new Vector(i, "Lado derecho");

      ldouble h = (c - a) / (i - 1); // Incremento en la malla
      ldouble P = 2 / (h * h);
      ldouble Q = -1.0 / (h * h) + 1.0 / (2.0 * h);
      ldouble R = -1.0 / (h * h) - 1.0 / (2.0 * h);



      // LLena la matriz
      A->asigna(0, 0, P);
      A->asigna(0, 1, Q);
      b->asigna(0, -Y0 * R);
      for(j = 1; j < i - 1; j++)
      {
         A->asigna(j, j - 1, R);
         A->asigna(j, j, P);
         A->asigna(j, j + 1, Q);
      }
      A->asigna(i - 1, i - 2, R);
      A->asigna(i - 1, i - 1, P);
      b->asigna(i - 1, -Y1 * Q);
      A->visualizaMatricesInternas();
      A->visualiza(0);



      // Definicion de los distintos sistemas lineales a usar en el ejemplo
      ResuelveCGMBandDisp                     jc1(A, x, b);
      ResuelveGaussSeidelBandDisp             jc2(A, x, b);
      ResuelveJacobiBandDisp                  jc3(A, x, b);

      MatrizDispersa *M3 = new MatrizDispersa(i,i,3,"M3");
      A->copia(M3);
      ResuelveFactorizacionLUBandDisp         jc4(M3,x,b);
      
      
      // Se ponen cada uno de los solver en el arreglo
      ResuelveSistemaLineal *arr[4];
      arr[0] = &jc1;
      arr[1] = &jc2;
      arr[2] = &jc3;
      arr[3] = &jc4;
      


      // Solucion y visualizacion del resultado
      for(k = 0; k < 4; k++)
      {
         x->inicializa(0.0);
         arr[k]->resuelve();
         arr[k]->informacionMetodo();
         x->visualiza(1, 1);
      }

      delete x;
      delete b;
      delete A;
      delete M3;
   }
}
