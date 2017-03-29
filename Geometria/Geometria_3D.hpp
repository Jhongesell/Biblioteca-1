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



#ifndef __Geometria_3D__
#define __Geometria_3D__

#include "Geometria.hpp"


/// Clase base para generar una geometria en 3D
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Geometria_3D : public Geometria
{

public:

   /// Constructor de la clase
   Geometria_3D(void) : Geometria()
   {
      size_t i;
      Dominio.redimensiona(2,3);
      Particion.redimensiona(3);
   }

   /// Coordenadas dentro del dominio
   /** @param x Coordenada X
       @param y Coordenada Y
       @param z Coordenada Z
       @return (1) si las coordenadas estan dentro del dominio, (0) en caso contrario  */
   int coordenadasDentroDominio(ldouble x, ldouble y, ldouble z)
   {
      if (x < (Dominio.retorna(0,0) - TOLERANCIA_NODO) || x > (Dominio.retorna(1,0) + TOLERANCIA_NODO) ) return 0;
      if (y < (Dominio.retorna(0,1) - TOLERANCIA_NODO) || y > (Dominio.retorna(1,1) + TOLERANCIA_NODO) ) return 0;
      if (z < (Dominio.retorna(0,2) - TOLERANCIA_NODO) || z > (Dominio.retorna(1,2) + TOLERANCIA_NODO) ) return 0;
      return 1;
   }

   // Retorna el numero de nodo que tiene coordenadas Coor, si no pertenece -1
   /** @param x Coordenada X
       @param y Coordenada Y
       @param z Coordenada Z
       @return retorna el numero de nodo o (-1) si no es encontrado  */
   int retornaNodoCoord(ldouble x, ldouble y, ldouble z);

   /// Retorna las coordenadas del nodo especificado
   /** @param nd Número de nodo
       @param[out] x Coordenada X
       @param[out] y Coordenada Y
       @param[out] z Coordenada Z */
   inline void coordenadasNodo(int nd, ldouble &x, ldouble &y, ldouble &z)
   {
      x = ND->retorna(nd, 0);
      y = ND->retorna(nd, 1);
      z = ND->retorna(nd, 2);
   }

   /// Establece las coordenadas del nodo
   /** @param nodo Número de nodo
       @param x Coordenada X
       @param y Coordenada Y
       @param z Coordenada Z */
   inline void estableceValorCoordenadas(int nodo, ldouble x, ldouble y, ldouble z)
   {
      ND->asigna(nodo,0,x);
      ND->asigna(nodo,1,y);
      ND->asigna(nodo,2,z);
   }

   /// Regresa las coordenadas del elemento
   /** @param el Número de elemento
       @param x Puntero a las coordenada X
       @param y Puntero a las coordenada Y
       @param z Puntero a las coordenada Z */
   void coordenadasElemento(int el, ldouble *x, ldouble *y, ldouble *z);

   /// Número máximo de nodos en la frontera
   /** @return Número máximo de nodos en la frontera */
   inline int numeroMaximoNodosFrontera(void)
   {
      return ((2*Particion.retorna(0) + 2*Particion.retorna(1)) * Particion.retorna(2));
   }

   /// Retrona las coordenadas del dominio
   /** @param ini Puntero a las coordenadas iniciales del dominio
       @param fin Puntero a las coordenadas finales del dominio */
   inline void coordenadasDominio(ldouble *ini, ldouble *fin)
   {
      ini[0] = Dominio.retorna(0,0);
      ini[1] = Dominio.retorna(0,1);
      ini[2] = Dominio.retorna(0,2);
      fin[0] = Dominio.retorna(1,0);
      fin[1] = Dominio.retorna(1,1);
      fin[2] = Dominio.retorna(1,2);
   }

   //~ /// Regresa los nodos externos en un arreglo ARR y numero ND
   //~ /** @param arr Puntero a un arreglo de nodos
   //~ @param nd Número de nodos */
   //~ void Regresa_Nodos_externos(int *arr, int nd);

   //~ /// Marca los nodos externos con el valor MC
   //~ /** @param mc Valor a usar de marca */
   //~ void Marca_Nodos_Externos(int mc);

   //~ /// Retorna el numero y nodos adyacentes a un nodo dado
   //~ /** @param nd Nodo a buscar
   //~ @param nds Puntero a un arreglo de nodos
   //~ @param nnds Número de nodos */
   //~ int Retorna_Nodos_Adyacentes(int nd, int *nds, int nnds);

   //~ /// Calcula el tipo de nodo dentro del dominio positivo es desconocido, negativo es conocido (1) Interior , (2) cara, (3) Vertice
   //~ void Calcula_tipo_nodo(void);

   /// Visualiza coordenadas del dominio
   void visualizaCoordenadasDominio(void)
   {
#ifdef __Double__
      printf("\nDominio: (%f,%f,%f) a (%f,%f,%f)\n\n",Dominio.retorna(0,0),Dominio.retorna(0,1),Dominio.retorna(0,2),Dominio.retorna(1,0),Dominio.retorna(1,1),Dominio.retorna(1,2));
#else
      printf("\nDominio: (%Lf,%Lf,%Lf) a (%Lf,%Lf,%Lf)\n\n",Dominio.retorna(0,0),Dominio.retorna(0,1),Dominio.retorna(0,2),Dominio.retorna(1,0),Dominio.retorna(1,1),Dominio.retorna(1,2));
#endif
   }

};

#endif
