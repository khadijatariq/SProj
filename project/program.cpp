#include "stdio.h"

int gcd (int n1, int n2) {
	//printf("%d %d\n", n1, n2);
    return (n2 == 0) ? n1 : gcd(n2, n1 % n2);
}

int main() {
    printf("%d\n", gcd(72, 32));
    //printf("%d\n", gcd(72, 32));
    return 0;
}