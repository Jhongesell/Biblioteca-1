//////////////////////////////////////////////////////////////////////////////////////////////
// Programa para generar una geometria en 3D usando Ortoedros                               //
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


 // Funcion Principal ....
int main(void)
{
   printf("\nGenera partición del dominio\n");
   Geometria_3DOrtoedros A(0.0,0.0,0.0,1.0,1.0,1.0,3,3,3);
   A.visualizaCoordenadasDominio();
   A.visualizaElementos();
   A.visualizaNodos();
   //~ A.grabaGeometria("MiGeometria.dat");
   
   //~ printf("\nLee partición del dominio\n");
   //~ Geometria_3DOrtoedros *B = new Geometria_3DOrtoedros("MiGeometria.dat");
   //~ Geometria *C = B;
   
   //~ C->visualizaCoordenadasDominio();
   //~ C->visualizaElementos();
   //~ C->visualizaNodos();
   
   //~ delete B;
}

