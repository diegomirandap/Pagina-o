// Diego Miranda 2210996
// Felipe Cancella 2210487

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "auxiliar.h"
/*
int main(int argc, char *argv[]) {

  char algoritmo[4];
  char arquivo[31];

  // Cria a fila dos proximos acessos
  Fila *fila = criaFila(SIZE_FILA);
  
  // Armazena os índices de páginas virtuais que serão acessadas em breve
  int *proxLeitura = (int *)malloc(SIZE_FILA * sizeof(int));

  // Define Algoritmo de substituicao, Nome do log, Tamanho da pagina/quadro (8 ou 16KB), Tamanho da memoria fisica (1 a 4MB)
  strcpy(algoritmo, argv[1]);
  strcpy(arquivo, argv[2]);
  int tamPagina = atoi(argv[3]);
  int tamMemFis = atoi(argv[4]);

  // Quantidade de bits que guardam a pagina
  int paginaBits;
  // Número de paginas virtuais
  int tamTabPaginas;
  // Número de quadros na memória física
  int tamQuadro;

  if (tamPagina == 16){
    paginaBits = 14; // 2^14 ==> 8KB
    tamTabPaginas = pow(2, 18); // 32 - 14 = 18 ==> Quantidade de paginas
    tamQuadro = (tamMemFis*1024)/16; // *1024 ==> MB -> KB
  }
  else if (tamPagina == 8) {
    paginaBits = 13; // 2^13 ==> 8KB
    tamTabPaginas = pow(2, 19); // 32 - 13 = 19 ==> Quantidade de paginas
    tamQuadro = (tamMemFis*1024)/8; // *1024 ==> MB -> KB
  }

  // Quadros da memoria
  Frame *vetQuadros = malloc(tamQuadro * sizeof(Frame));

  // Paginas da tabela de pagina
  int *tabPaginas = malloc(tamTabPaginas * sizeof(int));

  for (int i = 0; i < tamTabPaginas; i+=1) {
    tabPaginas[i] = VAZIO;
  }
  
  char flag;
  int indice; // Indice(traducao) do endereco na tabela de paginas para o frame fisico
  int indiceV, tempo = 0, pageFault, contWrite = 0, contRead = 0, contPageFault = 0, alocados = 0, i;
  
  // Abre o log
  FILE *arq = fopen(arquivo, "r");
  if (arq == NULL) {
    printf("Erro ao abrir arquivo");
    exit(1);
  }

  while (leLinha(&flag, fila, arq, &indiceV, paginaBits) != -1) {
    // leLinha() ==> Define o Endereco Virtual e a Flag (Read/Write) da linha lida

    // Page fault
    // (indice = tabPaginas[indiceV])==VAZIO ==> Verifica se ja esta na tabela de paginas
    if ((indice = tabPaginas[indiceV]) == VAZIO) {
      contPageFault++;
      
      if (alocados < tamQuadro) { // Espaço na mem fisica disponivel

        tabPaginas[indiceV] = alocados; // Atualiza a tabela de páginas (Associa o indice (pagina) virtual com o indice (quadro) físico)
        vetQuadros[alocados].W = FALSE;

        indice = alocados;
        alocados++;
      }

      // Memoria fisica lotada (Substituicao de pagina)
      else {
        int indexNovo, len, atual, tamFila = fila->itens;
        unsigned int addr;
        char flag;

        // Substituindo com o devido algoritmo
        if (strcmp("NRU", algoritmo) == 0)
          indexNovo = NRU(tamQuadro, vetQuadros);
        else if (strcmp("LRU", algoritmo) == 0)
          indexNovo = LRU(tamQuadro, vetQuadros);

        if (vetQuadros[indexNovo].W == TRUE)
          contWrite++;
/
        for (int i = 0; i < (SIZE_FILA - tamFila); i++) {
          // Interpreta cada enderecos de memeria acessado e enfilera ele
          if (fscanf(arq, "%x %c", &addr, &flag) != 2) {
            break;
          }
         // addFila(flag, fila, (addr >> paginaBits));
        }/

        Leitura* temp;
        len = fila->itens;
        temp = fila->vetor;
        atual = fila->prox;

        for (i = 0; i < len; i++) {
          // Percorre todo o vetor preenchendo com a fila
          proxLeitura[i] = temp[atual].end;
          atual = (atual + 1) % len;
          
          //Traduzindo os enderecos com a tabela de paginas
          int indFisico = tabPaginas[proxLeitura[i]];
          // Atualizando o índice de próxima leitura com base na tradução
          if (indFisico < 0) {
              proxLeitura[i] = VAZIO;
          }
          else {
              proxLeitura[i] = indFisico;
          }
        }

        for (i = len; i < SIZE_FILA; i+=1) {
          proxLeitura[i] = VAZIO;
        }

        // Atualiza a tabela de páginas (Associa o novo indice (pagina) virtual com o indice (quadro) físico)
        tabPaginas[indiceV] = indexNovo;
        // Atualiza estado da pagina removida
        tabPaginas[vetQuadros[indexNovo].endV] = VAZIO;

        indice = indexNovo;
      }
    }

    // Atualizando o estado do quadro na memoria fisica
    atualizaQuadro(flag, vetQuadros, indice, indiceV, tempo);

    // Reset dos bit's R a cada 1000 leituras
    if (tempo++ % 1000 == 0) {
      for (i = 0; i < alocados; i+=1) {
        vetQuadros[i].R = FALSE;
      }
    }
  }
  fclose(arq);

  // Resultado
  printf("Executando o simulador...\n");
  printf("Arquivo de entrada: %s\n", arquivo);
  printf("Tamanho de memoria fisica: %dMB\n", tamMemFis);
  printf("Tamanho das paginas %dKB\n", tamPagina);
  printf("Algoritmo de substituicao: %s\n", algoritmo);
  printf("Numero de Faltas de Paginas: %d\n", contPageFault);
  printf("Numero de Paginas Escritas: %d\n\n\n", contWrite);

  deleteFila(fila);
  free(proxLeitura);

  return 0;
}*/


