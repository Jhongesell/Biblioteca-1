//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para generar una geometría en tres dimensiones usando ortoedros                    //
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




#include "Geometria_3DOrtoedros.hpp"


// Genera la geometria
void Geometria_3DOrtoedros::generaGeometria(void)
{

   // Solicita la memoria necesaria
   EL = new MatrizInt(N_E,NNE,"Nodos que conforman a los elementos",-1);
   if (!EL) errorSolicitudMemoria("Elementos Geometria_Ortoedros3D");

   int col[]= {Particion.retorna(0)+1, Particion.retorna(1)+1, Particion.retorna(2)+1};
   ND = new MatrizTamanoVariable(DIM, col, "Coordenadas de Nodos");
   if (!ND) errorSolicitudMemoria("Coordenadas Geometria_Ortoedros3D");

   NN = new VectorInt(N_N,"Numeracion de nodos");
   if (!NN) errorSolicitudMemoria("Nodos Geometria_Ortoedros3D");

   TN = new VectorInt(N_N,"Tipo de nodos");
   if (!TN) errorSolicitudMemoria("Tipo de Nodo Geometria_Ortoedros3D");

   int i, j, t, n, k;

   // Calcula los tamaños de las particiones horizontales como verticales
   ldouble Ic_H = (Dominio.retorna(1,0) - Dominio.retorna(0,0)) / Particion.retorna(0);
   ldouble Ic_V = (Dominio.retorna(1,1) - Dominio.retorna(0,1)) / Particion.retorna(1);
   ldouble Ic_Z = (Dominio.retorna(1,2) - Dominio.retorna(0,2)) / Particion.retorna(2);

   for (k = 0; k < Particion.retorna(2); k++)
   {
      ND->asigna(2,k,Dominio.retorna(0,2) + Ic_Z * k);
      for (i = 0; i < Particion.retorna(1); i++)
      {
         ND->asigna(1,i,Dominio.retorna(0,1) + Ic_V * i);
         for (j = 0; j < Particion.retorna(0); j++)
         {
            ND->asigna(0,j,Dominio.retorna(0,0) + Ic_H * j);
            t = (k * Particion.retorna(0) * Particion.retorna(1)) + (Particion.retorna(0) * i) + j;

            // Cara anterior
            n = (Particion.retorna(0) * i) + j + i + (Particion.retorna(0) + 1) * (Particion.retorna(1) + 1)*k;
            EL->asigna(t,0,n);
            //~ estableceValorCoordenadas(n,(Dominio.retorna(0,0) + (j * ic_x)),(Dominio.retorna(0,1) + (i * ic_y)), (Dominio.retorna(0,2) + (k * ic_z)));

            n = (Particion.retorna(0) * i) + j + i + 1 + (Particion.retorna(0) + 1) * (Particion.retorna(1) + 1) * k;
            EL->asigna(t,1,n);
            //~ estableceValorCoordenadas(n,(Dominio.retorna(0,0) + ((j + 1) * ic_x)), (Dominio.retorna(0,1) + (i * ic_y)), (Dominio.retorna(0,2) + (k * ic_z)));

            n = (Particion.retorna(0) * (i + 1)) + j + i + 2 + (Particion.retorna(0) + 1)*(Particion.retorna(1) + 1) * k;
            EL->asigna(t,2,n);
            //~ estableceValorCoordenadas(n,(Dominio.retorna(0,0) + ((j + 1) * ic_x)), (Dominio.retorna(0,1) + ((i + 1) * ic_y)), (Dominio.retorna(0,2) + (k * ic_z)));

            n = (Particion.retorna(0) * (i + 1)) + j + i + 1 + (Particion.retorna(0) + 1) * (Particion.retorna(1) + 1) * k;
            EL->asigna(t,3,n);
            //~ estableceValorCoordenadas(n,(Dominio.retorna(0,0) + (j * ic_x)), (Dominio.retorna(0,1) + ((i + 1) * ic_y)), (Dominio.retorna(0,2) + (k * ic_z)));


            // Cara posterior
            n = (Particion.retorna(0) * i) + j + i + (Particion.retorna(0) + 1)*(Particion.retorna(1) + 1) * ( k + 1);
            EL->asigna(t,4,n);
            //~ estableceValorCoordenadas(n,(Dominio.retorna(0,0) + (j * ic_x)),(Dominio.retorna(0,1) + (i * ic_y)), (Dominio.retorna(0,2) + ((k+1) * ic_z)));

            n = (Particion.retorna(0) * i) + j + i + 1 + (Particion.retorna(0) + 1)*(Particion.retorna(1) + 1) * (k + 1);
            EL->asigna(t,5,n);
            //~ estableceValorCoordenadas(n,(Dominio(0,0) + ((j + 1) * ic_x)), (Dominio.retorna(0,1) + (i * ic_y)), (Dominio.retorna(0,2) + ((k+1) * ic_z)));

            n = (Particion.retorna(0) * (i + 1)) + j  + i + 2 + (Particion.retorna(0) + 1)*(Particion.retorna(1) + 1) * (k + 1);
            EL->asigna(t,6,n);
            //~ estableceValorCoordenadas(n,(Dominio.retorna(0,0) + ((j + 1) * ic_x)), (Dominio.retorna(0,1) + ((i + 1) * ic_y)), (Dominio.retorna(0,2) + ((k+1) * ic_z)));

            n = (Particion.retorna(0) * (i + 1)) + j  + i + 1 + (Particion.retorna(0) + 1)*(Particion.retorna(1) + 1) * (k + 1);
            EL->asigna(t,7,n);
            //~ estableceValorCoordenadas(n,(Dominio.retorna(0,0) + (j * ic_x)), (Dominio.retorna(0,1) + ((i + 1) * ic_y)), (Dominio(0,2) + ((k+1) * ic_z)));
         }
         ND->asigna(0,j,Dominio.retorna(0,0) + Ic_H * j);
      }
      ND->asigna(1,i,Dominio.retorna(0,1) + Ic_V * i);
   }
   ND->asigna(2,k,Dominio.retorna(0,2) + Ic_Z * k);
}


