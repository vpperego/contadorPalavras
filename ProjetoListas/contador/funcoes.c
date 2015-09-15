#define TAM 20
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

PALAVRA* insere(PALAVRA* l, char *buffer)
{
    int *ptr;
    int freq = 0;
    ptr = &freq;
    l = remover(l, buffer, ptr);
    if(freq == 0)
    {
        freq = 1;
        l=insere_ord(l,buffer,freq);
    }
    else
    {
        freq++;
        l=insere_ord(l,buffer, freq);
    }
    return l;
}
PALAVRA* insere_ord (PALAVRA* l, char *buffer, int frequencia)
{
    PALAVRA *novo; //novo elemento
    PALAVRA *ant = NULL; //ponteiro auxiliar para a posição anterior
    PALAVRA *ptaux = l; //ponteiro auxiliar para percorrer a lista

    /*aloca um novo nodo */
    novo = (PALAVRA*) malloc(sizeof(PALAVRA));

    /*insere a informação no novo nodo*/
    strncpy(novo->nome,buffer,TAM);
    novo->frequencia = frequencia;
    /*procurando a posição de inserção*/
    while ((ptaux!=NULL) && novo->frequencia < ptaux->frequencia)
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }
    while ((ptaux!=NULL) && strcmp(novo->nome,ptaux->nome)>0 && novo->frequencia == ptaux->frequencia)
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /*encaeia o elemento*/
    if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
    {
        //  puts("inserindo primeiro");
        novo->prox = l;
        l=novo;
    }
    else /*elemento inserido no meio da lista*/
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return l;
}

//=======================================================

PALAVRA* destroiLista(PALAVRA *lista)
{
    PALAVRA *ptAux;
    while(lista != NULL)
    {
        ptAux = lista;
        lista=lista->prox;
        free(ptAux);
    }
    free(lista);    //desaloca os ponteiros e aponta pra nulo pra não deixar ponteiros soltos
    ptAux = NULL;   //se não apontar para nulo pode ocorrer memory leak
    lista = NULL;
    return NULL;
}
/*
Imprime as palavras com suas respectivas
frequencias

*/
void printaLista(PALAVRA *lista)
{
    PALAVRA* ptaux=lista;
    while(ptaux!=NULL)
    {
        printf("%20s\t%d\n", ptaux->nome, ptaux->frequencia);
        ptaux=ptaux->prox;
    }
}
/**/
PALAVRA* remover(PALAVRA* l, char *titulo, int *freq)//freq é um parâmetro de sáida
{
    PALAVRA *ant = NULL; //ponteiro auxiliar para a posição anterior
    PALAVRA *ptaux = l; //ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux != NULL && (strcmp(ptaux->nome, titulo)!=0))
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }
    if (ptaux == NULL)
        return l; /*retorna a lista original*/

    if (ant == NULL) /*vai remover o primeiro elemento*/
        l = ptaux->prox;
    else /*vai remover do meio ou do final*/
        ant->prox = ptaux->prox;

    *freq = ptaux->frequencia;
    free(ptaux); /*libera a memória alocada*/
    ptaux = NULL;
    return l;
}
int leArquivo(char *nome,int limSup, int limInf,clock_t begin)
{

    PALAVRA *lista = (PALAVRA*)malloc(sizeof(PALAVRA));
    lista = NULL;
    PALAVRA *ptaux=NULL;
    FILE *arquivo;
    FILE *saida;

    char str[80]="";
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
        //Le o arquivo numa string só e vai separando a em tokens
        result = fread(palavra,1,tamanho,arquivo);
        palavra[result] = '\0';
        palavra = strtok (palavra,"\\ !\"#$%&'()*+,-./:;<=>?[]^_`{|}~\n");
        palavra = strlwr(palavra);
        while (palavra)
        {
            palavra = strlwr(palavra);
            lista = insere(lista, palavra);
            palavra = strtok(NULL,"\\ !\"#$%&'()*+,-./:;<=>?[]^_`{|}~\n");
        }
        free(palavra);
        palavra = NULL;


    }
    ptaux=lista;
    while(limSup < ptaux->frequencia){
        ptaux = ptaux->prox;
    }

    while(ptaux!=NULL && limInf <= ptaux->frequencia)
    {
        fprintf(saida,"%d\t%s\n",ptaux->frequencia,ptaux->nome);
        ptaux=ptaux->prox;
    }
    lista = destroiLista(lista);
    //variavel para receber o tempo final de execução da aplicação
    clock_t end=clock();
    //double para armazenar a diferença do tempo de execução da aplicação
    double tempoExecucao = (double)(end - begin) / CLOCKS_PER_SEC;


    fprintf(saida,"\n Tempo de execução: %f",tempoExecucao);
    fclose(saida);
    fclose(arquivo);
    return 0;
}
