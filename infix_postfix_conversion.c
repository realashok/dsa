#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100 

// Global Stack for POSTFIX to INFIX (String Stack)
char *pToI_stack[MAX_SIZE];
int pToI_top = -1;

void pToI_push(char *str) {
    if(pToI_top == MAX_SIZE-1) {
        printf("Stack Overflow\n");
        return;
    }
    pToI_stack[++pToI_top] = str;
}

char* pToI_pop() {
    if(pToI_top == -1) {
        return NULL;
    }
    return pToI_stack[pToI_top--];
}

// Global Stack for INFIX to POSTFIX (Character Stack)
char iToP_stack[MAX_SIZE];
int iToP_top = -1;

void iToP_push(char c) {
    if(iToP_top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    iToP_stack[++iToP_top] = c;
}

char iToP_pop() {
    if(iToP_top == -1) {
        return '\0';
    }
    return iToP_stack[iToP_top--];
}

char iToP_peek() {
    if(iToP_top == -1) {
        return '\0';
    }
    return iToP_stack[iToP_top];
}

// Function to determine precedence
int precedence(char op) {
    if(op == '^') 
        return 3;
    if(op == '*' || op == '/') 
        return 2;
    if(op == '+' || op == '-')
        return 1;
    return 0;
}

// Postfix to Infix
void postfixToInfix(char* postfix) {
    pToI_top = -1;
    int i;
    // Note: To prevent memory leaks, we should ensure all dynamically allocated memory is freed.
    // In this simple example, we'll assume the input expression is valid or cleanup is external.

    for(i = 0; postfix[i] != '\0'; i++){
        char symbol = postfix[i];

        if(isalnum(symbol)) {
            char* temp = (char*)malloc(sizeof(char) * 2);
            temp[0] = symbol;
            temp[1] = '\0';
            pToI_push(temp);
        } else if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') {
            char* op2 = pToI_pop();
            char* op1 = pToI_pop();

            if(op1 == NULL || op2 == NULL) {
                printf("\n--- Invalid Postfix Expression (Too few operands) ---\n");
                return;
            }

            // Form the infix string: (op1 operator op2)
            // +4 is for '(', operator, ')', and '\0'
            char* temp = (char*)malloc(sizeof(char)* (strlen(op1) + strlen(op2) + 4));
            if (temp == NULL) { /* Handle allocation failure */ return; }
            sprintf(temp, "(%s%c%s)", op1, symbol, op2);

            free(op1);
            free(op2);

            pToI_push(temp);
        }
    }
    char* infix = pToI_pop();
    if(infix != NULL && pToI_top == -1) {
        printf("\n✅ Postfix to Infix Conversion:\n");
        printf("The Infix Expression is: %s\n", infix);
        free(infix);
    } else {
        printf("\n❌ Invalid Postfix Expression (Stack not empty or empty input)\n");
        // Clean up remaining memory if any
        while(pToI_top != -1) {
            free(pToI_pop());
        }
    }

}

// Infix to Postfix
void infixToPostfix(char* infix) {
    iToP_top = -1;
    char postfix[MAX_SIZE];
    int i, j = 0;
    char next_char;

    printf("\n\nProcessing Infix: %s\n", infix);
    for(i=0; infix[i] != '\0'; i++) {
        char symbol = infix[i];

        if(isalnum(symbol)) {
            postfix[j++] = symbol;
        } else if(symbol == '(') {
            iToP_push(symbol);
        } else if(symbol == ')') {
            // Pop until '(' is found
            while ((next_char = iToP_pop()) != '(') {
                if(next_char == '\0') {
                    printf("\n--- Invalid Infix Expression (Mismatched parentheses) ---\n");
                    return;
                }
                postfix[j++] = next_char;
            } 
        } else if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') {
            
            // Standard Operator Handling Logic
            // The condition for popping from the stack depends on the precedence of the current operator 
            // and the top-of-stack operator, and also its associativity (especially for '^').

            // For non-right associative operators (+, -, *, /):
            // Pop if stack top has GREATER OR EQUAL precedence.
            // For right associative operators (^):
            // Pop only if stack top has STRICTLY GREATER precedence.

            while (iToP_top != -1 && iToP_peek() != '(' && precedence(iToP_peek()) >= precedence(symbol)) {
                
                // Special check for right-associative '^'
                if (symbol == '^' && precedence(iToP_peek()) == precedence(symbol)) {
                    // For '^', if precedence is equal, we STOP popping (right-associative)
                    break;
                }
                
                postfix[j++] = iToP_pop();
            }
            // Push the current operator onto the stack
            iToP_push(symbol);
        }
    }

    // Drain the remaining operators from the stack to the postfix expression
    while (iToP_top != -1) {
        next_char = iToP_pop();
        if(next_char == '(') {
             printf("\n--- Invalid Infix Expression (Mismatched parentheses) ---\n");
             return;
        }
        postfix[j++] = next_char;
    }

    postfix[j] = '\0'; // Null-terminate the resulting string
    
    printf("\n✅ Infix to Postfix Conversion:\n");
    printf("The Postfix Expression is: %s\n", postfix);
}

// --- Main Function ---

int main() {
    
    char infix_expr1[MAX_SIZE];
    char postfix_expr1[MAX_SIZE];
    
    printf("Enter an Infix Expression (e.g., a+b*c): ");
    if (fgets(infix_expr1, MAX_SIZE, stdin) != NULL) {
        infix_expr1[strcspn(infix_expr1, "\n")] = '\0'; // Remove newline character
        // Convert to postfix and print
        infixToPostfix(infix_expr1);
    }

    printf("\n\nEnter a Postfix Expression (e.g., abc*+): ");
    if (fgets(postfix_expr1, MAX_SIZE, stdin) != NULL) {
        postfix_expr1[strcspn(postfix_expr1, "\n")] = '\0'; // Remove newline character
        // Convert to infix and print
        postfixToInfix(postfix_expr1);
    }
    
    // Example for a specific test case:
    // postfixToInfix("ab*c+"); // Converts to ((a*b)+c)
    // infixToPostfix("a+b*c"); // Converts to abc*+

    return 0;
}