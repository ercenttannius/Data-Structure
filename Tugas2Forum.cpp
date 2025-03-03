#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Struktur Stack untuk karakter
typedef struct {
    char data[MAX];
    int top;
} CharStack;

// Struktur Stack untuk string
typedef struct {
    char data[MAX][MAX];
    int top;
} StringStack;

// Inisialisasi stack karakter
void initCharStack(CharStack *s) {
    s->top = -1;
}

// Inisialisasi stack string
void initStringStack(StringStack *s) {
    s->top = -1;
}

// Cek apakah stack kosong
int isCharStackEmpty(CharStack *s) {
    return s->top == -1;
}

// Push elemen ke stack karakter
void pushChar(CharStack *s, char value) {
    s->data[++(s->top)] = value;
}

// Pop elemen dari stack karakter
char popChar(CharStack *s) {
    if (isCharStackEmpty(s)) return '\0';
    return s->data[(s->top)--];
}

// Melihat elemen teratas stack karakter
char peekChar(CharStack *s) {
    if (isCharStackEmpty(s)) return '\0';
    return s->data[s->top];
}

// Push string ke stack string
void pushString(StringStack *s, char *value) {
    strcpy(s->data[++(s->top)], value);
}

// Pop string dari stack string
void popString(StringStack *s, char *res) {
    if (s->top >= 0) {
        strcpy(res, s->data[(s->top)--]);
    }
}

// Prioritas operator
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Konversi Infix ke Postfix
void infixToPostfix(char *infix, char *postfix) {
    CharStack s;
    initCharStack(&s);
    int i, j = 0;
    
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            pushChar(&s, ch);
        } else if (ch == ')') {
            while (!isCharStackEmpty(&s) && peekChar(&s) != '(') {
                postfix[j++] = popChar(&s);
            }
            popChar(&s);
        } else {
            while (!isCharStackEmpty(&s) && precedence(peekChar(&s)) >= precedence(ch)) {
                postfix[j++] = popChar(&s);
            }
            pushChar(&s, ch);
        }
    }

    while (!isCharStackEmpty(&s)) {
        postfix[j++] = popChar(&s);
    }
    postfix[j] = '\0';
}

// Konversi Postfix ke Infix
void postfixToInfix(char *postfix, char *infix) {
    StringStack s;
    initStringStack(&s);
    char temp[MAX], op1[MAX], op2[MAX];
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch[2] = {postfix[i], '\0'};

        if (isalnum(postfix[i])) {
            pushString(&s, ch);
        } else {
            popString(&s, op2);
            popString(&s, op1);
            sprintf(temp, "(%s%c%s)", op1, postfix[i], op2);
            pushString(&s, temp);
        }
    }

    popString(&s, infix);
}

int main() {
    char infix[MAX], postfix[MAX], convertedInfix[MAX];
    int choice;

    while (1) {
        printf("MENU:\n");
        printf("1. Konversi Infix ke Postfix\n");
        printf("2. Konversi Postfix ke Infix\n");
        printf("3. Keluar\n");
        printf("Pilih (1/2/3): ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            printf("Masukkan ekspresi Infix: ");
            scanf("%s", infix);
            infixToPostfix(infix, postfix);
            printf("Postfix: %s\n", postfix);
        } else if (choice == 2) {
            printf("Masukkan ekspresi Postfix: ");
            scanf("%s", postfix);
            postfixToInfix(postfix, convertedInfix);
            printf("Infix: %s\n", convertedInfix);
        } else if (choice == 3) {
            printf("Terima kasih!\n");
            return 0;
        } else {
            printf("Pilihan tidak valid, coba lagi!\n");
        }
    }
}
