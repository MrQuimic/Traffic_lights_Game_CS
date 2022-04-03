// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
/*
 * Author:Carlos Tiago Simões dos Santos
 * Email: a2003035578@isec.pt
 *
 * Created on: 27 April 2021, 22:57
 * Last Edit: 12 Junho 2021
 */
#include <time.h>
#include "gdata.h"
#include "moves.h"

void newboard(int b_square, char *current_game) {
    int i, j;

    for (i = 0; i < b_square; i++) {
        for (j = 0; j < b_square; j++) {
            //current_game[i][j]='-';
            *(current_game + b_square * i + j) = '-';
        }
    }
    printf("\nTamanho do tabuleiro: %d\n", b_square);

}

int changeboard(int b_cols, char *current_game) {
    int new_size = 0;
    char *aux;

    printf("Para um novo tabuleiro, escolha o tamanho do tabuleiro (3 a 5): ");
    scanf("%d", &new_size);

    if (new_size >= 3 && new_size <= 5) {

        return new_size;

    } else {
        return 0;
    }
}

void show_board(int b_lines, int b_cols, const char *current_game) {
    int i, j, n, k;
    putchar('\n');

    for (i = 0; i < b_cols; i++) {
        printf("  C%d  ", i);
    }
    putchar('\n');
    putchar('\n');

    for (i = 0; i < b_lines; i++) {

        for (j = 0; j < b_cols; j++) {
            if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == '-') {
                for (k = 0; k < 5; k++) {
                    putchar(' ');
                }
            } else if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == 'G') {
                printf("  G  ");
            } else if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == 'Y') {
                printf("  Y  ");
            } else if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == 'R') {
                printf("  R  ");
            } else if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == '#') {
                printf("  #  ");
            } else {
                for (k = 0; k < 5; k++) {
                    putchar(' ');
                }
            }
            if (j != (b_cols - 1))
                printf("|");
        }

        putchar('\n');

        for (n = 0; n < b_cols; n++) {
            for (k = 0; k < 1; k++) {
                putchar(' ');
            }
            for (k = 0; k < 3; k++) {
                putchar('-');
            }
            for (k = 0; k < 2; k++) {
                putchar(' ');
            }
        }
        printf(" L%d", i);
        putchar('\n');
    }
    //putchar('\n');
}

void show_board_aux(int b_lines, int b_cols, int x, int y, char currentchar, int game_move, const char *current_game) {
    int i, j, n, k;

    putchar('\n');
    printf("Consulta de jogada n:%d", game_move);
    printf("\tx:%d y:%d Peca: %c", x, y, currentchar);
    putchar('\n');

    for (i = 0; i < b_lines; i++) {

        for (j = 0; j < b_cols; j++) {

            if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == '-') {
                for (k = 0; k < 5; k++) {
                    putchar(' ');
                }
            } else if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == 'G') {
                printf("  G  ");
            } else if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == 'Y') {
                printf("  Y  ");
            } else if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == 'R') {
                printf("  R  ");
            } else if (*(current_game + ((i + j) + (i * (b_lines - 1)))) == '#') {
                printf("  #  ");
            } else {
                for (k = 0; k < 5; k++) {
                    putchar(' ');
                }
            }
            if (j != (b_cols - 1))
                printf(" ");
        }
        putchar('\n');

        for (n = 0; n < b_cols; n++) {
            for (k = 0; k < 1; k++) {
                putchar(' ');
            }
            for (k = 0; k < 3; k++) {
                putchar('-');
            }
            for (k = 0; k < 2; k++) {
                putchar(' ');
            }
        }
        printf(" L%d", i);
        putchar('\n');
    }
    for (i = 0; i < b_cols; i++) {
        printf("  C%d  ", i);
    }
    putchar('\n');
    putchar('\n');
}

