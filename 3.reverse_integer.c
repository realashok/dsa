#include<stdio.h>
int reverse_integer(int num);

int main(){
    int num;
    printf("Enter number that is to be reversed: ");
    if(scanf("%d", &num) != 1){
        printf("Invalid Input.\n");
        return 1;
    }
    printf("The number: %d if reversed is: %d \n", num, reverse_integer(num));
    return 0;
}

int reverse_integer(int num){
    int reversed_num = 0; 
    while(num != 0){
        reversed_num *= 10;
        reversed_num += num%10;
        num /=10;
    }
    return reversed_num;
}