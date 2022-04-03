// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
/*
 * Author:Carlos Tiago Simões dos Santos
 * Email: a2003035578@isec.pt
 *
 * Created on: 27 April 2021, 22:57
 * Last Edit: 12 Junho 2021
 */

#ifndef TRAFFIC_LIGHTS_GAME_CS_GDATA_H
#define TRAFFIC_LIGHTS_GAME_CS_GDATA_H
#endif //TRAFFIC_LIGHTS_GAME_CS_GDATA_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void newboard(int b_square, char *current_game); //initializa o tabuleiro com o valor: '-'
int changeboard(int b_cols, char *current_game); //Para iniciar um novo tabuleiro mas com possibilidade de escolha do tamanho
void show_board(int b_lines, int b_cols, const char *current_game); //Mostra tabuleiro - desenha o tabuleiro de jogo
void show_board_aux(int b_lines, int b_cols, int x, int y, char currentchar, int game_move, const char *current_game); //Mostra tabuleiro - desenha o tabuleiro utilizado para fazer o revert da peca e mostrar os ultimos movimentos
void show_address(int b_lines, int b_cols, char *current_game); //Mostra o endereço de memória de cada posição de current_game no tabuleiro
int newcolline(int b_lines, int b_cols, char charinput, const char *current_game, int a, int b, int player, int newcolline_p1, int newcolline_p2); // acrescenta linha o colunas
int joker_play(int player, int joker_p1, int joker_p2); // Jogada do Joker

void game_rules(); //Mostra as regras do jogo
void game_info(); // Informação inicial do jogo
int main_menu(int config_menu); // Menu principal do jogo

int gamemode(int check, int t_player); // alternar o tipo de jogador para o jogador dois - human vs human ou human vs computer
void timeprint(); // Mostra data e horas -- Função que pode ser utilizada depois paras estatísticas

void delete_stats(); // Elimina as informações de todos os jogos anteriores
void del_lastgame(); // Apaga os dados do último jogo
