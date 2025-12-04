#include<stdio.h>
#define MAX 5

int stack[MAX];
int top = -1;

int isEmpty();
int isFull();
void push(int value);
int pop();
int peek();
void dispaly();

int main(){
    int choice, value;
    while (1)
    {
        printf("\n==== Stack Menu ====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Dispaly\n");
        printf("5. Check if Empty\n");
        printf("6. Check if Full\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter value to be pushed: ");
            scanf("%d", &value);
            push(value);
            break;
        
        case 2:
            value = pop();
            printf("Popped value: %d\n", value);
            break;
        
        case 3:
            value = peek();
            printf("Top value: %d\n", value);
            break;
        
        case 4:
            dispaly();
            break;
        
        case 5:
            if(isEmpty()){
                printf("\nStack is Empty.\n");
            }
            else{
                printf("\nStack is not Empty.\n");
            }
            break;

        case 6:
            if(isFull()){
                printf("\nStack is Full.\n");
            }
            else{
                printf("\nStack is not Full.\n");
            }
            break;

        case 7:
            printf("Exitting the program...\n");
            return 0;
        
        default:
            printf("\nInvalid Choice\n");
        }
    }
    
}

int isEmpty(){
    return (top == -1);
};
int isFull()
{
    return (top == MAX-1);
};
void push(int value){
    if(isFull()){
        printf("\nStack Overflow.");
        return;
    }
    stack[++top] =value;
    printf("%d is pushed onto the stack.\n", value);

};
int pop(){
    if(isEmpty()){
        printf("\nStack Underflow.\n");
        return -1;
    }
    return stack[top--];
};
int peek(){
    if(isEmpty()){
        printf("\nStack Underflow.\n");
        return -1;
    }
    return stack[top];
};
void dispaly(){
    if(isEmpty()){
        printf("\nStack is Empty.\n");
        return;
    }
    printf("\nStack Elements are: ");
    for(int i=top; i >=0; i--){
        printf("%d ", stack[i]);
    }
    printf("\n");
};
