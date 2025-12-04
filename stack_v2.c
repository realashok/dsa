#include <stdio.h>
#include <limits.h>

#define MAX 5
#define STACK_EMPTY INT_MIN

typedef enum {
    PUSH = 1,
    POP,
    PEEK,
    DISPLAY,
    CHECK_EMPTY,
    GET_SIZE,
    CLEAR_STACK,
    EXIT
} MenuOptions;

typedef enum {
    SUCCESS = 1,
    STACK_FULL,
    STACK_EMPTY_ERROR
} OperationStatus;

typedef struct {
    int data[MAX];
    int top;
} Stack;

// Function prototypes
void initStack(Stack *s);
int isEmpty(const Stack *s);
int isFull(const Stack *s);
OperationStatus push(Stack *s, int value);
int pop(Stack *s);
int peek(const Stack *s);
void display(const Stack *s);
int getSize(const Stack *s);
void clearStack(Stack *s);
void clearInputBuffer();
void printStackStatus(const Stack *s);

int main() {
    Stack stack;
    initStack(&stack);
    
    int choice, value, result;
    OperationStatus status;
    
    printf("==== Stack Implementation ====\n");
    printf("Maximum stack size: %d\n\n", MAX);
    
    while (1) {
        printf("\n==== Stack Operations ====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Check if Empty\n");
        printf("6. Get Size\n");
        printf("7. Clear Stack\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number between 1 and 8.\n");
            clearInputBuffer();
            continue;
        }
        
        switch (choice) {
            case PUSH:
                printf("Enter value to push: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input! Please enter a valid integer.\n");
                    clearInputBuffer();
                    break;
                }
                status = push(&stack, value);
                if (status == SUCCESS) {
                    printf("✓ %d pushed onto stack successfully.\n", value);
                } else if (status == STACK_FULL) {
                    printf("✗ Stack Overflow! Cannot push %d (Stack is full)\n", value);
                }
                printStackStatus(&stack);
                break;
                
            case POP:
                result = pop(&stack);
                if (result != STACK_EMPTY) {
                    printf("✓ Popped value: %d\n", result);
                } else {
                    printf("✗ Stack Underflow! Nothing to pop.\n");
                }
                printStackStatus(&stack);
                break;
                
            case PEEK:
                result = peek(&stack);
                if (result != STACK_EMPTY) {
                    printf("Top element: %d\n", result);
                } else {
                    printf("Stack is empty. No element to peek.\n");
                }
                break;
                
            case DISPLAY:
                display(&stack);
                break;
                
            case CHECK_EMPTY:
                if (isEmpty(&stack)) {
                    printf("✓ Stack is EMPTY\n");
                } else {
                    printf("✓ Stack is NOT empty\n");
                }
                break;
                
            case GET_SIZE:
                printf("Current stack size: %d/%d\n", getSize(&stack), MAX);
                break;
                
            case CLEAR_STACK:
                clearStack(&stack);
                printf("✓ Stack cleared successfully.\n");
                printStackStatus(&stack);
                break;
                
            case EXIT:
                printf("\nThank you for using Stack Implementation!\n");
                printf("Exiting...\n");
                return 0;
                
            default:
                printf("Invalid choice! Please enter a number between 1 and 8.\n");
        }
    }
}

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(const Stack *s) {
    return (s->top == -1);
}

int isFull(const Stack *s) {
    return (s->top == MAX - 1);
}

OperationStatus push(Stack *s, int value) {
    if (isFull(s)) {
        return STACK_FULL;
    }
    s->data[++s->top] = value;
    return SUCCESS;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        return STACK_EMPTY;
    }
    return s->data[s->top--];
}

int peek(const Stack *s) {
    if (isEmpty(s)) {
        return STACK_EMPTY;
    }
    return s->data[s->top];
}

void display(const Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    
    printf("\nStack Contents (Top to Bottom):\n");
    printf("┌─────┐\n");
    for (int i = s->top; i >= 0; i--) {
        if (i == s->top) {
            printf("│ %-3d │ ← top\n", s->data[i]);
        } else {
            printf("│ %-3d │\n", s->data[i]);
        }
    }
    printf("└─────┘\n");
    printf("Size: %d/%d\n", getSize(s), MAX);
}

int getSize(const Stack *s) {
    return s->top + 1;
}

void clearStack(Stack *s) {
    s->top = -1;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printStackStatus(const Stack *s) {
    printf("[Status: %d/%d elements]", getSize(s), MAX);
    if (isFull(s)) {
        printf(" [FULL]");
    } else if (isEmpty(s)) {
        printf(" [EMPTY]");
    }
    printf("\n");
}