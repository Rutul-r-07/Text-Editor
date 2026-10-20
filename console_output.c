#include <stdio.h>
#include <string.h>

#define MAX 200
#define SIZE 20

char text[MAX] = "";
char undoStack[SIZE][MAX];
char redoStack[SIZE][MAX];

int undoTop = -1;
int redoTop = -1;

void push(char stack[SIZE][MAX], int *top, char str[]) {
    if (*top < SIZE - 1) {
        (*top)++;
        strcpy(stack[*top], str);
    }
}

int pop(char stack[SIZE][MAX], int *top, char str[]) {
    if (*top == -1)
        return 0;

    strcpy(str, stack[*top]);
    (*top)--;

    return 1;
}

void undo() {
    char temp[MAX];

    if (pop(undoStack, &undoTop, temp)) {
        push(redoStack, &redoTop, text);
        strcpy(text, temp);
        printf("\nUndo successful!\n");
    } else {
        printf("\nNothing to undo!\n");
    }
}

void redo() {
    char temp[MAX];

    if (pop(redoStack, &redoTop, temp)) {
        push(undoStack, &undoTop, text);
        strcpy(text, temp);
        printf("\nRedo successful!\n");
    } else {
        printf("\nNothing to redo!\n");
    }
}

void clearText() {
    if (text[0] != '\0') {
        push(undoStack, &undoTop, text);
        text[0] = '\0';
        redoTop = -1;
        printf("\nDocument cleared!\n");
    } else {
        printf("\nDocument is already empty!\n");
    }
}

void saveText() {
    FILE *fp = fopen("text.txt", "w");

    if (fp != NULL) {
        fprintf(fp, "%s", text);
        fclose(fp);
        printf("\nDocument saved to text.txt!\n");
    } else {
        printf("\nError saving document!\n");
    }
}

int main() {
    int choice;
    char input[MAX];

    while (1) {
        printf("\n==============================\n");
        printf("       TEXT EDITOR PROJECT\n");
        printf("   Undo and Redo using Stacks\n");
        printf("==============================\n");

        printf("\nCurrent Document:\n");
        printf("------------------------------\n");
        printf("%s\n", text);
        printf("------------------------------\n");

        printf("\n1. Enter/Edit Text");
        printf("\n2. Undo");
        printf("\n3. Redo");
        printf("\n4. Clear");
        printf("\n5. Save");
        printf("\n6. Exit");

        printf("\n\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input!\n");
            return 0;
        }

        getchar();

        if (choice == 1) {
            printf("\nEnter new text: ");

            if (fgets(input, MAX, stdin) != NULL) {
                input[strcspn(input, "\n")] = '\0';

                push(undoStack, &undoTop, text);
                strcpy(text, input);
                redoTop = -1;

                printf("\nText updated successfully!\n");
            }
        } else if (choice == 2) {
            undo();
        } else if (choice == 3) {
            redo();
        } else if (choice == 4) {
            clearText();
        } else if (choice == 5) {
            saveText();
        } else if (choice == 6) {
            printf("\nExiting Text Editor...\n");
            break;
        } else {
            printf("\nInvalid choice! Try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
    }

    return 0;
}
