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
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "utils.h"
#include "moves.h"
#include "gdata.h"

#define MBRAND 5
#define MBSIZE ((MBRAND*MBRAND)+4)

int game_play(pmoves* mlist, stats* slist, char *player1, char *player2, int b_square, int b_lines,
               int b_cols,
               int g_move_aux, int type_player, char *current_game) {
    pmoves listed = *mlist;
    int joker = 0, newcolline_p1 = 2, newcolline_p2 = 2, joker_p1 = 0, joker_p2 = 0, joker_rdm, valid = 0, player = 1, win_game = 0, precheck = -1, win_precheck = 0, game_move = g_move_aux+1, new_size = 0, winner = 0, save=0, sair=0;
    char a = 0, b = 0, x = 0, y = 0, *player_name;

    do {
        if (game_move % 2 == 0) { //Muda de jogador
            player = 2;
            player_name = player2;
        } else {
            player = 1;
            player_name = player1;
        }
        do {
            if (type_player == 2 || player == 1) {//Jogadores humanos
                do {
                    printf("\nJogador %s introduz as coordenadas\n\n", player_name);
                    fflush(stdin);
                    printf("L:");
                    scanf("%c", &a);
                    fflush(stdin);
                    if (isdigit(a)) {
                        printf("C:");
                        scanf("%c", &b);
                        fflush(stdin);
                    }
                    a = toupper(a);
                    b = toupper(b);

                    if  (a == 'A' || b == 'A') {
                        printf("\n\n----------------Check admin: %d-------------------\n", game_move);
                        show_moves(listed);
                        show_address(b_lines, b_cols, current_game);
                    }else if (a == 'C' || b == 'C') { // Adiciona Coluna
                        if (player == 1 && newcolline_p1 > 0) {
                            b_cols++;
                            newcolline_p1--;
                            show_board(b_lines, b_cols, current_game);
                            newcolline(b_lines, b_cols, 'C', current_game, a, b, player, newcolline_p1, newcolline_p2);

                        } else if (player == 2 && newcolline_p2 > 0) {
                            b_cols++;
                            newcolline_p2--;
                            show_board(b_lines, b_cols, current_game);
                            newcolline(b_lines, b_cols, 'C', current_game,a, b, player, newcolline_p1, newcolline_p2);

                        } else {
                            printf("\n\nJa utilizou todas as possibilidades de acrescentar linhas ou colunas. Insira uma jogada válida!\n\n");
                        }
                    } else if (a == 'E' || b == 'E') { // Estatiticas
                        printf("\n\nStats:\n\n");
                        stats_rebuild(slist);
                    }else if (a == 'L' || b == 'L') { // Adiciona linha
                        if (player == 1 && newcolline_p1 > 0) {
                            b_lines++;
                            newcolline_p1--;
                            show_board(b_lines, b_cols, current_game);
                            newcolline(b_lines, b_cols, 'L', current_game, a, b, player, newcolline_p1, newcolline_p2);
                        } else if (player == 2 && newcolline_p2 > 0) {
                            b_lines++;
                            newcolline_p2--;
                            show_board(b_lines, b_cols, current_game);
                            newcolline(b_lines, b_cols, 'C', current_game, a, b, player, newcolline_p1, newcolline_p2);
                        } else {
                            printf("\n\nJa utilizou todas as possibilidades de acrescentar linhas ou colunas. Insira uma jogada valida!\n\n");
                        }
                    } else if (a == 'J' || b == 'J') { // Muda modo de jogador
                        type_player = gamemode(0, type_player);
                    } else if (a == 'M' || b == 'M') {// Mostra tabuleiro
                        printf("\n\n----------------Game move: %d-------------------\n", game_move);
                        show_board(b_lines, b_cols, current_game);
                    }  else if (a == 'N' || b == 'N') {// Novo tabuleiro com escolha de dimensão personalisada
                        do{
                            printf("\nAo mudar o tamanho o jogo atual termina, pretende continuar?\n");
                            printf("1 - Sim\n");
                            printf("2 - Nao\n");
                            scanf("%d", &new_size);
                        }while(new_size == 0 ||new_size > 2 );
                        if (new_size == 1){
                        return 5;
                        }
                    }else if ((a == 'P' || b == 'P') && joker == 0) { // Lança a pedra
                        if (player == 1) {
                            joker_p1 = joker_play(player, joker_p1, joker_p2);
                            joker = joker_p1;
                        } else {
                            joker_p2 = joker_play(player, joker_p1, joker_p2);
                            joker = joker_p2;
                        }
                    } else if (a == 'R' || b == 'R') { //Mostra as regras
                        game_rules();
                    } else if ((a == 'S' || b == 'S') && game_move >= 1) { // Sair do jogo
                        savedata(mlist, game_move);// Salvar informação do jogo
                        stats_create(slist, type_player, player1, player2, game_move, winner);
                            do{
                                printf("\nConfirme o que pretende:\n");
                                printf("1 - Continuar\n");
                                printf("2 - Desistir do jogo actual e ir para o menu\n");
                                printf("3 - Sair\n");
                                scanf("%d", &sair);
                            }while(sair > 3 );
                            if (sair!=1){
                                win_game = 3;
                                valid = 3;
                                if (sair==2){
                                    return 0;
                                }
                                if (sair==3){

                                    exit(1);
                                }
                            }
                    } else if (a == 'V' || b == 'V') { //mostra jogadas anteriores
                        last_moves(listed, slist, game_move, current_game);
                        show_board(b_lines, b_cols, current_game);
                    } else {
                        if (isdigit(a)) {
                            x = a - 48;
                        } else {
                            printf("L: ");
                            scanf("%c", &a);
                            if (isdigit(a)) {
                                x = a - 48;
                            }
                        }
                        if (isdigit(b)) {
                            y = b - 48;
                        } else {
                            printf("C: ");
                            scanf("%c", &b);
                            if (isdigit(b)) {
                                y = b - 48;
                            }
                        }
                    }

            } while (!isdigit(a) || !isdigit(b));

         if(isdigit(a) && isdigit(b)){
                // Valida e joga o player 1 e player dois em modo human vs human
                    valid = 0;
                    valid = valid_place(x, y, b_lines, b_cols, current_game);
                    if (valid >= 1) {
                        valid += place_piece(x, y, joker, b_lines, b_cols, current_game);
                        valid = 2;
                        printf("\n Coordenadas L:%d\tC:%d", x, y);
                    }
                }
                win_precheck = win_count(1, b_lines, b_cols, current_game);

            } else { //Jogadas feitas pelo computador
                precheck = win_count(0, b_lines, b_cols, current_game); //Verifica se não ganhou e verifica a probabilidade de ganhar
                if (precheck <=-1) {  //Valida e joga e no caso do computador valida e joga se não tiver probabilidade de ganhar
                        valid = 0;
                        printf("\nO computador introduziu as coordenadas\t");
                        printf("\n L:%d\tC:%d", x, y);

                        joker_rdm = intUniformRnd(0, b_lines * b_cols); //Nivel de dificuldade acrescida contra o computador: lançamento de pedra
                        if (joker_p2 == 0 && joker_rdm == 3) {
                            joker_p2 = 1;
                            joker = 1;
                        } else {
                            joker = 0;
                        }
                        if (b_square == 3 && *(current_game + 4) == 'G') { //Nivel de dificuldade acrescida contra o computador no caso de tabuleiro 3x3, para jogada de peça no meio do tabuleiro
                            x = 1;
                            y = 1;
                        } else { //Se computador não ganhar e se não tiver probabilidade de ganhar prepara jogada aleatória

                            x = intUniformRnd(0, b_square - 1); // NOLINT(cppcoreguidelines-narrowing-conversions)
                            y = intUniformRnd(0, b_square - 1); // NOLINT(cppcoreguidelines-narrowing-conversions)
                        }
                        valid = valid_place(x, y, b_lines, b_cols, current_game);
                        if (valid >= 1) {
                            valid += place_piece(x, y, joker, b_lines, b_cols, current_game);
                            valid = 2;
                        }

                    } else {
//Nivel de dificuldade acrescida contra o computador: se calculo de probabilidade de ganho a jogada é feita na função win_count e é necessário validar a jogada
                        valid = 2;
                        break;
                    }
                }
        } while (valid < 2); // Se a jogada não for válida o ciclo repete até uma jogada válida

        listed = insert_end(*mlist, x, y, b_lines, b_cols, joker, joker_p1, joker_p2, player1, player2, newcolline_p1,
                            newcolline_p2,
                            type_player, player, game_move, current_game); // Insere os dados na lista ligada

        win_precheck = win_count(1, b_lines, b_cols, current_game);

        printf("\n\n----------------Jogada: %d-------------------\n", game_move++);

        if (win_precheck > 0 && win_precheck < 5) { // Anuncia quem ganhou e mostra o tabuleiro
            win_game = 1;

            printf("#%d --------> O JOGADOR %d!!! GANHOU!!! <--------", win_precheck,
                   player); // Anuncia quem ganhou e mostra o tabuleiro
            show_board(b_lines, b_cols, current_game);
            winner = player;
        } else {
            show_board(b_lines, b_cols, current_game); // Mostra o tabuleiro e continua o jogo
            savedata(mlist, game_move);// Salvar informação do jogo
            joker = 0;
        }
    } while (win_game == 0 && game_move < (b_lines * b_cols * 3)); // se ninguém ganhar o Win_game fica a zero e o game_move atinge o maximo de jogadas
    if (game_move >= (b_lines * b_cols * 3)) {
        printf("# --------> Jogo empatado!!! <--------");
        winner = 0;
    }
    stats_create(slist, type_player, player1, player2, game_move, winner);
    printf("\nDeseja gravar o jogo num ficheiro de texto?\n 1 - Sim\n 2 - Nao\n");
    scanf("%d", &save);

    if (save == 1) {
        savedataend(mlist, game_move);
        printf("\nJogo guardado!\n");
    }

return 0;
}