// Calcula el tipo de nodo dentro del dominio, positivo es desconocido, negativo es conocido (1) Interior , (2) cara, (3) Vertice
void Geometria_3DOrtoedros::calculaTipoNodo(void)
{
   int st, i, sg = 0;
   //~ ldouble x, y,ini[3], fin[3];
#ifdef DEPURAR
   if (!TN)
   {
      printf("\nNo ha sido inicializado el arreglo para mantener al tipo de nodo\n");
      exit(1);
   }
#endif
   //~ Coordenadas_dominio(ini,fin);
   for (i = 0; i <  N_N; i++)
   {
      if (retornaNumeracionNodo(i) >= 0) sg = 1;
      else sg = -1;

      //~ coordenadasNodo(i,x,y);
      st = 0;

//~ #ifdef __Double__
      //~ if (fabs(ini[0] - x) < TOLERANCIA_NODO) st ++;
      //~ if (fabs(ini[1] - y) < TOLERANCIA_NODO) st ++;
      //~ if (fabs(fin[0] - x) < TOLERANCIA_NODO) st ++;
      //~ if (fabs(fin[1] - y) < TOLERANCIA_NODO) st ++;
//~ #else
      //~ if (fabsl(ini[0] - x) < TOLERANCIA_NODO) st ++;
      //~ if (fabsl(ini[1] - y) < TOLERANCIA_NODO) st ++;
      //~ if (fabsl(fin[0] - x) < TOLERANCIA_NODO) st ++;
      //~ if (fabsl(fin[1] - y) < TOLERANCIA_NODO) st ++;
//~ #endif
      switch (st)
      {
      case 1:  // Nodo en una cara
         TN->asigna(i,2*sg);
         break;
      case 2:  // Nodo en un vertice
         TN->asigna(i,3*sg);
         break;
      default: // Nodo interior
         TN->asigna(i,1*sg);
      }
   }
}





