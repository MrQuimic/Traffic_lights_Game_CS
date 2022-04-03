// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
/*
 * Author:Carlos Tiago Simões dos Santos
 * Email: a2003035578@isec.pt
 *
 * Created on: 27 April 2021, 22:57
 * Last Edit: 12 Junho 2021
 */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "moves.h"
#include "gdata.h"
#include "utils.h"

#define MBRAND 5 // Tamanho maximo normal de uma linha ou coluna
#define MBSIZE ((MBRAND*MBRAND)+4) // Tamanho maximo do tabuleiro

int main() {
    FILE *f;
    int b_square, b_lines, b_cols, repeat = 0, t_player = 0, recover_game = 0, configs = 0, g_play=0, new_size = 0;
    char *current_game, player1[20] = "Um", player2[20] = "Dois",config_menu = 1;

    setlocale(LC_ALL, "Portuguese"); //Acentos em português
    initRandom(); // Random números - esta função só deve ser chamada uma vez

    game_info();
    timeprint();

    stats slist = NULL; // Criar a lista ligada para as estatisticas
    pmoves mlist = NULL; // Criar a lista ligada para os movimentos
    mlist = malloc(sizeof(moves)); //Alocação de memória para a lista de movimentos
    if (mlist == NULL) {
        free_listed(mlist);
        printf("Erro na alocacao de memoria\n");
        return 0;
    }
    current_game = malloc(sizeof(char) * b_square*b_square); //Alocação de memória total para o array de movimentos
    if (current_game == NULL) {
        printf("Erro na realocacao\n");
        return 0;
    }

    do {
        b_square = intUniformRnd(3, MBSIZE); //tamanho aleatório
        b_lines = b_square; //Linhas = a colunas
        b_cols = b_square; //Linhas = a colunas

        if (g_play == 5){
            new_size = changeboard(b_cols, current_game); //Perguntar qual o novo tamanho
            b_lines = b_cols = b_square = new_size; //Iniciar linhas e colunas com novo tamanho
            newboard(b_square, current_game); // Novo tabuleiro
            show_board(b_lines, b_cols, current_game); // mostra o tabuleiro
        }

        stats_rebuild(&slist);

        if (repeat == 0) {
            configs = 1; //entrar em menu
        }
        if (g_play != 5){
            while (configs == 1) {
                config_menu = main_menu(config_menu);

                if (config_menu == 0) {

                    f = fopen("jago.bin", "rb"); //Verifica se há um jogo gravado
                    if ((f) == NULL) {
                        printf("\nInsira outra tecla\n");
                    }else{
                        printf("\nPara retomar o jogo anterior - tecla 0\n"); //Retoma jogo gravado
                        configs = 2; //sair do menu
                        recover_game = 1;
                    }
                    fclose(f);
                }
                if (config_menu == 2) {
                    game_rules(); //mostra as regras
                }

                if (config_menu == 3) {
                    printf("\nNome para Jogador 1:\n");
                    scanf("%s", player1);
                    printf("\nNome para Jogador 2:\n");
                    scanf("%s", player2);
                }
                if (config_menu == 4) {
                    t_player =  gamemode(0, t_player); //muda tipo de jogo
                }
                if (config_menu == 5) {
                    delete_stats(); //elimina as estatísticas
                }
                if (config_menu == 6) {
                    return 0; //sair do menu
                }
                if (config_menu == 1) {
                    configs = 2; //sair do menu e jogar
                }
            }
        }

        if (recover_game == 1) {
            rebuild_board(mlist, &slist); // reconstroi jogo anterior
            t_player = 1; //força modo jogador contra computador
            gamemode(1, t_player); //Verifica-se o modo de jogo
        } else {

            del_lastgame(); //apaga ultimo jogo se começar um novo
            gamemode(1, t_player); //Verifica-se o modo de jogo
            newboard(b_square, current_game); // novo tabuleiro
            show_board(b_lines, b_cols, current_game); // mostra o tabuleiro
            g_play = game_play(&mlist, &slist, player1, player2, b_square, b_lines, b_cols, 0, t_player, current_game); //função principal de jogo
        }

        if (g_play != 5) {
            printf("\nDeseja jogar um novo jogo? \n1 - Sim \n2 - Nao \n0 - Parametros do jogo\n");
            scanf("%d", &repeat);
        }
        free_part_listed(mlist); // liberta a memoria da lista de movimentos a partir do segundo elemento e coloca o primeiro pmoves prox e ant a null

        recover_game = 2;
    } while (repeat != 2);

    free_listed(mlist);// Liberta a memoria da lista de movimentos
    free(current_game);// Liberta a memoria da array
    free_slisted(slist);// Liberta a memoria da estatisticas

    return 0;
}