int valid_input(char input_value) {

    if (input_value == 'G' || input_value == 'Y' || input_value == 'R' || input_value == '#') {
        return 1;
    } else {
        return 0;
    }
}

int valid_place(char x, char y, int b_lines, int b_cols, const char *current_game) {

    if (x >= 0 && x < b_lines && y >= 0 && y < b_cols && *(current_game + ((x + y) + (x * (b_lines - 1)))) != '#' &&
        *(current_game + ((x + y) + (x * (b_lines - 1)))) != 'R') {
        return 1;
    }
    return 0;
}

int win_count(int checktype, int b_lines, int b_cols, char *current_game) {
    int i, j, k, countlin = 1, b_squarebigger=0, evalsuites = 0, countcol = 1, count_diag_m = 1, count_diag_s = 1, nextindice, indice;
    char a, b;

    if (b_lines == b_cols) {
        b_squarebigger = b_cols;
    }

    for (i = 0; i <= b_lines - 1; i++) {
        countlin = 1;
        countcol = 1;
        for (j = 0; j <= b_cols - 1; j++) {
            indice = ((i + j) + (i * (b_cols - 1)));
            nextindice = indice + 1;
            a = *(current_game + indice);
            b = *(current_game + nextindice);
            evalsuites = valid_input(a) && a == b && indice/b_cols==nextindice/b_cols; // Verifica se input valido, se são iguais e se não passa os limites

            if (evalsuites == 1) {
                countlin++;

                //Win lines check
                if (checktype == 1 && countlin >= b_cols && countcol < b_lines && count_diag_m < b_squarebigger &&
                    count_diag_s < b_squarebigger) {

                    return 1;
                }
            }
            //probability lines check
            if (checktype == 0 && countlin >= b_cols - 1) {

                for (k = 0; k <= b_cols - 1 && a != b && a!='#'; k++) {

                    place_piece_variant(nextindice, 0, b_lines, b_cols, current_game);
                    printf("\n Computador ganhou por linhas - Na casa: %d", nextindice+1);
                    return 5;

                }
            }

            indice = ((i + j) + (j * (b_lines - 1)));
            nextindice = indice + (b_lines);
            a = *(current_game + indice);
            b = *(current_game + nextindice);
            evalsuites = valid_input(a) && a == b && nextindice<b_lines*b_cols;;
            if (indice/b_lines == 0){countcol =1;}
            if (evalsuites == 1) {
                countcol++;

                //Win Columns check
                if (checktype == 1 && countcol >= b_lines) {

                    if (countlin < b_cols && a == b && count_diag_m < b_squarebigger &&
                        count_diag_s < b_squarebigger) {
                        return 2; //'' meter por caracteres tipo x1
                    }
                }
            }
            //probability Columns check

            if (checktype == 0 && countcol >= b_lines - 1) {
                for (k = 0; k <= b_lines - 1 && a != b && a!='#'; k++) {
                    place_piece_variant(nextindice, 0, b_lines, b_cols, current_game);
                    printf("\n Computador ganhou por colunas - Na casa: %d", nextindice+1);
                    return 6;
                }
            }
        }

        if (b_lines == b_cols) {
            count_diag_m = 1;
            for (j = 0; j <= b_squarebigger - 1; j++) {
                indice = ((b_squarebigger + 1) * j);
                nextindice = ((b_squarebigger + 1) * (j + 1));
                a = *(current_game + indice);
                b = *(current_game + nextindice);
                evalsuites = valid_input(a) && a == b && nextindice<b_lines*b_cols;

                if (evalsuites == 1) {
                    count_diag_m++;

                    //Win diagonal main check
                    if (checktype == 1 && count_diag_m >= b_squarebigger) {

                        if (countlin < b_lines && countcol < b_lines && a == b &&
                            count_diag_s < b_squarebigger) {
                            return 3;
                        }
                    }
                }
                //probability diagonal main check
                if (checktype == 0 && count_diag_m >= b_squarebigger - 1) {

                    for (k = 0;
                         k <= b_squarebigger - 1 && a != b && a!='#'; k++) {
                        place_piece_variant(nextindice, 0, b_lines, b_cols, current_game);

                        printf("\n O Computador ganhou por diagonal main - Na casa: %d", nextindice+1);
                        return 7;
                    }
                }
            }
        }
    }

    if (b_lines == b_cols) {
        count_diag_s = 1;
        for (k = 0; k <= b_squarebigger; k++) {

            indice = ((b_squarebigger - 1) * k);
            nextindice = ((b_squarebigger - 1) * (k + 1));

            a = *(current_game + indice);
            b = *(current_game + nextindice);
            evalsuites = valid_input(a) && a == b && nextindice<b_lines*b_cols;
            //printf("\n\t x:%d DIAGONAL secundaria current_game[K][k]:%c\n", k, a);

            if (evalsuites == 1 && indice>0) {
                count_diag_s++;

                //Win diagonal secondary check

                if (checktype == 1 && count_diag_s >= b_squarebigger) {
                    if (countlin < b_cols && countcol < b_lines && count_diag_m < b_squarebigger && a == b) {

                        return 4;
                    }
                }
            }
            //probability diagonal secondary check
            if (checktype == 0 && count_diag_s >= b_squarebigger - 1) {
                for (j = 0;
                     j <= b_squarebigger - 1 && a != b && a!='#'; j++) {
                    place_piece_variant(nextindice, 0, b_lines, b_cols, current_game);
                    printf("\n O Computador ganhou por diagonal main - diagonal main Na casa: %d", nextindice+1);
                    return 8;
                }
            }
        }
    }
    return -1;
}

