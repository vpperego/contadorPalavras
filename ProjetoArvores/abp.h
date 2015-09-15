#define TAM 20
#include <time.h>
struct abp{
        char nome[TAM];
        int frequencia;
        struct abp *esq;
        struct abp *dir;
};

typedef struct abp ABP;
ABP* ordena(ABP* a);
ABP* InsereCompleto(ABP *a, ABP*nodo);
ABP* insere(ABP *a, char *ch);
ABP* InsereArvore(ABP *a, char *ch, int freq);
void Central(ABP *a, FILE *arq);
void preFixado(ABP *a);
int leArquivo(char *nome,int limSup, int limInf,clock_t begin);
ABP* achaMin(ABP *arv);
int procuranodo(ABP* A, char str[]);
void buscaMaior(ABP* a, int *maior, char *buffer);
ABP *MaiorDireita(ABP **no);
ABP *MenorEsquerda(ABP **no);
void remover(ABP **pRaiz, int numero, char* buffer, ABP **removido);


