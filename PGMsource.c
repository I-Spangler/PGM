#include <stdlib.h>
#include <stdio.h>
#include "PGMsource.h"

/* -------------------------------------------------------------
Protótipo: *LePGM(char *entrada)
Função: Abrir o arquivo indicado pelo usuário,
criar uma estrutura que recebe os dados do arquivo de imagem
alocar a matriz com os valores da escala de cinza da imagem PGM
Entrada: argumento *argv[]
Saída: Estrutura contendo número (int) de linhas, colunas,
(unsigned char) valor máximo de transparência e matriz do tipo
unsigned char
--------------------------------------------------------------*/
PGM *LePGM(char *entrada){
	char t[2];
	int i, j;
	FILE *fp;
	fp = fopen(entrada, "r");
	PGM *pgmimg = malloc(sizeof(PGM));
	fscanf(fp, "%c %c", &t[0], &t[1]);
	fscanf(fp,"%d %d %hhu", &pgmimg->c, &pgmimg->l, &pgmimg->maximo);
    pgmimg->dados = malloc(sizeof(unsigned char*)*pgmimg->l);
    for(i = 0; i<pgmimg->l; i++){
    pgmimg->dados[i] = malloc(sizeof(unsigned char)*pgmimg->c);
		for(j = 0; j<pgmimg->c; j++){
			fscanf(fp, "%hhu", &pgmimg->dados[i][j]);
		}
	}
	fclose(fp);
	return pgmimg;
}
/* -------------------------------------------------------------
Protótipo: freePGM(PGM *img)
Função: Desalocar a memória usada em uma estrutura PGM
Entrada: Estrutura contendo número (int)
de linhas "l", colunas "c", (unsigned char) valor máximo de transparência
"maximo" e matriz "dados" do tipo unsigned char.
Saída: void
--------------------------------------------------------------*/
void freePGM(PGM *img){
    int i;
    for(i = 0; i< img->l; i++){
        free (img->dados[i]);
    }
    free(img->dados);
	free(img);
}
/* -------------------------------------------------------------
Protótipo: JanelaDeslizante(PGM *cena, PGM *obj)
Função: "Deslizar" uma PGM sobre a outra, fazendo a correlação
a cada iteração. armazenar o valor retornado por CorrelacaoCruzada
em aux, encontrar o maior valor e armazenar o ponto em que ele foi
encontrado em r (o ponto de "match" entre as imagens).
Entrada: Duas estruturas PGM, cena e obj, contendo número (int)
de linhas "l", colunas "c", (unsigned char) valor máximo de transparência
"maximo" e matriz "dados" do tipo unsigned char.
Saída: Estrutura Ponto contendo coordenadas (int) x, y.
--------------------------------------------------------------*/
Ponto JanelaDeslizante(PGM *cena, PGM *obj){
	Ponto p, r;
	int i, j, aux, maiorvalor = 0;
	for(i = 0; i<=cena->l-obj->l; i++){
		for(j = 0; j<=cena->c-obj->c; j++){
			p.x = i; p.y = j;
			aux = CorrelacaoCruzada(cena, obj, p);
			if(aux > maiorvalor){
				maiorvalor = aux;
				r.y = i; r.x = j;
			}
		}
	}
	return r;
}
/* -------------------------------------------------------------
Protótipo: CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto p)
Função: Aplicar a correlação cruzada às matrizes da cena e do objeto
retornando a soma dos produtos entre os valores inteiros das células
das duas matrizes
Entrada: Duas estruturas PGM, cena e obj, contendo número (int)
de linhas "l", colunas "c", (unsigned char) valor máximo de transparência
"maximo" e matriz "dados" do tipo unsigned char.
Uma estrutura Ponto contendo as coordenadas x e y da matriz "dados" de obj
Saída: int soma
--------------------------------------------------------------*/
int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto p){
	int soma = 0, i, j;
	for(i = 0; i<obj->l; i++){
		for(j = 0; j<obj->c; j++){
			soma += ((int)obj->dados[i][j])*((int)cena->dados[p.x+i][p.y+j]);
		}
	}
	return soma;
}