int place_piece(char x, char y, int joker, int b_lines, int b_cols, char *current_game) {

    // variante mete pedra em qualquer lugar - Correção de conformidade com os requisitos embora o jogo seja mais interessante com a pedra prioritária
    //if (joker == 1) {//pedra no meio do jogo
    if (joker == 1 && (*(current_game + ((x + y) + (x * (b_lines - 1)))) == '-')) {//pedra no meio do jogo
        *(current_game + ((x + y) + (x * (b_lines - 1)))) = '#';
        return 1;
    }

    if (*(current_game + ((x + y) + (x * (b_lines - 1)))) == 'G') {
        *(current_game + ((x + y) + (x * (b_lines - 1)))) = 'Y';
        return 1;
    } else if (*(current_game + ((x + y) + (x * (b_lines - 1)))) == 'Y') {
        *(current_game + ((x + y) + (x * (b_lines - 1)))) = 'R';
        return 1;
    }

    *(current_game + ((x + y) + (x * (b_lines - 1)))) = 'G';

    return 1;
}

int place_piece_variant(int indice, int joker, int b_lines, int b_cols, char *current_game) {

    if (joker == 1 && *(current_game + indice) == '-'){//pedra no meio do jogo
        *(current_game + indice) = '#';
        return 1;
        return 1;
    }
    if (*(current_game + indice) == 'G') {
        *(current_game + indice)= 'Y';
        return 1;
    } else if (*(current_game + indice) == 'Y') {
        *(current_game + indice) = 'R';
        return 1;
    }

    *(current_game + indice) = 'G';

    return 1;
}

