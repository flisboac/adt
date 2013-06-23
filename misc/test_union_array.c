#include <stdio.h>

typedef union u_ {
    int i;
    int* pi;
} u;

u U(int* i) {
    u ret;
    ret.pi = i;
    return ret;
}

void print_u(u u) {
    printf("(%d, %d, %d)", u.pi[0], u.pi[1], u.pi[2]);
}

int main() {
    int v[] = { 1, 0, 1 };
    print_u(U(v));
    return 0;
}
