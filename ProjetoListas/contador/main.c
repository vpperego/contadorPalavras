#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*O trabalho consiste em ler o arquivo texto de uma vez s� e separar as palavras em tokens!!!
Ao ler a palavra, se ela existir, remove da lista, aumenta frequencia e a insere de novo j� na ordem correta.
Se n�o, adiciona na lista, tamb�m inserindo na ordem correta.
No pior caso o algoritmo percorrer� a lista duas vezes (quando n�o existe o nodo e ele for inserido no final da lista)*/
int main (int argc, char *argv[])
{
    //cria uma variavel de tempo para marcar o inicio da aplica��o
    clock_t begin;
    begin = clock();


    //char *nome = "teste.txt";
    int sup = atoi(argv[1]);
    int inf = atoi(argv[2]);
    /**puts("Digite o nome do arquivo a ser lido: ");gets(nomearq);
    //puts("Digite o limite superior: "); scanf("%d", &sup);
    //puts("Digite o limite inferior: "); scanf("%d", &inf);
    puts("Processando....");
    */
    leArquivo(argv[3], sup, inf, begin);
//    leArquivo(nomearq, sup, inf, begin);//CASO FALHE A CHAMADA PELA MAIN, BASTA TROCAR O NOME DO ARQUIVO E OS LIMITES
    puts("Fim!!\nDigite uma tecla....");

    getchar();

    return 0;
}
