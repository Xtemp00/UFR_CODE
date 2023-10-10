#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Un argument est nécessaire !\n");
        return 1;
    }
    int arg = atoi(argv[1]);
    while(arg!=1){
        if (arg % 2 == 0){
            arg = arg / 2;
        } else {
            arg = 3 * arg + 1;
        }
        printf("%d, ", arg);
    }
    return 0;
}
