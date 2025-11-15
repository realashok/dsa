#include<stdio.h>
int check_prime(int n);

int main(){
    int num;
    printf("Enter number to check prime: ");
    if(scanf("%d", &num) != 1){
        printf("Invalid Input.\n");
        return 1;
    }
    printf("The numer %d is ", num);
    check_prime(num)? printf("a prime.\n"): printf("not a prime.\n");
    return 0;
}

int check_prime(int n){
    if(n<=1) return 0;
    if(n<=3) return 1;
    if(n%2==0) return 0;
    for(int i=3; i<=n/2; i+=2){
        if(n%i == 0) return 0;
    }
    return 1;
}