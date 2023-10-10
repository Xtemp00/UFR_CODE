#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc != 2) {
        printf("Un argument est nécessaire !\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int *tab = calloc(n, sizeof(int));
    printf("L’argument est : %d\n", n);

    //Initilisation
    for(int i = 0; i<n; i++){
        tab[i] = rand()%2;
    }

    //for(int i = 0;i < n; i++){
    //    printf("%d ",tab[i]);
    //}

    int count = 0;
    for( int i = 0; i < n; i++){
        if(tab[i] == 1 ){
            count++;
        }

    }
    printf("Il y a %d 1 dans le tableaux \n",count);

    // tri du tableaux

    int right = n - 1;
    int left = 0;
    while (left < right){
        if ( tab[left] == 0){
            left++;
        }
        else {
            tab[left] = tab[right];
            tab[right] = 1;
            right--;
        }
    }
    for(int i =0; i < n ; i++) {
        printf("%d ",tab[i]);
    }
    printf("\n");
    printf("%d est égale à %d \n",n-right,count);



    //complexité
    /*
     * On parcours n fois la boucle donc :
     * comme a chaque apssage de boucle on fait au maximum un calcul
     * on obtient alors une complexité C(n) = O(n)
     */



    free(tab);
    return 0;
}
