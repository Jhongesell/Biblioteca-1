
#include "DQGMRES.hpp"
#include "MatrizBandDisp.hpp"
#include "Vector.hpp"


int main(void)
{
   int i,j;

   const int TAM = 3;
   ldouble B[TAM]={ 24,30,-24};
   ldouble A[][TAM] = {
     {4,3,0},
     {3,4,-1},
     {0,-1,4}
   }; 

   
   
   Vector *x = new Vector(TAM,"Solucion");
   Vector *y = new Vector(TAM);
   Vector *b = new Vector(TAM,"Lado derecho");

   b->convierte(B,TAM); 
   
    
   
   MatrizBandDisp *M2 = new MatrizBandDisp(TAM,TAM,6,"M2");
   for (i = 0; i < TAM; i++) {
      for (j = 0; j < TAM; j++) {
         M2->asigna(i,j,A[i][j]);
      }         
   }


   
      x->inicializa(0.0);
      M2->resuelve();
      printf("\nIteraciones %d",arr[i]->retornaNumeroIteraciones());
      x->visualiza(1,1);

   
   delete M2;

   delete x;
   delete y;
   delete b;
   
   return 0;
}



