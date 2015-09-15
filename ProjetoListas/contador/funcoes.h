/*Igor Pires Ferreira e Vinicius Pittigliani Perego*/
#define TAM 20
#include <time.h>
typedef struct palavra PALAVRA;
struct palavra {
    int frequencia;
    char nome[TAM];
    PALAVRA *prox;
};
/*função principal para ordenar*/
PALAVRA* insere(PALAVRA* l, char *buffer);
/*função auxiliar*/
PALAVRA* insere_ord (PALAVRA* l, char *buffer, int frequencia);
/*remove nodo*/
PALAVRA* remover(PALAVRA* l, char *titulo, int *freq);
PALAVRA* criaLista(void);
PALAVRA* destroiLista(PALAVRA *lista);
void printaLista(PALAVRA *lista);

int leArquivo(char *nome, int limSup, int limInf,clock_t tempo);


