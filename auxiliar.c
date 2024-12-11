#include "auxiliar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ALGORITMOS
int NRU(int len, Frame *frames) {
  int indSubs = -1;

  for (int i = 0; i < len; i++) {
    if (!frames[i].R && !frames[i].W) { // Nao lida e nao escrita
      indSubs = i;
      break;
    } 
    else if (!frames[i].R && (indSubs == -1 || frames[i].W))  // nao lida e escrita
      indSubs = i;
    
    else if (frames[i].R && !frames[i].W && indSubs == -1)  // Lida e nao escrita
      indSubs = i;
      
    else if (frames[i].R && frames[i].W && indSubs == -1)  // Lida e escrita
      indSubs = i;
  }

  return indSubs;
}

int LRU(int len, Frame *frames) {
  int menorTempo = 2147483647; // Armazena o menor tempo registrado, o mais antigo
  int indSubs = 0;

  int i = 0;
  for (int i = 0; i < len; i++) {
    if (frames[i].tempo < menorTempo) {
      menorTempo = frames[i].tempo;
      indSubs = i;
    }
  }
  return indSubs; // Retorna o índice mais antigo para ser substituído
}



// Substituicao de paginas
int leLinha(char *tipo, Fila *fila, FILE *arq, int *endVirtual, int shift) {
  if (fila->itens <= 0) { // Fila vazia
    unsigned int end;
    if (fscanf(arq, "%x %c", &end, tipo) != 2) {
      return -1;
    }
    // Obtido de acordo com os diferentes tamanhos de pagina e deslocamento
    *endVirtual = end >> shift;
    return 0;
  }
  // Remove o ultimo lido e altera de acordo com a nova fila
  //Leitura temp = removeFila(fila);
  //*endVirtual = temp.end;
  //*tipo = temp.tipo;
  return 1;
}

// Atualiza um quadro do vetor de quadros/frames
void atualizaQuadro(char flag, Frame *vetQuadros, int indice, int indiceV, int tempo) {
  // Writing
  if (flag == 'W') {
    vetQuadros[indice].W = 1;
  }

  vetQuadros[indice].endV = indiceV;
  vetQuadros[indice].R = 1;
  vetQuadros[indice].tempo = tempo;
}



// MANIPULACAO DA FILA
Fila *criaFila(int len) {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  if (fila == NULL) {
    printf("Erro ao alocar memoria\n");
    exit(EXIT_FAILURE);
  }

  fila->vetor = (Leitura *)malloc(len * sizeof(Leitura)); // Elementos na fila
  if (fila->vetor == NULL) {
    printf("Erro ao alocar memoria\n");
    exit(EXIT_FAILURE);
  }

  fila->len = len; // Tamanho maximo da fila
  fila->itens = 0; // Tamanho da fila
  fila->prox = -1; // Ponteiro para prox

  return fila;
}

void addFila(char tipo, Fila *fila, int endereco) {
  if (fila->itens <= 0) { // Fila vazia
    fila->vetor[0].end = endereco;
    fila->vetor[0].tipo = tipo;
    fila->prox = 0;
    fila->itens = 1;
  } else { // Fila nao vazia
    int posicao = (fila->prox + fila->itens) % fila->len;
    Leitura *temp = &(fila->vetor[posicao]);
    temp->end = endereco;
    temp->tipo = tipo;
    fila->itens++;
    fila->prox = (fila->prox + 1) % fila->len;
  }
}

Leitura removeFila(Fila *fila) {
  Leitura temp;
  if (fila->itens == 0) {
    printf("Sem itens na fila\n");
    exit(EXIT_FAILURE);
  }

  temp = fila->vetor[fila->prox];
  fila->itens--;
  fila->prox = (fila->prox - 1 + fila->len) % fila->len;
  return temp;
}

void deleteFila(Fila *fila) {
  free(fila->vetor);
  free(fila);
}

