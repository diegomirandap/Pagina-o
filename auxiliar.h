#include <stdio.h>
#define FALSE 0
#define TRUE 1
#define VAZIO -1
#define SIZE_FILA 1000
  
typedef struct frame {
   int R; // indica leitura
   int W; // indica escrita
   int tempo; // indica tempo de ultimo uso
   int endV; // indica endereco de memoria virtual

} Frame;

typedef struct leitura{
   char tipo; // R ou W
   int end;
} Leitura;

typedef struct fila{
   Leitura* vetor;
   int len;
   int itens;
   int prox;
} Fila;

// Algoritmos
int NRU(int len, Frame* frames);
int LRU(int len, Frame* frames);


// Substituicao de paginas
int leLinha(char* tipo, Fila* fila, FILE* arq, int* endVirtual, int shift);
void atualizaQuadro(char flag, Frame *vetQuadros, int indice, int indiceV, int tempo);


// Fila
Fila* criaFila(int tam);
void addFila(char tipo, Fila *fila, int endereco);
Leitura removeFila(Fila *fila);
void deleteFila(Fila *fila);

