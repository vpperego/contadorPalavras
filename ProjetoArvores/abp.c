#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"
#include <time.h>
ABP* ordena(ABP* a)
{
    ABP* c = NULL, *novo=NULL;
    novo = (ABP*)malloc(sizeof(ABP));
    int info=0;
    char buffer[20]="";
    while(a!=NULL)
    {
        info = 0;
        buscaMaior(a, &info, buffer);
        remover(&a, info, buffer, &novo);
        c = InsereCompleto(c, novo);
    }
    //free(novo);
    //novo = NULL;
    return c;
}
void buscaMaior(ABP* a, int *maior, char *buffer)
{
    if(a!=NULL)
    {
        if(a->frequencia > *maior){
            *maior = a->frequencia;
            strncpy(buffer,a->nome,TAM);
        }
        buscaMaior(a->esq, maior,buffer);
        buscaMaior(a->dir, maior,buffer);
    }
}
ABP* insere(ABP *a, char *ch)
{
    if(!procuranodo(a, ch))
        a = InsereArvore(a, ch, 1);

    return a;
}

ABP* InsereArvore(ABP *a, char *ch, int freq)
{
    if (a == NULL)
    {
        a =  (ABP*) malloc(sizeof(ABP));
        strncpy(a->nome,ch,TAM);
        a->frequencia = freq;
        a->esq = NULL;
        a->dir = NULL;
        return a;
    }
    else if (strcmp(ch, a->nome) > 0)
        a->esq = InsereArvore(a->esq,ch, freq);
    else if (strcmp(ch, a->nome) < 0)
        a->dir = InsereArvore(a->dir,ch, freq);
    return a;
}
ABP* InsereCompleto(ABP *a, ABP *nodo)
{
    if (a == NULL)
    {
        a =  (ABP*) malloc(sizeof(ABP));
        strncpy(a->nome,nodo->nome,TAM);
        a->frequencia = nodo->frequencia;
        a->esq = NULL;
        a->dir = NULL;
        return a;
    }
    else if(a->frequencia > nodo->frequencia)
        a->esq = InsereCompleto(a->esq,nodo);
    else if(a->frequencia < nodo->frequencia)
        a->dir = InsereCompleto(a->dir,nodo);
    else if (strcmp(nodo->nome, a->nome) > 0)
        a->esq = InsereCompleto(a->esq,nodo);
    else if (strcmp(nodo->nome, a->nome) < 0)
        a->dir = InsereCompleto(a->dir,nodo);


    return a;
}


void Central(ABP *a,FILE *arq)
{
    if (a!= NULL)
    {
        Central(a->dir, arq);
        fprintf(arq,"%s\t%d\n",a->nome, a->frequencia);
        Central(a->esq, arq);
    }
}
void preFixado(ABP *a)
{
    if (a!= NULL)
    {
        preFixado(a->dir);
        printf("%20s\t%d\n",a->nome, a->frequencia);
        preFixado(a->esq);
    }
}



