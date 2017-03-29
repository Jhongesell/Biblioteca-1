//////////////////////////////////////////////////////////////////////////////////////////////
// Clase base para generar una geometría en tres dimensiones                                //
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


#include <math.h>
#include "Geometria_3D.hpp"
#include "Ctrl_vis.hpp"





// Retorna el numero de nodo que tiene coordenadas Coor, si no pertenece -1
// @param x Coordenada X
// @param y Coordenada Y
// @param z Coordenada Z
// @return retorna el numero de nodo o (-1) si no es encontrado
int Geometria_3D::retornaNodoCoord(ldouble x, ldouble y, ldouble z)
{
   int i;
   ldouble x1, y1, z1;

#ifdef DEPURAR
   // Revisa que el nodo solicitado este en el dominio
   if (!coordenadasDentroDominio(x,y,z)) return -1;
#endif

   for (i = 0; i <  N_N; i++)
   {
      coordenadasNodo(i, x1, y1, z1);
#ifdef __Double__
      if ( fabs(x1 - x) < TOLERANCIA_NODO && fabs(y1 - y) < TOLERANCIA_NODO && fabs(z1 - z) < TOLERANCIA_NODO) return i;
#else
      if ( fabsl(x1 - x) < TOLERANCIA_NODO && fabsl(y1 - y) < TOLERANCIA_NODO && fabsl(z1 - z) < TOLERANCIA_NODO) return i;
#endif
   }
   // Nodo no encontrado
   return -1;
}


// Regresa las coordenadas del elemento
// @param el Número de elemento
// @param x Puntero a las coordenada X
// @param y Puntero a las coordenada Y
// @param z Puntero a las coordenada Z
void Geometria_3D::coordenadasElemento(int el, ldouble *x, ldouble *y, ldouble *z)
{
   int i, xnd;
   for (i = 0; i < NNE; i++)
   {
      xnd = EL->retorna(el-1,i);
      x[i] = ND->retorna(xnd,0);
      y[i] = ND->retorna(xnd,1);
      z[i] = ND->retorna(xnd,2);
   }
}

