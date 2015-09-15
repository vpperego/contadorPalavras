#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"
#include <time.h>

int main(int argc, char *argv[])
{
    clock_t begin;


    int sup = atoi(argv[1]);
    int inf = atoi(argv[2]);

    puts("processando....");
    begin = clock();
    leArquivo(argv[3], sup, inf, begin);


    puts("fim!");
    getchar();
    return 0;
}



