#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// --------------------- STACK FOR CHAR ---------------------
char stackChar[MAX];
int topChar = -1;

void pushChar(char c) {
    if (topChar >= MAX - 1) {
        printf("Error: stack overflow on pushChar('%c')\n", c);
        exit(EXIT_FAILURE);
    }
    stackChar[++topChar] = c;
}

char popChar() {
    if (topChar < 0) {
        printf("Error: stack underflow on popChar()\n");
        exit(EXIT_FAILURE);
    }
    return stackChar[topChar--];
}

char peekChar() {
    if (topChar < 0) {
        return '\0';  // or some sentinel
    }
    return stackChar[topChar];
}

int isEmptyChar() {
    return topChar == -1;
}

// --------------------- STACK FOR STRING ---------------------
char stackStr[MAX][MAX];
int topStr = -1;

void pushStr(const char *str) {
    if (topStr >= MAX - 1) {
        printf("Error: stack overflow on pushStr(\"%s\")\n", str);
        exit(EXIT_FAILURE);
    }
    strcpy(stackStr[++topStr], str);
}

char* popStr() {
    if (topStr < 0) {
        printf("Error: stack underflow on popStr()\n");
        exit(EXIT_FAILURE);
    }
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
void infixToPostfix(const char *exp) {
    char result[MAX];
    int j = 0;
    topChar = -1;

    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        if (isalnum(c)) {
            result[j++] = c;
        } 
        else if (c == '(') {
            pushChar(c);
        } 
        else if (c == ')') {
            while (!isEmptyChar() && peekChar() != '(') {
                result[j++] = popChar();
            }
            if (isEmptyChar()) {
                printf("Error: mismatched parentheses — no matching '('.\n");
                exit(EXIT_FAILURE);
            }
            popChar(); // remove '('
        } 
