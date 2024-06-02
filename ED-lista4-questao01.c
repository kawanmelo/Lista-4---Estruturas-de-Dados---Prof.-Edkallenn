#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book Book;

struct book {
    char writer[50];
    char title[30];
    char publisher[30];
    char editionYear[12];
};

typedef struct element Element;

struct element {
    Book *book;
    Element *next;
};

typedef struct list List;

struct list {
    Element *head;
    int len;
};

Book* CreateLivro(char writer[], char title[], char publisher[], char editionYear[]) {
    Book *book = malloc(sizeof(Book));
    strcpy(book->writer, writer);
    strcpy(book->title, title);
    strcpy(book->publisher, publisher);
    strcpy(book->editionYear, editionYear);
    return book;
}

List* CreateList() {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->len = 0;
    return list;
}

int IsEmpty(List *list) {
    return list->head == NULL;
}

void Insert(List *list, Book *book) {
    Element *newElement = malloc(sizeof(Element));
    newElement->book = book;
    newElement->next = list->head;
    list->head = newElement;
    list->len++;
}

void Remove(List *list, Book *book) {
    if (IsEmpty(list)) {
        printf("Empty List!\n");
        return;
    }
    Element *element = list->head;
    Element *prev = NULL;
    while (element != NULL && element->book != book) {
        prev = element;
        element = element->next;
    }
    if (element == NULL) {
        printf("Book not found!\n");
        return;
    }
    if (prev == NULL) {
        list->head = element->next;
    } else {
        prev->next = element->next;
    }
    list->len--;
    free(element);
}

void Update(List *list, Book* book, Book *newBook) {
    if (IsEmpty(list)) {
        printf("Empty List!\n");
        return;
    }
    Element *element = list->head;
    while (element != NULL && element->book != book) {
        element = element->next;
    }
    if (element == NULL) {
        printf("Book not found!\n");
    } else {
        element->book = newBook;
        printf("Update was successful.\n");
    }
}

Element* GetByName(List *list, char title[]) {
    if (IsEmpty(list)) {
        printf("Empty List!\n");
        return NULL;
    }
    Element *element = list->head;
    while (element != NULL && strcmp(element->book->title, title) != 0) {
        element = element->next;
    }
    if (element == NULL) {
        printf("Book not found!\n");
        return NULL;
    } else {
        return element;
    }
}

Element* GetByWriter(List *list, char writer[]) {
    if (IsEmpty(list)) {
        printf("Empty List!\n");
        return NULL;
    }
    Element *element = list->head;
    while (element != NULL && strcmp(element->book->writer, writer) != 0) {
        element = element->next;
    }
    if (element == NULL) {
        printf("Book not found!\n");
        return NULL;
    } else {
        return element;
    }
}

void PrintBook(Book *book) {
    if (book != NULL) {
        printf("Title: %s\n", book->title);
        printf("Writer: %s\n", book->writer);
        printf("Publisher: %s\n", book->publisher);
        printf("Edition Year: %s\n", book->editionYear);
    }
}

void PrintList(List *list) {
    if (IsEmpty(list)) {
        printf("Empty List!\n");
        return;
    }
    Element *element = list->head;
    while (element != NULL) {
        PrintBook(element->book);
        element = element->next;
    }
}

void LimpaTela() {
    printf("Pressione Enter para continuar...");
    getchar();
    system("clear");
}

int main(void) {
    List *list = CreateList();
    int choice;
    char writer[50], title[30], publisher[30], editionYear[12];

    do {
        printf("\nMenu:\n");
        printf("1. Insert a book\n");
        printf("2. Remove a book\n");
        printf("3. Update a book\n");
        printf("4. Get book by title\n");
        printf("5. Get book by writer\n");
        printf("6. Print all books\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character

        switch(choice) {
            case 1:
                printf("Enter writer: ");
                fgets(writer, sizeof(writer), stdin);
                writer[strcspn(writer, "\n")] = '\0';
                printf("Enter title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                printf("Enter publisher: ");
                fgets(publisher, sizeof(publisher), stdin);
                publisher[strcspn(publisher, "\n")] = '\0';
                printf("Enter edition year: ");
                fgets(editionYear, sizeof(editionYear), stdin);
                editionYear[strcspn(editionYear, "\n")] = '\0';
                Book *book = CreateLivro(writer, title, publisher, editionYear);
                Insert(list, book);
                break;
            case 2:
                printf("Enter title of the book to remove: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                Element *elemToRemove = GetByName(list, title);
                if(elemToRemove != NULL) {
                    Remove(list, elemToRemove->book);
                    printf("Book removed successfully.\n");
                }
                LimpaTela();
                break;
            case 3:
                printf("Enter title of the book to update: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                Element *elemToUpdate = GetByName(list, title);
                if(elemToUpdate != NULL) {
                    printf("Enter new writer: ");
                    fgets(writer, sizeof(writer), stdin);
                    writer[strcspn(writer, "\n")] = '\0';
                    printf("Enter new title: ");
                    fgets(title, sizeof(title), stdin);
                    title[strcspn(title, "\n")] = '\0';
                    printf("Enter new publisher: ");
                    fgets(publisher, sizeof(publisher), stdin);
                    publisher[strcspn(publisher, "\n")] = '\0';
                    printf("Enter new edition year: ");
                    fgets(editionYear, sizeof(editionYear), stdin);
                    editionYear[strcspn(editionYear, "\n")] = '\0';
                    Book *newBook = CreateLivro(writer, title, publisher, editionYear);
                    Update(list, elemToUpdate->book, newBook);
                }
                LimpaTela();
                break;
            case 4:
                printf("Enter title of the book: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                Element *elemByName = GetByName(list, title);
                if(elemByName != NULL) {
                    PrintBook(elemByName->book);
                }
                LimpaTela();
                break;
            case 5:
                printf("Enter writer of the book: ");
                fgets(writer, sizeof(writer), stdin);
                writer[strcspn(writer, "\n")] = '\0';
                Element *elemByWriter = GetByWriter(list, writer);
                if(elemByWriter != NULL) {
                    PrintBook(elemByWriter->book);
                }
                LimpaTela();
                break;
            case 6:
                PrintList(list);
                LimpaTela();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                LimpaTela();
        }
    } while(choice != 0);

    return 0;
}