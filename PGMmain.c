#include <stdio.h>
#include <stdlib.h>
#include "PGMsource.h"

int main(int argc,char *argv[]){

    PGM* cena = NULL;
    cena = LePGM(argv[1]);
    PGM* obj = NULL;
    obj = LePGM(argv[2]);
    Ponto result;
    result = JanelaDeslizante(cena, obj);
    FILE *fp;
    fp = fopen(argv[3], "w");
    fprintf(fp, "%d %d", result.x, result.y);
    freePGM(cena);
    freePGM(obj);
    fclose(fp);
	return 0;
}