ABP *MaiorDireita(ABP **no)
{
    if((*no)->dir != NULL)
        return MaiorDireita(&(*no)->dir);
    else
    {
        ABP *aux = *no;
        if((*no)->esq != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da esq!
            *no = (*no)->esq;
        else
            *no = NULL;
        return aux;
    }
}

ABP *MenorEsquerda(ABP **no)
{
    if((*no)->esq != NULL)
        return MenorEsquerda(&(*no)->esq);
    else
    {
        ABP *aux = *no;
        if((*no)->dir != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da direita!
            *no = (*no)->dir;
        else
            *no = NULL;
        return aux;
    }
}

void remover(ABP **pRaiz, int numero, char* buffer, ABP **removido)
{
    if(*pRaiz == NULL)    // esta verificacao serve para caso o numero nao exista na arvore.
    {
        return;
    }
    if(strcmp(buffer,(*pRaiz)->nome) > 0)
        remover(&(*pRaiz)->esq, numero,buffer, removido);
    else if(strcmp(buffer,(*pRaiz)->nome) < 0)
        remover(&(*pRaiz)->dir, numero,buffer, removido);
    else     // se nao eh menor nem maior, logo, eh o numero que estou procurando! :)
    {
        (*removido)->frequencia=numero;
        strncpy((*removido)->nome, (*pRaiz)->nome, TAM);
        (*removido)->esq=NULL;
        (*removido)->dir=NULL;
        ABP *pAux = *pRaiz;     // quem programar no Embarcadero vai ter que declarar o pAux no inicio do void! :[
        if (((*pRaiz)->esq == NULL) && ((*pRaiz)->dir == NULL))          // se nao houver filhos...
        {
            free(pAux);
            (*pRaiz) = NULL;
        }
        else      // so tem o filho da direita
        {
            if ((*pRaiz)->esq == NULL)
            {
                (*pRaiz) = (*pRaiz)->dir;
                pAux->dir = NULL;
                free(pAux);
                pAux = NULL;
            }
            else             //so tem filho da esq
            {
                if ((*pRaiz)->dir == NULL)
                {
                    (*pRaiz) = (*pRaiz)->esq;
                    pAux->esq = NULL;
                    free(pAux);
                    pAux = NULL;
                }
                else        //Escolhi fazer o maior filho direito da subarvore esq.
                {
                    pAux = MaiorDireita(&(*pRaiz)->esq); //se vc quiser usar o Menor da esq, so o que mudaria seria isso:
                    pAux->esq = (*pRaiz)->esq;          //        pAux = MenorEsquerda(&(*pRaiz)->dir);
                    pAux->dir = (*pRaiz)->dir;
                    (*pRaiz)->esq = (*pRaiz)->dir = NULL;
                    free((*pRaiz));
                    *pRaiz = pAux;
                    pAux = NULL;
                }
            }
        }
    }
}
ABP* achaMin(ABP *arv)
{
    if(arv==NULL)
    {
        return NULL;
    }
    if(arv->esq)
        return achaMin(arv->esq);
    else
        return arv;
}
int leArquivo(char *nome,int limSup, int limInf,clock_t begin)
{
    ABP *lista = (ABP*)malloc(sizeof(ABP)), *ptaux=NULL,*nodo=NULL, *c=NULL;
    nodo = (ABP*)malloc(sizeof(ABP)); strncpy(nodo->nome, "",20);nodo->frequencia=0;
    lista = NULL;
    FILE *arquivo;
    FILE *saida;
    int info = 0;

    char str[80]="",buffer[TAM]="";
    strcpy(str,nome);

    char nomesaida[80]="saida_";

    strcat(nomesaida,nome);

    arquivo=fopen(nome,"r");

    saida=fopen(nomesaida,"wt");
    if(!arquivo)
    {
        puts("Erro ao abrir o arquivo!");
        return -1;
    }

    else
    {

//        calcula o tamanho do arquivo ,armazenando no long int tamanho e retornando
        //          para o inicio do arquivo

        fseek(arquivo,0,SEEK_END);
        long int tamanho = ftell(arquivo);

        size_t result;
        rewind(arquivo);

        char *palavra=(char*)malloc(tamanho);

        result = fread(palavra,1,tamanho,arquivo);
        palavra[result] = '\0';
        palavra = strtok (palavra,"\\ !\"#$%&'()*+,-./:;<=>?[]^_`{|}~\n");
        palavra = strlwr(palavra);
        while (palavra)
        {
            palavra = strlwr(palavra);
            lista = insere(lista, palavra);     //COLOCAR O INSERE DE ABP
            palavra = strtok(NULL,"\\ !\"#$%&'()*+,-./:;<=>?[]^_`{|}~\n");
        }
        free(palavra);
        palavra = NULL;
    }
    lista = ordena(lista);
    preFixado(lista);
    Central(lista, saida);
    clock_t end=clock();
    double tempoExecucao = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(saida,"\n Tempo de execução: %f",tempoExecucao);
    fclose(saida);
    fclose(arquivo);
    return 0;
}
int procuranodo(ABP* A, char str[])
{
    if(A == NULL)
        return 0;
    else if(!strcmp(A->nome, str))
    {
        A->frequencia++;
        return 1;
    }
    else
    {
        procuranodo(A->esq, str);
        procuranodo(A->dir, str);
    }
    return 0;
}
ABP* consultaABP(ABP *a, int chave)
{

    while (a!=NULL)
    {
        if (a->frequencia == chave )
            return a; //achou ent�o retorna o ponteiro para o nodo
        else if (a->frequencia > chave)
            a = a->esq;
        else
            a = a->dir;
    }
    return NULL; //se n�o achou
}
