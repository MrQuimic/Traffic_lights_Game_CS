// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
/*
 * Author:Carlos Tiago Simões dos Santos
 * Email: a2003035578@isec.pt
 *
 * Fornecido pelo professor como ferramenta pata o trabalho
 *
 */

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    int num_rand;
    do{
        num_rand =  a + rand()%(b-a+1);
    }while(num_rand>5);

    return num_rand;

}

int probEvento(float prob){
    return prob > ((float)rand()/RAND_MAX);
}

/*
// Função main () com alguns exemplos simples de utilizacao das funcoes
int main(){

  int i;

    initRandom();   // esta função só deve ser chamada uma vez

    printf("10 valores aleatorios uniformes entre [4, 10]:\n");
    for(i=0; i<10; i++)
        printf("%d\n", intUniformRnd(4, 100));

    printf(" Probabilidade 0.25 de um evento suceder: \n");
    for(i=0; i<10; i++)
        printf("%d\n", probEvento(0.25));

    return 0;
}
*/
