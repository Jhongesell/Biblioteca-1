//////////////////////////////////////////////////////////////////////////////////////////////
// Programa para generar una geometria en una dimensión                                     //
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



#include "Geometria_1DHomogenea.hpp"
#include "Geometria_1DLeerArchivo.hpp"
#include "Geometria_1DHeterogenea.hpp"


 // Funcion Principal ....
int main(void)
{
   // Primer ejemplo
   printf("\nGenera partición del dominio\n");
   Geometria_1DHomogenea C(0.0,1.0,10);
   C.visualizaCoordenadasDominio();
   C.visualizaElementos();
   C.visualizaNodos();
   printf("\nVisualiza los elementos que contienen al nodo 2\n\n");
   C.visualizaElementosContienenNodo(2);



   // Segundo ejemplo
   Geometria_1D *arr[2];
   Geometria_1DHeterogenea *A = new Geometria_1DHeterogenea(0.0,2.0,10,DOMINIO_NM,IZQUIERDA);
   Geometria_1DHeterogenea *B = new Geometria_1DHeterogenea(0.0,2.0,10,DOMINIO_NM,DERECHA);
   
   arr[0] = A;
   arr[1] = B;
   
   for (int i = 0; i < 2; i++)
   {
      arr[i]->visualizaCoordenadasDominio();
      arr[i]->visualizaElementos();
      arr[i]->visualizaNodos();
      printf("\nVisualiza los elementos que contienen al nodo 2\n\n");
      arr[i]->visualizaElementosContienenNodo(2);
      arr[i]->generaSoporteNodos();
      arr[i]->visualizaSoporteNodos();
   }
   
   delete A;
   delete B;
   arr[0] = NULL;
   arr[1] = NULL;
}
