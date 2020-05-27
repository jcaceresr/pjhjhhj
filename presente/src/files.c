#include "files.h"

#include <stdlib.h>
#include <stdio.h>
//return the hiscore
int retorna_puntaje(){ 
    FILE *archivo;
    int hiscore;
    archivo = fopen("../presente/src/hiscore.txt", "r");
    fscanf(archivo, "%d", &hiscore);
    fclose(archivo);
    return hiscore;

}
//change if puntaje> hiscore
void cambia_puntaje(int *puntaje){ 
    int hiscore = retorna_puntaje();
    FILE *archivo2;
    if(*puntaje > hiscore){
        archivo2 = fopen("../presente/src/hiscore.txt", "w");
        fprintf(archivo2, "%d", *puntaje);
        fclose(archivo2);
    }
}