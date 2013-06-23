#include <stdio.h>
#include <stdlib.h>

void* getp(size_t idx, size_t )

int main(void) {
    
    void*** ary;
    int x = 1;
    int y = 2;
    void* a[] = { &x, &y };
    void* b[] = { &y, &x };
    
    ary = malloc(sizeof(void**) * 2);
    if (!ary) return 1;
    ary[0] = a;
    ary[1] = b;
    
    printf("{%p, %p}\n", ary[0][0], ary[0][1]);
    printf("{%p, %p}\n", ary[1][0], ary[1][1]);
    
    free(ary);
    return 0;
}
