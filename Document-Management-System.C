#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Document {
    int id;
    char title[100];
    char author[100];
    char content[1000];
    struct Document* next;
};

struct Document* head = NULL;
struct Document* deletedHead = NULL;

struct Document* createDocument(int id, const char* title, const char* author, const char* content) {
    struct Document* newDoc = (struct Document*)malloc(sizeof(struct Document));
    newDoc->id = id;
    strcpy(newDoc->title, title);
    strcpy(newDoc->author, author);
    strcpy(newDoc->content, content);
    newDoc->next = NULL;
    return newDoc;
}

void addDocument(int id, const char* title, const char* author, const char* content) {
    struct Document* newDoc = createDocument(id, title, author, content);
    if (head == NULL) {
        head = newDoc;
    } else {
        struct Document* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newDoc;
    }
}

struct Document* searchDocument(const char* title) {
    struct Document* current = head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void displayDocument(struct Document* doc) {
    if (doc != NULL) {
        printf("Document ID: %d\n", doc->id);
        printf("Title: %s\n", doc->title);
        printf("Author: %s\n", doc->author);
        printf("Content: %s\n", doc->content);
    } else {
        printf("Document not found.\n");
    }
}

void deleteDocument(const char* title) {
    struct Document* current = head;
    struct Document* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = deletedHead;
            deletedHead = current;
            printf("Document deleted successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Document not found.\n");
}

void restoreDocument(const char* title) {
    struct Document* current = deletedHead;
    struct Document* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            if (prev == NULL) {
                deletedHead = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = head;
            head = current;
            printf("Document restored successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Document not found in the deleted documents list.\n");
}

void freeDocumentList(struct Document* list) {
    struct Document* current = list;
    while (current != NULL) {
        struct Document* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    printf("Document Management System\n");
    printf("==========================\n");

    while (1) {
        int choice;
        printf("\nOptions:\n");
        printf("1. Add a Document\n");
        printf("2. Search for a Document\n");
        printf("3. Delete a Document\n");
        printf("4. Restore a Deleted Document\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int id;
                char title[100];
                char author[100];
                char content[1000];
                printf("Enter the Document ID: ");
                scanf("%d", &id);
                printf("Enter the Document Title: ");
                scanf("%s", &title);
                printf("Enter the Document Author: ");
                scanf("%s", &author);
                printf("Enter the Document Content: ");
                scanf("%s", &content);
                addDocument(id, title, author, content);
                printf("Document added successfully.\n");
                break;
            }
            case 2: {
                char searchTitle[100];
                printf("Enter the title of the document to search: ");
                scanf("%s", searchTitle);
                struct Document* foundDoc = searchDocument(searchTitle);
                displayDocument(foundDoc);
                break;
            }
            case 3: {
                char deleteTitle[100];
                printf("Enter the title of the document to delete: ");
                scanf("%s", deleteTitle);
                deleteDocument(deleteTitle);
                break;
            }
            case 4: {
                char restoreTitle[100];
                printf("Enter the title of the document to restore: ");
                scanf("%s", restoreTitle);
                restoreDocument(restoreTitle);
                break;
            }
            case 5:
                freeDocumentList(head);
                freeDocumentList(deletedHead);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
