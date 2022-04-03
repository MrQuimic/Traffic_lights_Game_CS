// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2020-2021
/*
 * Author:Carlos Tiago Simões dos Santos
 * Email: a2003035578@isec.pt
 *
 * Created on: 27 April 2021, 22:57
 * Last Edit: 12 Junho 2021
 */
#ifndef TRAFFIC_LIGHTS_GAME_CS_MOVES_H
#define TRAFFIC_LIGHTS_GAME_CS_MOVES_H
#endif //TRAFFIC_LIGHTS_GAME_CS_MOVES_H

// Estrutura para lista ligada prevista para as jogadas
typedef struct movesed moves, *pmoves;

struct movesed{
    int b_lines, b_cols, joker, joker_p1, joker_p2, newcolline_p1, newcolline_p2, type_player, player, game_move;
    char x, y, player1[20], player2[20], currentchar;
    pmoves ant;
    pmoves prox;
};

// Estrutura para lista ligada prevista para as estatísticas
typedef struct statisc statiscs, *stats;
struct statisc{
    char player1[20], player2[20];
    int gamesplayed, game_moves, w1, e1, d1, w2, e2, d2, type_player,winner;
    stats prox;
};

int game_play(pmoves* mlist, stats* slist, char *player1, char *player2, int b_square, int b_lines, int b_cols, int g_move_aux, int type_player, char *current_game); // Controlo de jogo

int valid_input(char input_value); //Caracteres validos para jogar
int valid_place (char x, char y, int b_lines, int b_cols, const char *current_game);
int win_count(int checktype, int b_lines, int b_cols, char *current_game);
int place_piece (char x, char y, int joker, int b_lines, int b_cols, char *current_game);
int place_piece_variant(int indice, int joker, int b_lines, int b_cols, char *current_game);
int revert_piece(char x, char y, int joker, int b_lines, int b_cols, char *current_game);

pmoves insert_end(pmoves p, char x, char y, int b_lines, int b_cols, int joker, int joker_p1, int joker_p2, char *player1, char *player2,int newcolline_p1, int newcolline_p2, int type_player, int player, int game_move, char *current_game); // Insere as jogadas no fim da lista ligada em conjunto com a função fill_moves
pmoves fill_moves(pmoves p, char x, char y, int b_lines, int b_cols, int joker, int joker_p1, int joker_p2, char *player1, char *player2, int newcolline_p1, int newcolline_p2, int type_player, int player, int game_move, const char *current_game); // Insere as jogadas no fim da lista ligada em conjunto com a função insert_end

void savedata(pmoves *p, int game_move); // Salva as informações relevantes do jogo no ficheiro "jago.bin"
void savedataend(pmoves *p, int game_move); // Salva os dados do jogo a pedido do jogador

int rebuild_board(pmoves listed, stats* slist); // função para reconstruir o último jogo caso o jogador pretenda recuperar

void show_moves(pmoves p); // mostra as jogadas - Lista de todas as jogadas na lista ligada
void last_moves(pmoves listed, stats* slist, int game_move, char *current_game); // Para verificar os últimos movimentos

int stats_create(stats *slist, int type_player, char *player1, char *player2, int game_move, int winner);  // Insere as jogadas no fim da lista ligada em conjunto com a função fill_moves
int update_sList(stats *slist, int total, int w1, int e1, int d1, int w2, int e2, int d2, int game_moves, int type_player, int winner, char * pl1, char * pl2); //Adiciona as estatísticas a partir do ficheiro “stats.bin” em conjunto com a função “stats_rebuild”
int stats_rebuild(stats *slist); //Adiciona as estatísticas a partir do ficheiro “stats.bin” em conjunto com a função “update_sList” e apresenta as estatísticas de jogo em conjunto conjunto com a função “show_stats”
void show_stats(stats *slist); //Mostra as estatísticas função chamada por “stats_rebuild”
void free_part_listed(pmoves p); // liberta todos os nós da lista pmoves a partir do segundo elemento e coloca no primeiro o pmoves prox e ant a null
void free_listed(pmoves p); //Liberta todos os nós da lista pmoves
void free_slisted(stats slist); //Liberta todos os nós da lista stats