//Reverte as peças no tabuleiro
int revert_piece(char x, char y, int joker, int b_lines, int b_cols, char *current_game) {

    if (*(current_game + ((x + y) + (x * (b_lines - 1)))) == 'Y') {
        *(current_game + ((x + y) + (x * (b_lines - 1)))) = 'G';
        return 1;
    } else if (*(current_game + ((x + y) + (x * (b_lines - 1)))) == 'R') {
        *(current_game + ((x + y) + (x * (b_lines - 1)))) = 'Y';
        return 1;
    } else if (*(current_game + ((x + y) + (x * (b_lines - 1)))) == 'G') {
        *(current_game + ((x + y) + (x * (b_lines - 1)))) = '-';
        return 1;
    }
    else if (*(current_game + ((x + y) + (x * (b_lines - 1)))) == '#') {
        *(current_game + ((x + y) + (x * (b_lines - 1)))) = '-';
        return 1;
    }

    return 1;
}


pmoves
insert_end(pmoves p, char x, char y, int b_lines, int b_cols, int joker, int joker_p1, int joker_p2, char *player1,
           char *player2, int newcolline_p1,
           int newcolline_p2, int type_player, int player, int game_move, char *current_game) {
    pmoves new_ed, aux;
    new_ed = p;

    if (p->ant  != NULL ) {
        new_ed = malloc(sizeof(moves));
        if (new_ed == NULL) {
            free(new_ed);
            printf("Erro na alocacao de memoria\n");
            return p;
        }

    }
        fill_moves(new_ed, x, y, b_lines, b_cols, joker, joker_p1, joker_p2, player1, player2, newcolline_p1, newcolline_p1,
                   type_player,
                   player, game_move, current_game);

    if (p == NULL) {
        p = new_ed;
    } else {
        aux = p;

        while (aux->prox != NULL){
            aux = aux->prox;
        }
            new_ed->ant = aux;
            aux->prox = new_ed;
            new_ed->prox = NULL;

    }
    return p;
}

