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




#ifndef __Geometria_3DOrtoedros__
#define __Geometria_3DOrtoedros__


#include "Geometria_3D.hpp"


/// Clase para generar una geométria ortoedrica 3D
/** @author Antonio Carrillo Ledesma
    @date primavera 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class Geometria_3DOrtoedros : public Geometria_3D
{

public:

   /// Constructor de la clase
   /** @param x1 Coordenada X del inicio del dominio
       @param y1 Coordenada Y del inicio del dominio
       @param z1 Coordenada Z del inicio del dominio
       @param x2 Coordenada X del fin del dominio
       @param y2 Coordenada Y del fin del dominio
       @param z2 Coordenada Z del fin del dominio
       @param part_x Partición en X
       @param part_y Partición en Y
       @param part_z Partición en Z  */
   Geometria_3DOrtoedros(ldouble x1, ldouble y1, ldouble z1, ldouble x2, ldouble y2, ldouble z2, int part_x, int part_y, int part_z) : Geometria_3D()
   {
      // Dimension 3
      DIM = 3;
      // Numero de nodos por elemento
      NNE = 8;
      // Numero máximo de elementos que son soporte de un nodo
      NMESN = 8;
      // Numero de rectangulos
      N_E = part_x * part_y * part_z;
      // Numero de nodos
      N_N = (part_x + 1) * (part_y + 1) * (part_z + 1);

      Dominio.asigna(0,0,x1);
      Dominio.asigna(0,1,y1);
      Dominio.asigna(0,2,z1);
      Dominio.asigna(1,0,x2);
      Dominio.asigna(1,1,y2);
      Dominio.asigna(1,2,z2);

      Particion.asigna(0,part_x);
      Particion.asigna(1,part_y);
      Particion.asigna(2,part_z);

      generaGeometria();
   }

   /// Constructor de la clase
   /** @param arch Nombre del archivo que contiene la geometria */
   Geometria_3DOrtoedros(const char *arch)
   {
      // Dimension 1D
      DIM = 3;
      // Numero de nodos por elemento
      NNE = 8;
      // Numero máximo de elementos que son soporte de un nodo
      NMESN = 8;

      leeGeometria(arch);
   }

   /// Genera la geometria
   void generaGeometria(void);


   /// Calcula el tipo de nodo dentro del dominio, positivo es desconocido, negativo es conocido (1) Interior , (2) cara, (3) Vertice
   void calculaTipoNodo(void);

};

/**
Esta clase implementa los componentes para generar una geométria ortoedrica 3D
@example EjemploGeometria3DOctaedros.cpp */

#endif
