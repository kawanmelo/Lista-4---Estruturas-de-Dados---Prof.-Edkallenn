#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** Função : Simular uma lista de compras.
** Autor : Kawan Melo - 3º período turma F 2024.1
** Data : 24.05.2024
** Observações: Null
*/

typedef struct item Item;
struct item{
  int id;
  char description[30];
  int quant;
};

typedef struct element Element;
struct element{
  Item *item;
  Element *next;
};

typedef struct shoppingList ShoppingList;
struct shoppingList{
  Element *head;
  int tam;
};

Item* CreateItem(int id,char description[], int quant){
  Item *item = malloc(sizeof(Item));
  item->id = id;
  strcpy(item->description, description);
  item->quant = quant;
  return item;
}

ShoppingList* CreateShoppingList(){
  ShoppingList *shoppingList = malloc(sizeof(ShoppingList));
  shoppingList->head = NULL;
  return shoppingList;
}

void Add(ShoppingList *shoppingList, Item *item){
  Element *element = malloc(sizeof(Element));
  element->item = item;
  element->next = shoppingList->head;
  shoppingList->head = element;
  shoppingList->tam++;
}

int IsEmpty(ShoppingList *shoppingList){
  return (shoppingList->head == NULL);
}

int Remove(ShoppingList *shoppingList, int id){
  if(IsEmpty(shoppingList)){
    printf("Empty list!\n");
    return 0;
  }
  Element *current = shoppingList->head;
  Element *previous = NULL;
  while(current != NULL && current->item->id != id){
    previous = current;
    current = current->next;
  }
  if(current == NULL){
    printf("Elemento não encontrado!\n");
  }
  if(previous == NULL){
    shoppingList->head = current->next;
    free(current);
    shoppingList->tam--;
    return 1;
  }
  else{
    previous->next = current->next;
    free(current);
    shoppingList->tam--;
    return 1;
  }
}

void GetById(ShoppingList *shoppingList, int id){
  if(IsEmpty(shoppingList)){
    printf("Empty list!\n");
    return;
  }
  Element *element = shoppingList->head;
  while(element != NULL && element->item->id != id){
    element = element->next;
  }
  if(element == NULL){
    printf("Item not found!\n");
    return;
  }
  printf("Item : %s\n", element->item->description);
  printf("Quantity : %d\n", element->item->quant);
}

void PrintList(ShoppingList *shoppingList){
  if(IsEmpty(shoppingList)){
    printf("Empty list!\n");
    return;
  }
  Element *element = shoppingList->head;
  while(element != NULL){
    printf("Item : %s\n", element->item->description);
    printf("Quantity : %d\n", element->item->quant);
    element = element->next;
  }
}

void Destroy(ShoppingList *shoppingList){
  Element *element = shoppingList->head;
  while(element != NULL){
    Element *aux = element;
    element = element->next;
    free(aux);
  }
  free(shoppingList);
}

void LimpaTela() {
  printf("Type enter to continue...");
  getchar();
  system("clear");  
}


int main(void) {
  ShoppingList *shoppingList = CreateShoppingList();
  int choice;
  int id;
  char description[30];
  int quant;

  do {
    printf("\nMenu:\n");
    printf("1. Add item\n");
    printf("2. Remove item\n");
    printf("3. Search item by ID\n");
    printf("4. Print List\n");
    printf("0. Exit\n");
    printf("Type your choice: ");
    scanf("%d", &choice);
    getchar(); // Consumir o '\n' deixado pelo scanf

    switch (choice) {
      case 1:
        printf("Type the item ID: ");
        scanf("%d", &id);
        getchar(); // Consumir o '\n' deixado pelo scanf
        printf("Type the item description: ");
        fgets(description, sizeof(description), stdin);
        description[strcspn(description, "\n")] = '\0'; // Remover o '\n' final
        printf("Type the quantity: ");
        scanf("%d", &quant);
        getchar(); // Consumir o '\n' deixado pelo scanf
        Item *item = CreateItem(id, description, quant);
        Add(shoppingList, item);
        printf("Item added with sucess.\n");
        LimpaTela();
        break;
      case 2:
        printf("Type the item ID to be removed: ");
        scanf("%d", &id);
        getchar(); // Consumir o '\n' deixado pelo scanf
        if(Remove(shoppingList, id)){
            printf("Item removed with sucess.\n");
            LimpaTela();
        }
        LimpaTela();
        break;
      case 3:
        printf("Type the item ID: ");
        scanf("%d", &id);
        getchar(); // Consumir o '\n' deixado pelo scanf
        GetById(shoppingList, id);
        LimpaTela();
        break;
      case 4:
        PrintList(shoppingList);
        LimpaTela();
        break;
      case 0:
        printf("Closing...\n");
        Destroy(shoppingList);
        break; 
      default:
        printf("Invalid option, try again...");
        LimpaTela();
        break;
    }
  } while (choice != 0);

  return 0;
}