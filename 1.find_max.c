#include<stdio.h>
int find_max(int a, int b);

int main(){

    int first_num, second_num;
    printf("Enter first number: ");
    if(scanf("%d", &first_num) != 1){
        printf("Invalid Input\n");
        return 1;
    }
    printf("Enter second number: ");
    if(scanf("%d", &second_num) != 1){
        printf("Invalid Input \n");
        return 1;
    };
    printf("Maximum of %d and %d is: %d\n", first_num, second_num, find_max(first_num, second_num));
    return 0;
}

int find_max(int a, int b){
    return (a>b) ? a:b;
}