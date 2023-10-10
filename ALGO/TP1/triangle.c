#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Un argument est nécessaire !\n");
        return 1;
    }
    int arg = atoi(argv[1]);
    for (int i = 1; i <= arg;i++){
        for (int j=1; j <= i;j++){
            printf("# ");
        }
        printf("\n");
    }
    return 0;
}
