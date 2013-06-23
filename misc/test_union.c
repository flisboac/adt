#include <stdio.h>
#include <stddef.h>

typedef union un_ {
    
    int i;
    void* v;
} un;

un I(int i) {
    un v;
    v.i = i;
    return v;
}

un V(void* p) {
    un v;
    v.v = p;
    return v;
}

void print_i(un v) {
    printf("%d\n", v.i);
}

void print_v(un v) {
    printf("<%p>\n", v.v);
}

int main(void) {
    
    int i = 50;
    // Only possible in GCC?
    //print_i(256);
    print_i(I(10));    
    print_i(I(i));
    // Only possible in GCC?
    //print_v(NULL);
    print_v(V(0));
    print_v(V(&i));
}