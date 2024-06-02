#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** Função : Gerenciar uma pilha de processos
** Autor : Kawan Melo - 3º período turma F 2024.1
** Data : 23.05.2024
** Observações: Null
*/

typedef struct process Process;
struct process{
  int id;
  char description[30];
};

typedef struct element Element;
struct element{
  Process *process;
  Element *next;
};

typedef struct stack Stack;
struct stack{
  Element *head;
};

Process* CreateProcess(int id, char description[]){
  Process *process = malloc(sizeof(Process));
  process->id = id;
  strcpy(process->description, description);
  return process;
}

Stack* CreateStack(){
  Stack *stack = malloc(sizeof(Stack));
  stack->head = NULL;
  return stack;
}

void Push(Stack *stack, Process *process){
  Element *element = malloc(sizeof(Element));
  element->process = process;
  element->next = stack->head;
  stack->head = element;
}

int IsEmpty(Stack *stack){
  return (stack->head == NULL);
}

Process* Pop(Stack *stack){
  if(IsEmpty(stack)){
    printf("Empty stack!");
    return NULL;
  }
  Process *process = CreateProcess(stack->head->process->id,stack->head->process->description);
  Element *aux = stack->head;
  stack->head = stack->head->next;
  free(aux);
  return process;
}

void Peek(Stack *stack){
  if(IsEmpty(stack)){
    printf("Empty stack!");
    return;
  }
  Process *process = CreateProcess(stack->head->process->id,stack->head->process->description);
  printf("Current states of stack:\n");
  printf("Process #%d - %s\n", process->id, process->description);
}

void Print(Stack *stack){
  if(IsEmpty(stack)){
    printf("Empty stack!\n");
    return;
  }
  Element *element = stack->head;
  printf("Current stack content:\n");
  while(element != NULL){
    printf("Process #%d - %s\n", element->process->id, element->process->description);
    element = element->next;
  }
}


void Destroy(Stack *stack){
  Element *element = stack->head;
  while(element != NULL){
    Element *aux = element->next;
    free(element);
    element = aux;
  }
  free(stack);
}

void Clear(){
  printf("type enter to continue...");
  getchar();
  system("clear");
}

int main(void) {
  Stack *stack = CreateStack();
  int choice;
  int id;
  char description[30];

  do {
    printf("\nMenu:\n");
    printf("1. Add process on stack\n");
    printf("2. Remove process from stack\n");
    printf("0. Exit\n");
    printf("Type your choice: ");
    scanf("%d", &choice);
    getchar(); // consumir o '\n' deixado pelo scanf

    switch(choice) {
      case 1:
        printf("Type the process identificator: ");
        scanf("%d", &id);
        getchar(); // consumir o '\n' deixado pelo scanf
        printf("Type the process description: ");
        fgets(description, sizeof(description), stdin);
        description[strcspn(description, "\n")] = '\0'; // remover o '\n' final
        Process *process = CreateProcess(id, description);
        Push(stack, process);
        printf("Process added with sucess.\n");
        Peek(stack);
        Clear();
        break;
      case 2:
        if(!IsEmpty(stack)){
          Process *removedProcess = Pop(stack);
          printf("Removed the process #%d - %s\n", removedProcess->id, removedProcess->description);
          free(removedProcess);
          Print(stack);
        } else {
          printf("Empty stack!\n");
        }
        Clear();
        break;
      case 0:
        printf("Closing...\n");
        Destroy(stack);
        break;
      default:
        printf("Invalid choice, try again.\n");
        Clear();
    }
  } while (choice != 0);

  return 0;
}