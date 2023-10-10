#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Un argument est nécessaire !\n");
        return 1;
    }
    int arg = atoi(argv[1]);
    printf("L’argument est : %d\n", arg);
    return 0;
}
