#include <stdio.h>
void main() {
    int n = 2147483648;
    printf(
            "The size of the number %d is %d bytes \n", 
            n, sizeof(n) );   
}
