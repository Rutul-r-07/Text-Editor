
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>

#define MAX 200
#define SIZE 40

char text[MAX] = "";
char undoStack[SIZE][MAX];
char redoStack[SIZE][MAX];

int undoTop = -1;
int redoTop = -1;

char status[50] = "Ready to type";

/* Push text into stack */
void push(char stack[SIZE][MAX], int *top, char str[]) {
    if (*top < SIZE - 1) {
        (*top)++;
        strcpy(stack[*top], str);
    }
}

/* Pop text from stack */
int pop(char stack[SIZE][MAX], int *top, char str[]) {
    if (*top == -1)
        return 0;

    strcpy(str, stack[*top]);
    (*top)--;

    return 1;
}

/* Draw text with automatic line wrapping */
void drawText() {
    int i, j = 0, y = 165;
    char line[75];

    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n' || j >= 65) {
            line[j] = '\0';
            outtextxy(45, y, line);
            y += 20;
            j = 0;

            if (text[i] == '\n')
                continue;
        }

        if (y > 385)
            break;

        line[j++] = text[i];
    }

    line[j] = '\0';

    if (y <= 385)
        outtextxy(45, y, line);
}

/* Draw the GUI */

void display() {
    setbkcolor(WHITE);
    cleardevice();

    setfillstyle(SOLID_FILL, BLUE);
    bar(0, 0, 640, 70);

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(190, 22, "TEXT EDITOR");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(25, 85, 145, 120);
    bar(155, 85, 275, 120);
    bar(285, 85, 405, 120);
    bar(415, 85, 535, 120);

    setcolor(BLACK);
    outtextxy(45, 98, "UNDO");
    outtextxy(175, 98, "REDO");
    outtextxy(305, 98, "CLEAR");
    outtextxy(435, 98, "SAVE");

    setfillstyle(SOLID_FILL, WHITE);
    bar(26, 136, 614, 404);

    setcolor(BLUE);
    rectangle(25, 135, 615, 405);

    setcolor(BLACK);
    outtextxy(40, 145, "Your Document:");

    /* Display each line */
    {
        int i = 0, j = 0, y = 170;
        char line[70];

        while (text[i] != '\0' && y < 390) {
            if (text[i] == '\n' || j >= 65) {
                line[j] = '\0';
                outtextxy(40, y, line);
                y += 20;
                j = 0;

                if (text[i] == '\n') {
                    i++;
                    continue;
                }
            }

            line[j++] = text[i++];
        }

        line[j] = '\0';

        if (j > 0 && y < 390)
            outtextxy(40, y, line);
    }

    setcolor(DARKGRAY);
    outtextxy(25, 420, "Type normally | Backspace: Delete");
    outtextxy(25, 440, "Enter: New line | TAB: Commands");
    outtextxy(25, 460, "ESC: Exit");
    outtextxy(25, 485, status);
}


/* Undo operation */
void undo() {
    char temp[MAX];

    if (pop(undoStack, &undoTop, temp)) {
        push(redoStack, &redoTop, text);
        strcpy(text, temp);
        strcpy(status, "Undo successful");
    } else {
        strcpy(status, "Nothing to undo");
    }
}

/* Redo operation */
void redo() {
    char temp[MAX];

    if (pop(redoStack, &redoTop, temp)) {
        push(undoStack, &undoTop, text);
        strcpy(text, temp);
        strcpy(status, "Redo successful");
    } else {
        strcpy(status, "Nothing to redo");
    }
}

/* Clear operation */
void clearText() {
    if (text[0] != '\0') {
        push(undoStack, &undoTop, text);
        text[0] = '\0';
        redoTop = -1;
        strcpy(status, "Document cleared");
    } else {
        strcpy(status, "Document is already empty");
    }
}

/* Save operation */
void saveText() {
    FILE *fp;

    fp = fopen("text.txt", "w");

    if (fp != NULL) {
        fprintf(fp, "%s", text);
        fclose(fp);
        strcpy(status, "Saved successfully to text.txt");
    } else {
        strcpy(status, "Unable to save file");
    }
}

/* Command menu inside graphics window */
void commandMenu() {
    int key;

    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(150, 170, 490, 350);

    setcolor(BLACK);
    rectangle(150, 170, 490, 350);

    outtextxy(220, 190, "COMMAND MENU");
    outtextxy(185, 220, "U - Undo");
    outtextxy(185, 240, "R - Redo");
    outtextxy(185, 260, "C - Clear");
    outtextxy(185, 280, "S - Save");
    outtextxy(185, 320, "Press a key");

    key = getch();

    if (key == 'u' || key == 'U')
        undo();
    else if (key == 'r' || key == 'R')
        redo();
    else if (key == 'c' || key == 'C')
        clearText();
    else if (key == 's' || key == 'S')
        saveText();
    else
        strcpy(status, "Command cancelled");
}

/* Main function */
int main() {
    int gd = DETECT, gm;
    int key;
    char ch;

    /* Change this path if your BGI folder is elsewhere */
    initgraph(&gd, &gm, "C:\\TC\\BGI");

    display();

    while (1) {
        key = getch();

        /* Exit */
        if (key == 27)
            break;

        /* Tab opens command menu */
        if (key == 9) {
            commandMenu();
            display();
            continue;
        }

        /* Ignore extended keys */
        if (key == 0) {
            getch();
            continue;
        }

        /* Backspace */
        if (key == 8) {
            if (strlen(text) > 0) {
                push(undoStack, &undoTop, text);
                text[strlen(text) - 1] = '\0';
                redoTop = -1;
                strcpy(status, "Character deleted");
            }
        }

        /* Enter inserts new line */
        else if (key == 13) {
            if (strlen(text) < MAX - 1) {
                push(undoStack, &undoTop, text);
                strcat(text, "\n");
                redoTop = -1;
            }
        }

        /* Normal typing */
        else if (key >= 32 && key <= 126) {
            if (strlen(text) < MAX - 1) {
                ch = (char)key;
                push(undoStack, &undoTop, text);
                strncat(text, &ch, 1);
                redoTop = -1;
                strcpy(status, "Editing document");
            } else {
                strcpy(status, "Document limit reached");
            }
        }

        display();
    }

    closegraph();
    return 0;
}
