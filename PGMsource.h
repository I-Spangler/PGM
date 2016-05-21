#ifndef PGMSOURCE_H_INCLUDED
#define PGMSOURCE_H_INCLUDED

typedef struct{
	int c;
	int l;
	unsigned char maximo;
	unsigned char **dados;
}PGM;

typedef struct{
    int x;
    int y;
}Ponto;

PGM *LePGM(char *entrada);
void freePGM(PGM *img);
int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto p);
Ponto JanelaDeslizante(PGM *cena, PGM *obj);

#endif // PGMSOURCE_H_INCLUDED