pmoves
fill_moves(pmoves p, char x, char y, int b_lines, int b_cols, int joker, int joker_p1, int joker_p2, char *player1,
           char *player2, int newcolline_p1,
           int newcolline_p2, int type_player, int player, int game_move, const char *current_game) {

    p->x = x;
    p->y = y;
    p->b_lines = b_lines;
    p->b_cols = b_cols;
    p->joker = joker;
    p->joker_p1 = joker_p1;
    p->joker_p2 = joker_p2;
    strcpy(p->player1, player1);
    strcpy(p->player2, player2);
    p->newcolline_p1 = newcolline_p1,
    p->newcolline_p2 = newcolline_p2,
    p->type_player = type_player;
    p->player = player;
    p->game_move = game_move;
    p->currentchar = *(current_game + ((x + y) + (x * (b_lines - 1))));
    p->prox = NULL;

    return p;
}

void savedata(pmoves* mlist, int game_m) {
    FILE *f;
    pmoves p = *mlist;
    // 1. Abrir Ficheiro
    if ((f = fopen("jago.bin", "wb+")) == NULL) {

        printf("Erro no acesso ao ficheiro\n");

    }
    // 2. Escrita da informação
    fwrite(&game_m, sizeof(int), 1, f);

    while (p != NULL) {
        fwrite(p, sizeof(moves), 1, f);
        p = p->prox;
    }
    // 3. Fechar o ficheiro
    fclose(f);
}

