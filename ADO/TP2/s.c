//TP3 ARCHI
//Exercice 1
//1.1
#include <stdlib.h>
#include "stdio.h"


int bitCount(int n) { // utiliser un masque (n>>1)&0x7FFFFFFF
    int res = 0;
    unsigned int mask = (n>>1)&0x7FFFFFFF;
    while (mask > 0) {
        res += mask & 1;
        mask = mask >> 1;
    }
    if(n<0) {
        res++;
    }

    return res;
}

//1.2
int absolue(int n) {// fonction absolue sans utiliser d'alternative if
    int mask = n >> 31;
    return (n + mask) ^ mask;

}
//fordigit prend en compte aussi bien les negatif que les positif
char forDigit(int n) {
    char res = n + '0';
    if (n > 9) {
        res = res - '0' + 'A' - 10;
    }
    return res;

}



//exercice 2
//2.1
//faire la focntion toStringBase en parcourant une seule fois les digit du nombre puis en inversant le contenu de la chaine
//verifier que cela fonctionne pour les nombres 2^31-1 et -2^31
//ajouter des caracteres de separation tous les 3 caracteres
void toStringBase(int n, char *s, int base){
    int i = 0;
    int sign = 0;
    if (n == 0) {
        s[i] = '0';
        i++;
    }
    if(n>>31){
        sign = 1;
        n = -n;
    }
    while(n>0){
        s[i] = forDigit(n%base);
        n = n/base;
        i++;
    }
    if(sign){
        s[i] = '-';
        i++;
    }
    s[i] = '\0';
    //renverser la chaine
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    for (int j = 0; j < len / 2; j++) {
        char tmp = s[j];
        s[j] = s[len - j - 1];
        s[len - j - 1] = tmp;
    }

}

int main() {
    int n = 0;
    printf("\nfonction bitCount\n");
    n = bitCount(0x80000000);//=>1
    printf("%d\n", n);
    n = bitCount(-1);//=>32
    printf("%d\n", n);
    printf("\nfonction absolue\n");
    n = absolue(-12);//=>12
    printf("%d\n", n);
    n = absolue(1);//=>1
    printf("%d\n", n);
    printf("\nfonction toStringBase\n");
    char s[12];
    toStringBase(0,s,10); // => *s="0\0"
    printf("%s\n", s);
    toStringBase(0x123,s,10); // => *s="291\0"
    printf("%s\n", s);
    toStringBase(0xFFFFFFFF,s,10); // => *s="-1\0"
    printf("%s\n", s);
    toStringBase(0xF00FF000,s,10); // => *s="-268369920\0"
    printf("%s\n", s);
    toStringBase(0x80000000,s,10); // => *s="-2147483648\0"
    printf("%s\n", s);
    toStringBase(0x7FFFFFFF,s,10); // => *s="2147483647\0"
    printf("%s\n", s);
    return 0;
}