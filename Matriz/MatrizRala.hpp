//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el trabajar con matrices rala de punto flotante                               //
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



#ifndef __MatrizRala__
#define __MatrizRala__

#include "Matriz.hpp"


// Estructura de las columnas de la lista doblemente ligada
typedef struct nodoColumna
{
   nodoColumna *Sig; // Nodo siguiente
   nodoColumna *Ant; // Nodo anterior
   int col;          // Columna
   ldouble val;      // Valor de la columna
} NodoCol;

// Estructura de los renglones de la lista doblemente ligada
typedef struct nodoRenglon
{
   nodoRenglon *Sig; // Nodo siguiente
   nodoRenglon *Ant; // Nodo anterior
   nodoColumna *inf; // Puntero a la informacion
   int ren;
} NodoRen;


/// Clase para el trabajar con matrices ralas de punto flotante
/** @author Antonio Carrillo Ledesma
    @date primavera 2010
    @version 1.0.1
    @bug No hay errores conocidos
*/
class MatrizRala: public Matriz
{

protected:
   NodoRen      *Nodo_Primero;
   NodoRen      *Nodo_Actual;
   NodoRen      *Nodo_Ultimo;
   NodoRen      *Nodo_temporal;
   unsigned int  Total_nodos;
   unsigned int  N_nodo_actual;
   unsigned int  Indice;
   const char   *pt_info;
   char         *C_nula;


   // Borra nodo temporal asi como la informacion que contiene
   void            Borra_nodo_temporal(void);
   // Adiciona un nodo en el nodo temporal
   void            Adiciona_nodo_temporal(const char *info);

   /// Inicializa las estructuras
   void inicializa(void)
   {
      Tipo_Matriz = MATRIZ_RALA;

      Total_nodos = 0;
      N_nodo_actual = 0;
      Nodo_Primero = NULL;
      Nodo_Actual = NULL;
      Nodo_Ultimo = NULL;
   }

   /// Inicializa las estructuras
   void inicializa(ldouble val)
   { }


private:

   /// Puntero a la matriz de datos
   ldouble **M;
   /// Indica el estado de la matriz cuando esta compactada
   int Estado;


   /// Solicita la memoria necesaria para contener los valores de la matriz
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz */
   void solicitaMemoria(const int ren, const int col);



public:

   //~ /// Constructor de la clase
   //~ MatrizRala(void) : Matriz()
   //~ {
   //~ Estado = 0;
   //~ solicitaMemoria(1, 1);
   //~ asignaNombre("SinNombre");
   //~ }

   //~ /// Constructor de la clase
   //~ /** Genera una matriz a partir de los datos de otra
   //~ @param mat Matriz del cual se hara una copia  */
   //~ MatrizRala(MatrizDensa &mat) : Matriz()
   //~ {
   //~ solicitaMemoria(mat.renglones(),mat.columnas());
   //~ asignaNombre(mat.nombre());
   //~ int i, j;
   //~ for (i = 0; i < Col; i++)
   //~ {
   //~ for (j = 0; j < Ren; j++) M[i][j] = mat.retorna(i,j);
   //~ }
   //~ }

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz */
   MatrizRala(const int ren, const int col) : Matriz()
   {
      Col = col;
      Ren = ren;
      inicializa();
      asignaNombre("SinNombre");
   }

   /// Constructor de la clase
   /** @param ren Número de renglones de la matriz
       @param col Número de columnas de la matriz
       @param nmb Nombre de la matriz*/
   MatrizRala(const int ren, const int col, const char *nmb) : Matriz()
   {
      Col = col;
      Ren = ren;
      inicializa();
      asignaNombre(nmb);
   }

   /// Destructor de la clase
   ~MatrizRala()
   {
      liberaMemoria();
   }

   /// Libera la memoria solicitada para la matriz
   void liberaMemoria(void);


   //~ /// Inicializa la matriz al valor indicado
   //~ /** @param val Valor por omisión para inicializar la matriz */
   //~ void inicializa(const ldouble val);


   /// Asigna el valor indicado en el renglo y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @param val Valor */
   void asigna(const int ren, const int col, const ldouble val);

   /// Retorna el valor del renglon y columna solicitado
   /** @param ren Renglon
       @param col Columna
       @return Valor */
   ldouble retorna(const int ren, const int col);



   /// Copia el contenido de la matriz a la matriz pasada como parámetro
   /** @param a Puntero a una Matriz */
   void copia(Matriz *a);

   /// Multiplica la matriz por el escalar pasado como parametro
   /** @param esc Escalar */
   void multiplica(ldouble esc);

   //~ /// Multiplica la matriz A por la matriz B
   //~ /** @param a Puntero a matriz densa
   //~ @param b Puntero a matriz densa  */
   //~ void multiplica(MatrizDensa *a, MatrizDensa *b);

   /// Multiplica la matriz por el vector B dejando el Resultado en R
   /** @param b Puntero a un Vector
       @param r Puntero a un Vector */
   void multiplica(Vector *b, Vector *r);

   /// Retorna el número de columnas de la banda para el renglon indicado
   /** @param ren Número de renglon
       @return Número de columnas de la banda para el renglon solicitado  */
   int retornaNumeroColumnasBanda(int ren)
   {
      printf("\nFuncion no implementada en esta clase %d\n",ren);
      return 0;
   }

   /// Retorna el número de columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param ind Número de indice
       @return Número de columna cuando se para en el renglon e indice de la banda  */
   int retornaNumeroColumna(int ren, int ind)
   {
      printf("\nFuncion no implementada en esta clase: %d %d\n",ren, ind);
      return 0;
   }

   /// Retorna el valor de la columna cuando se para en el renglon e indice de la banda
   /** @param ren Número de renglon
       @param ind Número de indice
       @return Valor de la columna cuando se para en el renglon e indice de la banda  */
   inline double retornaValorColumna(int ren, int ind)
   {
      return (M[ren][ind]);
   }


};

/**
Esta clase implementa los componentes para el trabajar con matrices rala de punto flotante
@example EjemploMatrizRala.cpp */

#endif
