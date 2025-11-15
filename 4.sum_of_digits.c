#include<stdio.h>
int sum_of_digits(int num);

int main(){
    int num;
    printf("Enter number to find sum of digits: ");
    if(scanf("%d", &num) != 1){
        printf("Invalid Input.\n");
        return 1;
    }
    printf("The sum of digits of: %d is: %d \n", num, sum_of_digits(num));
    return 0;
}

int sum_of_digits(int num){
    int sum = 0; 
    while(num != 0){
        sum += num%10;
        num /=10;
    }
    return sum;
}