#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc!=2){
        printf("erreur il faut des guillemet %s",argv[0]);
        return 1;
    }
    else {
        printf("%s\n",argv[1]);
        lngstr(argv[1]);
        cmpt_esp(argv[1]);
        voyelles(argv[1]);
    }
    return 0;
}

int lngstr(char *str){
    int len = 0;
    while(str[len] != 0){
        len+=1;
    }
    printf("la longueur de la chaine est : %d \n", len);
    return len;
}

int cmpt_esp(char *str){
    int len =0;
    int esp = 0;
    while(str[len] != 0){
        len+=1;
        if (str[len] == ' '){
            esp+=1;
        }
    }
    printf("Le nombre d'espace dans la chain est : %d\n",esp);
    return esp;
}

int voyelles(char *str){
    int len = 0;
    int j=0;
    char chaine[strlen(str)];
    while (str[len] != '\0'){
        if ((str[len] =='a') || (str[len] =='e') || (str[len] =='i') || (str[len] =='o') || (str[len] =='u') || (str[len] =='y')){
            ++len;
        } else {
            chaine[j] = str[len];
            ++j;
            ++len;
        }
    }
    chaine[j+1] = '\0';
    printf("Voici la chaine sans voyelles : %s\n",chaine);
    return len;
}