void show_address(int b_lines, int b_cols, char *current_game) {
    int i, j, n, k;
    putchar('\n');
    for (i = 0; i < b_cols; i++) {
        printf("  C%d  ", i);
    }
    putchar('\n');
    putchar('\n');
    for (i = 0; i < b_lines; i++) {

        for (j = 0; j < b_cols; j++) {
            printf("  %d  ", (current_game + ((i + j) + (i * (b_lines - 1)))));
            if (j != (b_cols - 1))
                printf("|");
        }

        putchar('\n');

        for (n = 0; n < b_cols; n++) {
            for (k = 0; k < 1; k++) {
                putchar(' ');
            }
            for (k = 0; k < 3; k++) {
                putchar('-');
            }
            for (k = 0; k < 2; k++) {
                putchar(' ');
            }
        }
        printf(" L%d", i);
        putchar('\n');
    }
    //putchar('\n');
}

int newcolline(int b_lines, int b_cols, char charinput, const char *current_game, int a, int b, int player, int newcolline_p1, int newcolline_p2) {
    char *aux = 0;

    aux = realloc(aux, sizeof(char*) * (b_lines*b_cols));

    if (aux == NULL) {
        printf("Erro na realocacao %lld\n ", sizeof(char *) * (b_lines * b_cols));
        return b_cols;
    }else{

        if (player == 1 && newcolline_p1 >= 1) {
            if (a == 'C' || b == 'C') {
                printf("\nColuna acrescentada ao tabuleiro a pedido do jogador  %d", player);

            } else {
                printf("\nLinha acrescentada ao tabuleiro a pedido do jogador  %d", player);

            }
            return 1;
        } else if (player == 2 && newcolline_p2 >= 1) {
            if (a == 'C' || b == 'C') {
                printf("\nColuna acrescentada ao tabuleiro a pedido do jogador  %d", player);

            } else {
                printf("\nLinha acrescentada ao tabuleiro a pedido do jogador  %d", player);

            }
            return 1;
        } else {
            return 0;

        }
    current_game = aux;

    free(aux);
    }
    return 0;
}

int joker_play(int player, int joker_p1, int joker_p2) {
    int joker = 0;
    if (player == 1 && joker_p1 == 0) {
        printf("\nJOCKER - Introduza as coordenadas para colocar a Pedra(#): \n\n");
        joker = 1;
    }
    if (player == 2 && joker_p2 == 0) {
        printf("\nJOCKER - Introduza as coordenadas para colocar a Pedra(#): \n\n");
        joker = 1;
    }

    if (joker == 0) {
        printf("\n\nJa utilizou o seu Joker, nao pode colocar mais uma pedra no tabuleiro. Insira uma jogada válida!\n\n");
    }
    return joker;
}

void game_rules() {
    printf("No inicio, o tabuleiro esta vazio e um tabuleiro de tamanho quadrado definido no inicio do jogo entre 3 e 5 linhas\n");

    printf("Os jogadores colocam as pecas de cor Verde (G), Amarela (Y) ou Vermelha (R). O jogador A joga sempre em primeiro.\n");

    printf("OBJETIVO: Ganha o jogador que coloque uma pela que permita formar uma linha, coluna ou diagonal completa com pelas da mesma cor.\n");

    printf("\nAs jogadas validas sao as seguintes:\n");
    printf("1.\tColocar uma pela Verde (G) numa celula vazia\n");
    printf("2.\tTrocar uma pela Verde (G) que esteja colocada no tabuleiro por uma pela Amarela (Y)\n");
    printf("3.\tTrocar uma pela Amarela (Y) que esteja colocada no tabuleiro por uma pela Vermelha (R)\n\n");

    printf("Existem duas jogadas adicionais que podem ser efetuadas pelos jogadores:  \n");
    printf("4.\tColocar uma pedra (#) numa celula vazia. Cada jogador tem este joker que pode colocar, no maximo, uma por jogo.");
    printf("Colocar uma pedra (#) inviabiliza que o jogo possa terminar por preenchimento da linha e coluna afetadas ( e, eventualmente tambem da diagonal ou diagonais ).\n");
    printf("5.\tAdicionar uma linha ou uma coluna ao final do tabuleiro. Esta jogada adiciona linhas ou colunas completas e vazias ao tabuleiro de jogo. ");
    printf("Cada jogador pode efetuar esta jogada, no maximo, duas vezes por jogo.\n\n");

    printf("Como jogar: \n");
    printf("-- Insira: digitos nas coordenadas \n"
           "-- Insira:R mostra as regras \t\t-- Insira:P Jogada da Pedra \t\t\n"
           "-- Insira:M Mostra o tabuleiro\t\t-- Insira:C Adiciona uma coluna\n"
           "-- Insira:N Para novo jogo\t\t-- Insira:L Adiciona uma linha\n"
           "-- Insira:E Stats\t\t\t-- Insira:V Para verificar as ultimas jogadas\n"
           "-- Insira:S Para sair do jogo\t\t\n");
}

