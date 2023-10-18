#include "stdio.h"
#include "stdlib.h"

//Excercice 1
// Path: ADO/TP4/r.c
// 1)
//Expliquez le fonctionnement des changements de types (*(unsigned*)&f) et ( *(float*)(&i)
// a faire plus tard

// 2)

// 3)
//le resultat de res doit etre (2²⁴-1)
float floatMaxplus1(){
    float res = 1;
    while(1+res != res){
        res ++ ;
    }
    return res;
}

unsigned inf(float f1,float f2){
    return ((*(unsigned*)&f1)<<1)<((*(unsigned*)&f2)<<1);
}

unsigned getSigne(float reel){
    return (*(unsigned*)(&reel) >> 31) & 1;
}

int getExposant(float reel){
    return (*(unsigned*)(&reel) >> 23) & 0xFF;
}

unsigned getMantisse(float reel){
    return (*(unsigned*)(&reel)) & 0x7FFFFF;
}



int main() {
    //floatMaxPlus1
    printf("Fonction floatMaxPlus1 \n");
    printf("%f \n", floatMaxplus1());

    //Codage
    printf("\nCodage\n");
    printf("%d\n",(0.25+0.5== 0.75)); //=> 1
    printf("%d\n",(0.2+0.1== 0.3)); //=> 0
    printf("%d\n",(0.2+0.1-0.3< 0.0000000001)); //=>1
    float z=0;
    printf("%f\n",(1.0/z)); //=>inf
    printf("%f\n",(1.0/z)+(-1.0/z)); //=>-nan

    //Inf
    printf("\nFonction inf \n");
    printf("%u \n",inf(-1.5,2.75)); //=> 1
    printf("%u \n",inf(1.5,-2.75)); //=> 1
    printf("%u \n",inf(-2.75,1.5)); //=> 0

    //Getter
    printf("\nFonctions get\n");
    printf("%u \n", getSigne(102));
    printf("%u \n", getSigne(-102));
    printf("%d \n", getExposant(102));
    printf("%d \n", getExposant(-102));
    printf("%u \n", getMantisse(102));
    printf("%u \n", getMantisse(-102));





}