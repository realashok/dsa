#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// --------------------- STACK FOR CHAR ---------------------
char stackChar[MAX];
int topChar = -1;

void pushChar(char c) {
    stackChar[++topChar] = c;
}

char popChar() {
    return stackChar[topChar--];
}

char peekChar() {
    return stackChar[topChar];
}

int isEmptyChar() {
    return topChar == -1;
}

// --------------------- STACK FOR STRING ---------------------
char stackStr[MAX][MAX];
int topStr = -1;

void pushStr(char *str) {
    strcpy(stackStr[++topStr], str);
}

char* popStr() {
    return stackStr[topStr--];
}

// --------------------- PRECEDENCE & ASSOCIATIVITY ---------------------
int prec(char c) {
    if (c == '^') return 3;
    else if (c == '*' || c == '/') return 2;
    else if (c == '+' || c == '-') return 1;
    return -1;
}

int isRightAssociative(char c) {
    return c == '^';
}

// --------------------- INFIX → POSTFIX ---------------------
void infixToPostfix(char *exp) {
    char result[MAX];
    int j = 0;
    topChar = -1;

    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        if (isalnum(c)) {
            result[j++] = c;
        } else if (c == '(') {
            pushChar(c);
        } else if (c == ')') {
            while (!isEmptyChar() && peekChar() != '(')
                result[j++] = popChar();
            popChar(); // remove '('
        } else { // operator
            while (!isEmptyChar() && peekChar() != '(' &&
                   (prec(peekChar()) > prec(c) ||
                    (prec(peekChar()) == prec(c) && !isRightAssociative(c)))) {
                result[j++] = popChar();
            }
            pushChar(c);
        }
    }

    while (!isEmptyChar())
        result[j++] = popChar();

    result[j] = '\0';
    printf("\nPostfix Expression: %s\n", result);
}

// --------------------- POSTFIX → INFIX ---------------------
void postfixToInfix(char *exp) {
    topStr = -1;
    char op1[MAX], op2[MAX], temp[MAX];

    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        if (isalnum(c)) {
            char s[2] = {c, '\0'};
            pushStr(s);
        } 
        else {
            strcpy(op2, popStr());
            strcpy(op1, popStr());

            sprintf(temp, "(%s%c%s)", op1, c, op2);

            pushStr(temp);
        }
    }

    printf("\nInfix Expression: %s\n", popStr());
}

// --------------------- MENU SYSTEM ---------------------
int main() {
    int choice;
    char exp[MAX];

    while (1) {
        printf("\n====== MENU ======\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Convert Postfix to Infix\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\nEnter Infix Expression: ");
            scanf("%s", exp);
            infixToPostfix(exp);
            break;

        case 2:
            printf("\nEnter Postfix Expression: ");
            scanf("%s", exp);
            postfixToInfix(exp);
            break;

        case 3:
            printf("\nExiting...\n");
            return 0;

        default:
            printf("\nInvalid choice! Try again.\n");
        }
    }
    return 0;
}
