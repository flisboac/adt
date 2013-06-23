#include <stdio.h>

#define println(s) println(s)

void println(char* s) {
    printf("%s\n", s);
}

int main(void) {
    println("Hello!");
    return 0;
}
