#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int *array_new(size_t size){
    //srand(time(NULL));
    int *tab = calloc(size, sizeof(int));
    if (tab == NULL){
        printf("ERREUR while allocating memory ln");
        return NULL;
    }
    //Initilisation
    for(int i = 0; i<size; i++){
        tab[i] = rand()%100;
    }
    return tab;
}



size_t array_index_max(const int *data, size_t size){
    int max = data[0];
    int indice = 0;
    for(int i = 0;i<size;i++){
        if (max < data[i]){
            max = data[i];
            indice = i;
        }
    }
    printf("L'indice du plus grand élement est : %d\n",indice);
    return indice;
}



int array_sum(const int *data, size_t size){
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum+=data[i];
    }
    printf("La somme est de : %d\n",sum);
    return sum;
}



size_t array_count(const int *data, size_t size, int value){
    int occ = 0;
    for ( int i = 0; i < size; i++){
        if ( value == data[i]){
            occ++;
        }
    }
    printf("Le nombre d'occurence de %d est de : %d\n",value,occ);
    return occ;
}

void array_shift_left(int *data, size_t size){
    int mem
    for( int i = size-1; i > 0; i--){
        temp2 = data[i];
        data[i] =temp;
        temp = temp2;
    }
}


size_t array_longest_even_seq(const int *data, size_t size){
    int max_s = 0;
    int nb = 0;
    for (int i = 0; i < size; i++){
        if( (data[i]%2) == 0){
            nb ++;
            if (max_s < nb){
                max_s = nb;
            }
        }
        else {
            nb = 0;
        }
    }
    printf("La plus longue série de nombres pairs est de : %d\n",max_s);
    return max_s;
}


void affichage(const int *data, size_t size){
    for (int i=0; i < size;i++){
        printf("%d ",data[i]);
    }
}


int main(int argc, char *argv[]) {
    int *t = array_new(10000);
    if (t == NULL){
        return 1;
    }
    size_t max = array_index_max(t,10000);
    affichage(t,10000);
    int sum = array_sum(t,10000);
    size_t occ = array_count(t,10000,42);
    array_shift_left(t,10000);
    size_t serie = array_longest_even_seq(t,10000);
    affichage(t,10000);

    free(t);
    return 0;
}
