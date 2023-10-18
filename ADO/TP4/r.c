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

float setSigne(float reel, unsigned signe){
    unsigned bits = (*(unsigned *)(&reel) & 0x7FFFFFFF) | (signe << 31);
    return *(float *) & bits;
}

float setMantisse(float reel, unsigned mantisse){
    unsigned bits = (*(unsigned *)(&reel) & 0xFF800000) | (mantisse & 0x7FFFFFFF);
    return *(float *) & bits;
}

float setExposant(float reel, unsigned exposant){
    unsigned bits = (*(unsigned *)(&reel) & 0x807FFFFF) | (exposant << 23);
    return *(float *) & bits;
}

//fonction add qui retourne |f1|+|f2|
//sachant ces tests:
//printf("%f \n",add(-1.5,2.75)); //=> 4.25
//printf("%f \n",add(-1.5,-2.75)); //=> 4.25
//-1.5 + 2.75 = 4.25
//-1.5 -2.75 = 4.25
//Opérateur d’addition Implémentez la fonction add qui retourne |f1|+|f2|, f1 et f2 étant deux
//nombres réels normalisés (sans utiliser l’addition des réels, ni la fonction fabs). Le résultat
//sera normalisé aussi. Vous pouvez utiliser les fonctions getSigne, getExposant, getMantisse,
//setSigne, setExposant, setMantisse.
float add(float f1, float f2){
    unsigned signe1 = getSigne(f1);
    unsigned signe2 = getSigne(f2);
    unsigned exposant1 = getExposant(f1);
    unsigned exposant2 = getExposant(f2);
    unsigned mantisse1 = getMantisse(f1);
    unsigned mantisse2 = getMantisse(f2);
    unsigned mantisse = 0;
    unsigned exposant = 0;
    unsigned signe = 0;
    if(exposant1 > exposant2){
        exposant = exposant1;
        mantisse = mantisse1;
    }else{
        exposant = exposant2;
        mantisse = mantisse2;
    }
    if(signe1 == signe2){
        mantisse = mantisse1 + mantisse2;
    }else{
        if(mantisse1 > mantisse2){
            mantisse = mantisse1 - mantisse2;
        }else{
            mantisse = mantisse2 - mantisse1;
        }
    }
    return setSigne(setExposant(setMantisse(0, mantisse), exposant), signe);

}

// Fonction pour convertir un nombre réel en sa représentation hexadécimale
//unsigned n = ...
//sprintf(res,"%c1.%xp%d", (n >> 31) ? ... : ... ,(n... ) << 1 ,((n....) ... )- ...);
void toHexString(char *res, float f) {
    unsigned n = *(unsigned *) &f;
    sprintf(res, "%c1.%xp%d", (n >> 31) ? '-' : '+', (n & 0x7FFFFF) << 1, ((n >> 23) & 0xFF) - 127);
}


//sachant
//res = (s==’-’) ? ... : ....| (e+...)... | (m >> 1));
//return ....;
float parseFloat(char *ch){
    unsigned res=0,e,m;
    char s;
    sscanf(ch,"%c1.%xp%d",&s,&m,&e);
    res = (s=='-') ? 0x80000000 : 0;
    res =res | ((e+127)<<23) | (m >> 1);
    return *(float*)&res;
}

void afficherDetailFloat(float reel){
    printf("--------\n");
    printf("Reel = %f\n", reel);
    printf("Signe = %d\n", getSigne(reel));
    printf("Mantisse = %d\n", getMantisse(reel));
    printf("Exposant = %d\n", getExposant(reel));
    printf("--------\n");
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

    //Setter
    printf("\nFonctions set\n");
    printf("%f \n", setSigne(102,1));
    printf("%f \n", setSigne(-102,0));
    printf("%f \n", setExposant(102,1));
    printf("%f \n", setExposant(-102,0));
    printf("%f \n", setMantisse(102,1));
    printf("%f \n", setMantisse(-102,0));

    //Add
    printf("\nFonction add\n");
    printf("%f \n",add(-1.5,2.75)); //=> 4.25
    printf("%f \n",add(-1.5,-2.75)); //=> 4.25

    //AfficherDetailFloat
    printf("\nFonction afficherDetailFloat\n");
    afficherDetailFloat(102);

    //ToHexString
    printf("\nFonction toHexString\n");
    char r[12];
    toHexString(r,125.25f); //=> *r="+1.f50000p6"
    printf("%s\n", r);
    toHexString(r,0.375f); //=> *r="+1.800000p-2"
    printf("%s\n", r);
    toHexString(r,-0.1f); //=> *r="-1.99999ap-4"
    printf("%s\n", r);


    //ParseFloat
    printf("\nFonction parseFloat\n");
    printf("%f\n",parseFloat("+1.F50000p85"));// => 125,25
    printf("%f\n",parseFloat("+1.800000p7D"));// =>0.375
    printf("%f\n",parseFloat("-1.99999Ap7B"));// =>-0.1




}