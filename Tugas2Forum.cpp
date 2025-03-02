#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char item) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++s->top] = item;
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->items[s->top--];
}

char peek(Stack *s) {
    return s->items[s->top];
}

int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

void infixToPostfix(char *exp) {
    Stack stack;
    initStack(&stack);
    char output[MAX];
    int j = 0;
    
    for (int i = 0; exp[i] != '\0'; i++) {
        if (isalnum(exp[i])) {
            output[j++] = exp[i];
        } else if (exp[i] == '(') {
            push(&stack, exp[i]);
        } else if (exp[i] == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                output[j++] = pop(&stack);
            }
            pop(&stack);
        } else {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(exp[i])) {
                output[j++] = pop(&stack);
            }
            push(&stack, exp[i]);
        }
    }
    
    while (!isEmpty(&stack)) {
        output[j++] = pop(&stack);
    }
    output[j] = '\0';
    printf("Postfix: %s\n", output);
}

void postfixToInfix(char *exp) {
    Stack stack;
    initStack(&stack);
    
    for (int i = 0; exp[i] != '\0'; i++) {
        if (isalnum(exp[i])) {
            char str[2] = {exp[i], '\0'};
            push(&stack, exp[i]);
        } else {
            char op2 = pop(&stack);
            char op1 = pop(&stack);
            printf("(%c%c%c)\n", op1, exp[i], op2);
            push(&stack, 'X'); 
        }
    }
}

int main() {
    char infix[] = "a+b*(c^d-e)^(f+g*h)-i";
    printf("Infix: %s\n", infix);
    infixToPostfix(infix);
    
    char postfix[] = "abcd^e-fgh*+^*+i-";
    printf("Postfix: %s\n", postfix);
    postfixToInfix(postfix);
    
    return 0;
}

