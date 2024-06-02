#include <stdio.h>
#include <stdlib.h>

/*
** Função : Implementar uma pilha de números reais
** Autor : Kawan Melo - 3º período turma F 2024.1
** Data : 22.05.2024
** Observações: Null
*/

typedef struct celula Celula;

struct celula {
  double dado;
  Celula *proximo;
};

typedef struct pilha Pilha;

struct pilha{
  Celula *topo;
  int tamanho;
};

Pilha* CreatePilha(){
  Pilha *pilha = malloc(sizeof(Pilha));
  pilha->topo = NULL;
  pilha->tamanho = 0;
  return pilha;
}

void Push(Pilha *pilha, double dado){
  Celula *novo = malloc(sizeof(Celula));
  novo->dado = dado;
  novo->proximo = pilha->topo;
  pilha->topo = novo;
  pilha->tamanho++;
}

int IsEmpty(Pilha *pilha){
  return pilha->topo == NULL;
}

double Pop(Pilha *pilha){
  if(IsEmpty(pilha)){
    printf("Pilha vazia!\n");
    exit(1);
  }
  Celula *aux = pilha->topo;
  double valor = aux->dado;
  pilha->topo = aux->proximo;
  free(aux);
  pilha->tamanho--;
  return valor;
}

void Peek(Pilha *pilha){
  if(IsEmpty(pilha)){
    printf("Pilha vazia!\n");
  }
  //exibir o topo da pilha
  else{
    printf("Topo da pilha: %.2f\n", pilha->topo->dado);
  }
}

void Print(Pilha *pilha){
  if(IsEmpty(pilha)){
    printf("Pilha vazia!\n");
    exit(1);
  }
  Celula *aux = pilha->topo;
  printf("[ ");
  while(aux != NULL){
    printf("%.2f, ", aux->dado);
    aux = aux->proximo;
  }
  printf("\b\b ]\n");
}

void Destroy(Pilha *pilha){
  Celula *aux = pilha->topo;
  while(aux != NULL){
    Celula *temp = aux->proximo;
    free(aux);
    aux = temp;
  }
  free(pilha);
}

void LimpaTela()
{
  printf("Aperte enter para continuar...");
  getchar();
  system("clear");  
}

int main(void) {
    Pilha *pilha = CreatePilha();
    int choice;
    double valor;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir um número na pilha \n");
        printf("2. Remover um número da pilha \n");
        printf("3. Ver o topo da pilha \n");
        printf("4. Exibir toda a pilha \n");
        printf("0. Sair\n");
        printf("Digite a sua escolha: ");
        scanf("%d", &choice);
        getchar(); // consumir o '\n' deixado pelo scanf

        switch (choice) {
            case 1:
              printf("Digite um número para inserir na pilha: ");
              scanf("%lf", &valor);
              getchar(); // consumir o '\n' deixado pelo scanf
              Push(pilha, valor);
              printf("Número inserido com sucesso.\n");
              LimpaTela();
              break;
            case 2:
              if (!IsEmpty(pilha)) {
                Print(pilha);
                valor = Pop(pilha);
                printf("Número %.2f removido da pilha.\n", valor);
                Print(pilha);
              }
              printf("Empty List!");
                LimpaTela();
                break;
            case 3:
              Peek(pilha);
              LimpaTela();
              break;
            case 4:
              Print(pilha);
              LimpaTela();
              break;
            case 0:
              printf("Saindo...\n");
              break;
            default:
              printf("Escolha inválida. Tente novamente.\n");
              LimpaTela();
        }
    } while (choice != 0);

    Destroy(pilha);
    return 0;
}