// Função para criar a tabela de páginas
int *criaTabPaginas(int tamTabPaginas) {
  int *tabPaginas = malloc(tamTabPaginas * sizeof(int));
  for (int i = 0; i < tamTabPaginas; i+=1) {
    tabPaginas[i] = VAZIO;
  }
  return tabPaginas;
}

// Função para simular o algoritmo de substituição
int substituiPagina(int tamQuadro, Frame *vetQuadros, char* algoritmo) {
  if (strcmp("NRU", algoritmo) == 0)
    return NRU(tamQuadro, vetQuadros);
  else if (strcmp("LRU", algoritmo) == 0)
    return LRU(tamQuadro, vetQuadros);
  else {
    // Adicione lógica para outros algoritmos de substituição, se necessário
    printf("Algoritmo de substituicao nao reconhecido\n");
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  char algoritmo[4];
  char arquivo[31];

  // Define Algoritmo de substituicao, Nome do log, Tamanho da pagina/quadro (8 ou 16KB), Tamanho da memoria fisica (1 a 4MB)
  strcpy(algoritmo, argv[1]);
  strcpy(arquivo, argv[2]);
  int tamPagina = atoi(argv[3]);
  int tamMemFis = atoi(argv[4]);

  // Quantidade de bits que guardam a pagina
  int paginaBits;
  // Número de paginas virtuais
  int tamTabPaginas;
  // Número de quadros na memória física
  int tamQuadro;

  if (tamPagina == 16){
    paginaBits = 14; // 2^14 ==> 8KB
    tamTabPaginas = pow(2, 18); // 32 - 14 = 18 ==> Quantidade de paginas
    tamQuadro = (tamMemFis*1024)/16; // *1024 ==> MB -> KB
  }
  else if (tamPagina == 8) {
    paginaBits = 13; // 2^13 ==> 8KB
    tamTabPaginas = pow(2, 19); // 32 - 13 = 19 ==> Quantidade de paginas
    tamQuadro = (tamMemFis*1024)/8; // *1024 ==> MB -> KB
  }

  // Quadros da memoria
  Frame *vetQuadros = malloc(tamQuadro * sizeof(Frame));

  // Paginas da tabela de pagina
  int *tabPaginas = criaTabPaginas(tamTabPaginas);

  char flag;
  int indice; // Indice(traducao) do endereco na tabela de paginas para o frame fisico
  int indiceV, tempo = 0, contPageFault = 0, contWrite = 0, alocados = 0, i;

  // Abre o log
  FILE *arq = fopen(arquivo, "r");
  if (arq == NULL) {
    printf("Erro ao abrir arquivo");
    exit(1);
  }

  while (fscanf(arq, "%c %d\n", &flag, &indiceV) == 2) {
    // Page fault
    // (indice = tabPaginas[indiceV])==VAZIO ==> Verifica se já está na tabela de páginas
    if ((indice = tabPaginas[indiceV]) == VAZIO) {
      contPageFault++;

      if (alocados < tamQuadro) { // Espaço na mem fisica disponível
        tabPaginas[indiceV] = alocados; // Atualiza a tabela de páginas (Associa o índice (página) virtual com o índice (quadro) físico)
        vetQuadros[alocados].W = FALSE;

        indice = alocados;
        alocados++;
      }

      // Memória física lotada (Substituição de página)
      else {
        int indexNovo = substituiPagina(tamQuadro, vetQuadros, algoritmo);

        if (vetQuadros[indexNovo].W == TRUE)
          contWrite++;

        // Atualiza a tabela de páginas (Associa o novo índice (página) virtual com o índice (quadro) físico)
        tabPaginas[indiceV] = indexNovo;
        // Atualiza estado da página removida
        tabPaginas[vetQuadros[indexNovo].endV] = VAZIO;

        indice = indexNovo;
      }
    }

    // Atualizando o estado do quadro na memória física
    atualizaQuadro(flag, vetQuadros, indice, indiceV, tempo);

    // Reset dos bit's R a cada 1000 leituras
    if (tempo++ % 1000 == 0) {
      for (i = 0; i < alocados; i+=1) {
        vetQuadros[i].R = FALSE;
      }
    }
  }
  fclose(arq);

  // Resultado
  printf("Executando o simulador...\n");
  printf("Arquivo de entrada: %s\n", arquivo);
  printf("Tamanho de memoria fisica: %dMB\n", tamMemFis);
  printf("Tamanho das paginas %dKB\n", tamPagina);
  printf("Algoritmo de substituicao: %s\n", algoritmo);
  printf("Numero de Faltas de Paginas: %d\n", contPageFault);
  printf("Numero de Paginas Escritas: %d\n\n\n", contWrite);

  free(vetQuadros);
  free(tabPaginas);

  return 0;
}