void savedataend(pmoves* mlist,int game_m) {
    FILE *f;
    pmoves p = *mlist;
    time_t t;
    time(&t);
    char savefile[100];

    printf("Gravar ficheiro com o nome: ");
    scanf("%s", savefile);
    putchar('\n');
    strcat(savefile, ".txt");
    printf("%s\n", savefile);
    // 1. Abrir Ficheiro

    if ((f = fopen(savefile, "w")) == NULL) {
        printf("Erro no acesso ao ficheiro\n");

    }
    // 2. Escrita da informação
    fprintf(f, "Lista de Jogadas: \t");
    fprintf(f, "Data: %s\n", ctime(&t));

    while (p != NULL)  {
        if(p->x<50 && p->y>=0){
            fprintf(f, "L:%d\tC:%d Joker:%d Jogada:%d Caracter:%c\n", p->x, p->y, p->joker, p->game_move,
                    p->currentchar);
        }
        p = p->prox;
    }
    // 3. Fechar o ficheiro
    fclose(f);
}

int rebuild_board(pmoves listed, stats *slist) {
    FILE *f;
    pmoves new_a;
    int i, total, neb_lines, neb_cols, nejoker, nejoker_p1, nejoker_p2, nenewcolline_p1, nenewcolline_p2, netype_player, neplayer, negame_move;
    char nex, ney, newchar, *current_game, *aux, neplayer1[20], neplayer2[20], necurrentchar;

    f = fopen("jago.bin", "rb");
    if ((f) == NULL) {
        printf("Erro no acesso ao ficheiro\n");
        return 0;
    }
    fread(&total, sizeof(int), 1, f);
    // printf("\ni: Tamanho: %d\n", total, 0);


    new_a = malloc(sizeof(moves) * total);
    if (new_a == NULL) {
        free(new_a);
        printf("Erro na alocacao de memoria\n");
        return 0;
    }


    aux = malloc(sizeof(char) * neb_lines* neb_cols);
    if (aux == NULL) {
        free(aux);
        printf("Erro na realocacao\n");
        return 0;
    }
    current_game = aux;
    // newboard(MBRAND+4, current_game);
    printf("\nTotal de jogadas = %d", total);
    for (i = 0; i < total-1 ; i++) {
        fread(new_a, sizeof(moves), 1, f);
        nex = new_a->x;
        ney = new_a->y;
        neb_lines = new_a->b_lines;
        neb_cols = new_a->b_cols;
        nejoker = new_a->joker;
        nejoker_p1 = new_a->joker_p1;
        nejoker_p2 = new_a->joker_p2;
        strcpy(neplayer1, new_a->player1);
        strcpy(neplayer2, new_a->player2);
        nenewcolline_p1 = new_a->newcolline_p1;
        nenewcolline_p2 = new_a->newcolline_p2;
        netype_player = new_a->type_player;
        neplayer = new_a->player;
        negame_move = new_a->game_move;
        necurrentchar = new_a->currentchar;
        new_a->ant;
        new_a->prox;
        if (nejoker == 1) { newchar = '#'; } else { newchar = necurrentchar; }
        *(current_game + 1) = 'Y';
        if (negame_move > 0) {
            place_piece(nex, ney, nejoker, neb_lines, neb_cols, current_game);
            listed = insert_end(listed, nex, ney, neb_lines, neb_cols, nejoker, nejoker_p1, nejoker_p2, neplayer1,
                                neplayer2, nenewcolline_p1, nenewcolline_p2, neplayer, neplayer, negame_move,
                                current_game);
        }
    }
    putchar('\n');
    fclose(f);


    show_board(neb_lines, neb_cols, current_game);

    game_play(&listed, slist, neplayer1, neplayer2, neb_lines, neb_lines, neb_cols, negame_move, netype_player,
              current_game);

    free(new_a);
    free(aux);
    //free(current_game);
    return 1;

}

