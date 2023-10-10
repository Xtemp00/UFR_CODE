#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Un argument est nécessaire !\n");
        return 1;
    }
    int arg = atoi(argv[1]);
    for(int i=1;i<=arg;i++){
        if (( i % 3 == 0) && ( i % 5 == 0)){
            printf("FizzBuzz ");
        } else if ( i % 3 == 0){
            printf("Fizz ");
        } else if ( i % 5 == 0){
            printf("Buzz ");
        } else {
            printf("%d ",i);
        }
    }
    return 0;
}
