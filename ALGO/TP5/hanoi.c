#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//Question 11.1
//Pour n = 1 il suffit de deplacer le disque 1 de A vers B
//Pour n = 2 il suffit de deplacer le disque 1 de A vers B, le disque 2 de A vers C et le disque 1 de B vers C
//ETC...

//Question 11.2
//proposer un algo qui va decrire a l'utilisateur les mouvements a effectuer
//pour resoudre le probleme des tours de Hanoi pour n disques et on ne peut pas deplacer un disque sur un disque plus petit
//algo : pour n=3
//A->C
//A->B
//C->B
//ETC...

//Question 11.3
//Analysez le nombres de mouvements de disques pour n disques
//pour n = 1 il y a 1 mouvement
//pour n = 2 il y a 3 mouvements
//pour n = 3 il y a 7 mouvements
//pour n = 4 il y a 15 mouvements
//pour n = 5 il y a 31 mouvements
//pour n+1 il y a 2^n - 1 mouvements
//ETC...

//Question 11.4
struct disc {
    int width;
    struct disc *next;
};
struct tower {
    struct disc *first;
};

//create an empty tower
void tower_create(struct tower *self){
    self->first = NULL;
}



//push a disc of size k on top of the tower
void tower_push_disc(struct tower *self, int k){
    struct disc *new_disc = malloc(sizeof(struct disc));
    if(new_disc == NULL){
        printf("Error: malloc échoué\n");
        return;
    }
    if(self->first == NULL){
        new_disc->width = k;
        new_disc->next = NULL;
        self->first = new_disc;
        return;
    }else{
        if(self->first->width > k){
            new_disc->width = k;
            new_disc->next = self->first;
            self->first = new_disc;
            return;
        }
    }

}




// pop the top disc and return its size
int tower_pop_disc(struct tower *self){
    struct disc *top_disc = self->first;
    int top_disc_width = top_disc->width;
    self->first = top_disc->next;
    free(top_disc);
    return top_disc_width;
}

// print the content of the tower
// dans ce sens 3 2 1
//utilisant une fonction mirror on peut afficher 3 2 1
void tower_print(struct tower *self){
    struct disc *current_disc = self->first;
    while(current_disc != NULL){
        printf("%d ", current_disc->width);
        current_disc = current_disc->next;
    }
    printf("\n");
}

struct hanoi {
    struct tower towers[3];
};

void hanoi_create(struct hanoi *self, int n){
    tower_create(&self->towers[0]);
    tower_create(&self->towers[1]);
    tower_create(&self->towers[2]);
    for(int i = n; i > 0; i--){
        tower_push_disc(&self->towers[0], i);
    }
}

void hanoi_print(const struct hanoi *self){
    printf("A: ");
    tower_print(&self->towers[0]);
    printf("B: ");
    tower_print(&self->towers[1]);
    printf("C: ");
    tower_print(&self->towers[2]);
}

void hanoi_destroy(struct hanoi *self){
    for(int i = 0; i < 3; i++){
        while(self->towers[i].first != NULL){
            tower_pop_disc(&self->towers[i]);
        }
    }
}

void hanoi_move_one_disc(struct hanoi *self, int i, int j){
    int disc_width = tower_pop_disc(&self->towers[i]);
    tower_push_disc(&self->towers[j], disc_width);
}

//algo qui deplace les n disque de la tour i vers la tour j. la tour k qui n'es ni i , ni j pourra etre calculer
// par la formule k = 3 - i - j
void hanoi_move(struct hanoi *self, int n, int i, int j){
    if(n == 1){
        hanoi_move_one_disc(self, i, j);
    }else{
        int k = 3 - i - j;
        hanoi_move(self, n-1, i, k);
        hanoi_move_one_disc(self, i, j);
        hanoi_move(self, n-1, k, j);
    }
}

// un algo qui prend en paramètres le nombre n
//de disque et qui retourne une description de la solution.
void Hanoi(int n, int i, int j, int k){
    if(n == 1){
        printf("%d -> %d\n", i, j);
    }else{
        Hanoi(n-1, i, k, j);
        printf("%d -> %d\n", i, j);
        Hanoi(n-1, k, j, i);
    }
}


int main(){
    struct tower A;
    struct tower B;
    struct tower C;
    tower_create(&A);
    tower_create(&B);
    tower_create(&C);
    tower_push_disc(&A, 3);
    tower_push_disc(&A, 2);
    tower_push_disc(&A, 1);
    tower_print(&A);
    tower_pop_disc(&A);
    tower_print(&A);
    tower_print(&B);
    tower_print(&C);
    tower_pop_disc(&A);
    tower_print(&A);
    tower_pop_disc(&A);
    tower_print(&A);

    struct hanoi h;
    hanoi_create(&h, 3);
    hanoi_print(&h);


    hanoi_move(&h, 3, 0, 1);
    hanoi_print(&h);

    hanoi_destroy(&h);

    Hanoi(3, 0, 1, 2);
    return 0;
}