void show_moves(pmoves p) {
    while (p != NULL) {
        printf("x: %d\ty: %d\tPeca: %c\tjoker: %d\tjoker_p1: %d\tjoker_p2: %d\tplayer: %d\tgame_move:  %d\t atual:%d\tant: %d\tprox: %d\n", p->x, p->y,
               p->currentchar, p->joker, p->joker_p1, p->joker_p2, p->player, p->game_move, p, p->ant, p->prox);
        p = p->prox;
    }
}
//Mostra historico nas ultimas x jogadas
void last_moves(pmoves mlist, stats *slist, int game_move, char *current_game) {
    int plays = 0;
    pmoves aux = mlist;

    printf("Pretende verificar quantas jogadas: ");
    scanf("%d", &plays);

    if (plays < game_move) {
        plays = game_move - plays;
        printf("----- %d \n\n", plays);
        printf("----- %d \n\n", game_move);
        printf("last_movesb_lines> %d \n\n", mlist->b_lines);

        while (mlist != NULL) {

            if (mlist->game_move >= plays) {
                printf("game_move2-> %d \n\n", mlist->game_move);
                //show_board_aux(mlist->b_lines, mlist->b_cols, mlist->x, mlist->y, mlist->currentchar, mlist->game_move, current_game);
                revert_piece(mlist->x, mlist->y, mlist->joker, mlist->b_lines,mlist->b_cols, current_game);
                show_board_aux(mlist->b_lines, mlist->b_cols, mlist->x, mlist->y, mlist->currentchar, mlist->game_move, current_game);
            }
            mlist = mlist->prox;
        }
        fflush(stdin);
        printf("\nQualquer tecla continuar\n");
        getchar();


        while (aux != NULL) {
            if (aux->game_move >= plays) {
            printf("game_move2-> %d \n\n", aux->game_move);
            place_piece(aux->x, aux->y, aux->joker, aux->b_lines, aux->b_cols, current_game);
            }
            aux = aux->prox;
        }
    } else {
        printf("Escolher um valor entre 1 e %d \n\n", game_move);
    }
}

int stats_create(stats *slist1, int type_player, char *player1, char *player2, int game_move, int winner) {
    FILE *f;
    int total=0, game_move2=0, winner2=0, type_player2=0, w1=0,e1=0,d1=0, w2=0, e2=0,d2=0;
    char pl1[20]="Um", pl2[20]="Dois";
    stats slist = *slist1;

    if ((f = fopen("stats.bin", "wb")) == NULL) {

        printf("Erro no acesso ao ficheiro\n");
        return 0;
    }

    if (winner == 1) {
        w1++;
        d2++;
    }else if (winner == 0){
        e1++;
        e2++;
        w1 = 0;
        d2 = 0;
        w2 = 0;
        d1 = 0;
    }
    else{
        w2++;
        d1++;
    }

    while (slist != NULL) {

        strcpy(slist->player1, pl1);
        strcpy(slist->player2, pl2);
        slist->gamesplayed++;
        slist->w1 = slist->w1+w1;
        slist->e1 = slist->e1+e1;
        slist->d1 = slist->d1+d1;
        slist->w2 = slist->w2+w2;
        slist->e2 = slist->e2+e2;
        slist->d2 = slist->d2+d2;
        slist->game_moves = slist->game_moves + game_move;
        slist->type_player = type_player;
        slist->winner = winner;
        slist= slist->prox;

        fwrite(*slist1, sizeof(statiscs), 1, f);
    }

    // 3. Fechar o ficheiro
    fclose(f);

    return 0;
}

