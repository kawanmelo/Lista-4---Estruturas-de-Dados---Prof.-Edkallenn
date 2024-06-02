#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** Função : Gerenciar um sistema de atendimento utilizando uma estrutura de Fila.
** Autor : Kawan Melo - 3º período turma F 2024.1
** Data : 25.05.2024
** Observações: Null
*/

#define MAX 10

typedef struct{
  int id;
  char nome[30];
  int ativo;
}Paciente;

typedef struct{
  Paciente vetor[MAX];
  int inicio;
  int fim;
  int quantidade;
}Fila;


Fila cria_fila(){
  Fila fila;
  fila.inicio = 0;
  fila.fim = -1;
  fila.quantidade = 0;
  return fila;
}

Paciente cria_paciente(int id, char nome[]){
  Paciente paciente;
  paciente.id = id;
  strcpy(paciente.nome, nome);
  paciente.ativo = 1;
  return paciente;
}

int is_empty(Fila *fila){
  return (fila->quantidade == 0);
}

int is_full(Fila *fila){
  return (fila->quantidade == MAX);
}

int adicionar_paciente(Fila *fila, Paciente paciente){
  if(is_full(fila)){
    printf("Fila cheia!\n");
    return 0;
  }
  fila->fim = (fila->fim + 1) % MAX;
  fila->vetor[fila->fim] = paciente;
  fila->quantidade++;
  return 1;
}

Paciente proximo_paciente(Fila* fila){
  Paciente paciente;
  if(is_empty(fila)){
    printf("Não há pacientes na fila!\n");
    return paciente;
  }
  paciente = fila->vetor[fila->inicio];
  fila->inicio = (fila->inicio + 1) % MAX;
  fila->quantidade--;
  return paciente;
}

int quantidade_pacientes(Fila *fila){
  return fila->quantidade;
}

void exibe_fila_pacientes(Fila *fila){
  if(is_empty(fila)){
    printf("Não há pacientes na fila!\n");
    return;
  }
  int i = fila->inicio;
  printf("[ ");
  for(int count = 0; count < fila->quantidade; count++){
    printf("Paciente %d: %s, ", count, fila->vetor[i].nome);
    i = (i + 1) % MAX;
  }
  printf("\b\b ]");
}

void LimpaTela() {
  printf("Aperte enter para continuar...\n");
  getchar();
  system("clear");  
}

int main(void) {
  Fila fila = cria_fila();
  int choice;
  Paciente paciente;
  int id;
  char nome[30];

  do {
    printf("\nMenu:\n");
    printf("1. Adicionar paciente\n");
    printf("2. Próximo paciente\n");
    printf("3. Quantidade de pacientes na fila\n");
    printf("4. Exibir fila de pacientes\n");
    printf("0. Encerrar\n");
    printf("Digite a sua escolha: ");
    scanf("%d", &choice);
    getchar(); // Consumir o '\n' deixado pelo scanf

    switch (choice) {
      case 1:
        printf("Digite o ID do paciente: ");
        scanf("%d", &id);
        getchar(); // Consumir o '\n' deixado pelo scanf
        printf("Digite o nome do paciente: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; // Remover o '\n' final
        paciente = cria_paciente(id, nome);
        if (adicionar_paciente(&fila, paciente)) {
          printf("Paciente adicionado com sucesso.\n");
        }
        LimpaTela();
        break;
      case 2: {
        paciente = proximo_paciente(&fila);
        if (paciente.ativo == 1) {
          printf("Chamando o próximo paciente: %d - %s\n", paciente.id, paciente.nome);
          LimpaTela();
          break;
        }
        LimpaTela();
        break;
      }
      case 3:
        printf("Quantidade de pacientes na fila: %d\n", quantidade_pacientes(&fila));
        LimpaTela();
        break;
      case 4:
        exibe_fila_pacientes(&fila);
        LimpaTela();
        break;
      case 0:
        printf("Encerrando...\n");
        break;
      default:
        printf("Escolha inválida. Tente novamente.\n");
        LimpaTela();
    }
  } while (choice != 0);

  return 0;
}