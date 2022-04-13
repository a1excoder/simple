#include <stdio.h>

int simple_number(int x) {
    if (x == 1 || x == 2) return 0;

    for (int i = 2; i < x; i++) {
        if (x % i == 0) return 0;
    }

    return 1;
}

void factorize( int n, int* a, int* b )
{
    if (n == 0 || n == 1 || n == 2) {
        *a = 1;
        *b = n;
        return;
    }

    for (int i = 2; i < n; i++) {
        for (int j = 2; j < n; j++) {
            if (i * j == n) {
                *a = i;
                *b = j;
                return;
            }
        }
        if (n % i == 0) {
            *a = 1;
            *b = n;
            return;
        }
    }

    *a = 1;
    *b = n;
}


int main(int argc, char const *argv[])
{
    int a = 0, b = 0;
    
    // output only simple numbers
    for (int i = 1; i <= 100; i++) {
        if (simple_number(i)) {
            factorize(i, &a, &b);
            printf("%d %d\n", a, b);
        }
    }

    return 0;
}
