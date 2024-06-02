#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
** Função : Classifica os elementos de um vetor em ordem crescente usando o algoritmo "Classificação Por Seleção"
** Autor : Kawan Melo - 3º período turma F 2024.1
** Data : 23.05.2024
** Observações: Utilizei a função "clear_keyboard_buffer()" para limpar o buffer
*do teclado e assim conseguir utilizar corretamente a função "getchar()".
*/

void clear_keyboard_buffer(void) {
  int c = 0;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
  return;
}

void ClassificaPorSelecao(int vetor[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    for (int j = i + 1; j < tamanho; j++) {
      int temp = vetor[j];
      if (vetor[j] < vetor[i]) {
        vetor[j] = vetor[i];
        vetor[i] = temp;
      }
    }
  }
}

int main(void) {
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
  printf("ORDENE O VETOR\n");
  printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
  int tam;
  printf("Digite o tamanho do vetor: ");
  scanf("%d", &tam);

  int *vetor = (int *)malloc(sizeof(int) * tam);
  if (vetor == NULL) {
    printf("Erro na alocação de memória.");
    exit(1);
  }

  srand((unsigned)time(NULL));
  for (int i = 0; i < tam; i++) {
    vetor[i] = rand() % 1000;
  }
  printf("Vetor com tamanho %d e elementos aleatórios criado!\n\n", tam);

  printf("Vetor antes da ordenação = [ ");
  for (int i = 0; i < tam; i++) {
    printf("%d, ", vetor[i]);
  }
  printf("\b\b ]\n");

  clear_keyboard_buffer();
  printf("Pressione a tecla 'enter' para ordenar o vetor...");
  getchar();
  ClassificaPorSelecao(vetor, tam);

  printf("Vetor ordenado = [ ");
  for (int i = 0; i < tam; i++) {
    printf("%d, ", vetor[i]);
  }
  printf("\b\b ]\n");

  return 0;
}