int update_sList(stats *slist, int total, int w1, int e1, int d1, int w2, int e2, int d2, int game_moves, int type_player, int winner, char *pl1, char *pl2){
    stats new_ed, aux;

    new_ed = malloc(sizeof(statiscs));
    if (new_ed == NULL) {
        free(new_ed);
        printf("Erro na alocacao de memoria\n");
        return 0;
    }

    // Equipa ja existe
    strcpy(new_ed->player1, pl1);
    strcpy(new_ed->player2, pl2);
    new_ed->gamesplayed = total;
    new_ed->w1 = w1;
    new_ed->e1 = e1;
    new_ed->d1 = d1;
    new_ed->w2 = w2;
    new_ed->e2 = e2;
    new_ed->d2 = d2;
    new_ed->game_moves = game_moves;
    new_ed->type_player = type_player;
    new_ed->winner = winner;

    if (*slist == NULL) {
        *slist = new_ed;
    } else {
        aux = *slist;
    }

    return 0;
}

int stats_rebuild(stats *slist1) {
    FILE *f;
    stats new_a;
    //stats slist = NULL;
    int game_move, game_moves1, game_moves2, winner, type_player, total=0, i,w1=0,e1=0,d1=0, w2=0,e2=0,d2=0;
    char player1[20]="Um", player2[20]="Dois";

    f = fopen("stats.bin", "rb");
    if ((f) == NULL) {
        //printf("Erro no acesso ao ficheiro\n");
        //putchar('\n');
        return 0;
    }

    new_a = malloc(sizeof(statiscs)*1);
    if (new_a == NULL) {
        free(new_a);
        printf("Erro na alocacao de memoria\n");
        return 0;
    }

        fread(new_a, sizeof(statiscs), 1, f);

        total = new_a->gamesplayed;
        game_move = new_a->game_moves;
        w1 = new_a->w1;
        e1 = new_a->e1;
        d1 = new_a->d1;
        w2 = new_a->w2;
        e2 = new_a->e2;
        d2 = new_a->d2;
        type_player = new_a->type_player;
        winner = new_a->winner;

    update_sList(slist1, total, w1, e1, d1, w2, e2, d2, game_move, type_player, winner, player1, player2);
    show_stats(slist1);
    fclose(f);

    return 1;
}

void show_stats(stats *slist1) {
    stats slist = *slist1;

    if (slist != NULL) {
        printf("Jogos: %d \t-- Movimentos: %d \n",
               slist->gamesplayed, slist->game_moves);
        printf("Jogador um \t{Ganhou %d, Empatou %d, Perdeu %d} \n",
               slist->w1, slist->e1, slist->d2);
        printf("Jogador dois \t{Ganhou %d, Empatou %d, Perdeu %d} \n",
               slist->w2, slist->e2, slist->d2);
    }
}

void free_part_listed(pmoves p) {
    pmoves aux;

    aux = p->prox; // para o segundo elemento
    p->prox = NULL;
    p->ant = NULL;
    while (aux != NULL) {
        aux = aux->prox;
        free(aux);
    }

}

void free_listed(pmoves p) {
    pmoves aux;

    while (p != NULL) {
        aux = p;
        p = p->prox;
        free(aux);
    }
}

void free_slisted(stats slist) {
    stats aux;
    if (slist != NULL) {
        aux = slist;
        free(aux);
    }
}