void game_info() {

    printf("\n************ O Jogo do Semaforo ************\n");
    printf("\nJogo de tabuleiro inventado pelo matematico Alan Parr.\n ");

    printf("\nTrabalho desenvolvido em contexto academico para a disciplina de Programacao - ISEC - 2020/2021 \n");
    printf("\nAluno: Carlos Santos - Email: a2003035578@isec.pt \n ");

    //game_rules();
}

int main_menu(int config_menu){
    FILE *f;
    fflush(stdin);
    do{
        f = fopen("jago.bin", "rb");
        if ((f) == NULL) {
            printf("\nSem jogos anteriores  guardados\n");
        }else{
            printf("\nPara retomar o jogo anterior - tecla 0\n");

        }
        fclose(f);
        printf("\nTecla 1: Jogar");
        printf("\nTecla 2: Regras do jogo / Como jogar");
        printf("\nTecla 3: Personalizar nomes dos jogadores");
        printf("\nTecla 4: Modo de jogo single/multi-player");
        printf("\nTecla 5: Apagar estatisticas");

        printf("\nTecla 6: Sair");
        //printf("\nTamanho de tabuleiro aleatório - Tecla: 4");

        printf("\n\nIndique a sua escolha:");
        scanf("%d", &config_menu);
        printf("\n\nIndique a sua escolha:%d", config_menu);

    }while((config_menu > 6));


    putchar('\n');
    return config_menu;
}

int gamemode(int check, int t_player) {
    if (check == 0) {
        if (t_player == 2) {
            printf("\n\nModo jogador vs jogador - Alterado - Jogador vs Computador\n\n");
            t_player = 1;

        } else {
            printf("\n\nModo jogador vs computador - Alterado - Jogador vs Jogador\n\n");
            t_player = 2;
        }
    } else {
        if (t_player == 2) {
            printf("Modo jogador vs jogador - verificado\n");


        } else if (t_player == 0) {
            printf("Modo jogador vs computador standard selecionado automaticamente\n");

        } else {
            printf("Modo jogador vs computador  - verificado\n");
        }
    }
    return t_player;
}

void timeprint() {
    char temp[100];
    time_t current_time = time(NULL);
    struct tm *tm = localtime(&current_time);
    strftime(temp, sizeof(temp), "%c", tm);
    printf("\nMuito Bemvindo! Inicio de jogo:   ");
    printf("%s\n\n", temp);
}

void delete_stats() {
    int stats_game = 0;
    char file[] = "stats.bin", file2[] = "Jago.bin";

    printf("\nConfirme que deseja apagar as estatisticas de todos os jogos:\n1 - Sim \n2 - Nao\n");
    scanf("%d", &stats_game);
    if (stats_game == 1) {
        remove(file);
        remove(file2);
    }
}

void del_lastgame() {
    int stats_game = 0;
    char file[] = "Jago.bin";

    remove(file);
}
