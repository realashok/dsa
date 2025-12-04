#include <stdio.h>

void TowerOfHanoi(int n, char source, char destination, char auxiliary) {
    if (n == 0)
        return;

    TowerOfHanoi(n - 1, source, auxiliary, destination);
    printf("Move disk %d from %c to %c\n", n, source, destination);
    TowerOfHanoi(n - 1, auxiliary, destination, source);
}

int main() {
    int n = 3;
    TowerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}
