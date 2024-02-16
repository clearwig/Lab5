/*
Trae Forde
February 8, 2024
COP 3502C
Professor Torosdagli
*/

#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the linked list
typedef struct node {
    char letter;
    struct node* next;
} node;

// Returns the number of nodes in the linked list.
int length(node* head) {
    int count = 0;
    node* current = head;
   
    //Traversing the linked list and count the nodes.
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Converts the linked list to a C-style string.
// If the linked list is head -> |a|->|b|->|c|,
// then the toCString function will return "abc".
char* toCString(node* head) {
    //Calculatng the length of the linked list.
    int len = length(head);
    //Allocating memory for the C-style string.
    char* str = (char*)malloc((len + 1) * sizeof(char));
    if (str == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    //Traversing the linked list and copy characters to the string.
    int i = 0;
    node* current = head;
    while (current != NULL) {
        str[i] = current->letter;
        current = current->next;
        i++;
    }
    
    //Null-terminating the string.
    str[i] = '\0'; 
    return str;
}

// Inserts a character at the end of the linked list.
// If the linked list is head -> |a|->|b|->|c|,
// then insertChar(&head, 'x') will update the linked list as follows:
// head -> |a|->|b|->|c|->|x|.
void insertChar(node** pHead, char c) {
    //Creating a new node.
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->letter = c;
    newNode->next = NULL;
    
    //If the linked list is empty, the new node becomes the head.
    if (*pHead == NULL) {
        *pHead = newNode;
    } else {
    //Otherwise, traverse the list to the end and append the new node.
        node* current = *pHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Deletes all nodes in the linked list.
void deleteList(node** pHead) {
    // Traversing the linked list and free memory for each node.
    node* current = *pHead;
    node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    //Setting the head to NULL after deleting all nodes.
    *pHead = NULL; 
}

int main(void) {
    int i, strLen, numInputs;
    node* head = NULL;
    char* str;
    char c;
    FILE* inFile = fopen("input.txt", "r");
    if (inFile == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    fscanf(inFile, " %d\n", &numInputs);
    while (numInputs-- > 0) {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++) {
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }
        str = toCString(head);
        printf("String is: %s\n", str);
        free(str);
        deleteList(&head);
        if (head != NULL) {
            printf("deleteList is not correct!\n");
            break;
        }
    }
    fclose(inFile);
    return 0;
}