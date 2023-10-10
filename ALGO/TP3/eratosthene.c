#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Un argument est nécessaire !\n");
        return 1;
    }
    int n = atoi(argv[1]);
    printf("L’argument est : %d\n", n);

    int *tab = calloc(n, sizeof(int));
    for (int i = 2; i <n; i++) {
        tab[i] = 1;

    }
    for(int i = 2; i < n; i++){
        if (tab[i] !=0){
            for(int j = i+i; j < n; j+= i){
                if ( j % i == 0){
                    tab[j] = 0;
                }
            }
        }
    }
    printf("Nombres premiers inferieurs à 1000:\n");
    for(int i =0; i < n; i++) {
        if (tab[i] == 1){

            printf("%d ",i);
        }
    }

    free(tab);
    return 0;
}
