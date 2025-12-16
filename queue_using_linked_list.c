#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} node;

typedef struct Queue {
    node *front;
    node *rear;
} queue;

node* createNode(int data) {
    node* newNode = (node*)malloc(sizeof(node));
    if(newNode == NULL)
        return NULL;

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

queue* createQueue() {
    queue *newQueue = (queue*)malloc(sizeof(queue));
    newQueue->front = newQueue->rear = NULL;
    return newQueue;
}

int isEmpty(queue *q) {
    return q->front == NULL;
}

void enqueue(queue *q, int data) {
    node* newNode = createNode(data);
    if(!newNode) {
        printf("Queue overflow!\n");
        return;
    }

    if(q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeue(queue *q) {
    if(isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }

    node* temp = q->front;
    q->front = q->front->next;
    if(q->front == NULL)
        q->rear = NULL;
    int data = temp->data;
    free(temp);
    return data;
}

int peek(queue *q) {
    if(isEmpty(q))
        return -1;
    return q->front->data;
}

void printQueue(queue *q) {
    node *temp = q->front;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    
}

int main() {
    queue *q = createQueue();

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 50);

    printf("Queue: ");
    printQueue(q);

    dequeue(q);
    printf("Queue: ");
    printQueue(q);

    return 0;    
 }