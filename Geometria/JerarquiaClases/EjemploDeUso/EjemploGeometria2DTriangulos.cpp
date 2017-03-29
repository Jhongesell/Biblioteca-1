//////////////////////////////////////////////////////////////////////////////////////////////
// Programa para generar una geometria en dos dimensiones con triángulos                    //
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




#include "Geometria_2DTriangulos.hpp"

 // Funcion Principal ....
int main(void)
{
   int i,arr[100], num = 0;
   printf("\nParticiona el dominio\n");
   Geometria_2DTriangulos A(0.0,0.0,1.0,1.0,2,2);
   A.visualizaCoordenadasDominio();
   A.visualizaElementos();
   A.visualizaNodos();
   
   //~ A.grabaGeometria("MiGeometria.dat");
   
   
   //~ Geometria_2DTriangulos B("MiGeometria.dat");
   //~ B.visualizaCoordenadasDominio();
   //~ B.visualizaElementos();
   //~ B.visualizaNodos();
   
   //~ printf("\nVisualiza los nodos que la primera coordenada sea 0.0\n\n");
   //~ B.marcaNodosSatisfagan(0.0, 0, -1);
   //~ B.visualizaElementos();
   //~ B.visualizaNodos();
   //~ num = B.regresaNodosSatisfagan(0.0, 0, arr,100);
   //~ printf("\nVisualiza los nodos marcados\n");
   //~ for (i = 0; i < num; i++) {
      //~ printf("Nodo: %d\n",arr[i]);
   //~ }
   //~ B.generaSoporteNodos();
   //~ B.visualizaSoporteNodos();

}


