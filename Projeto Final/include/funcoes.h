/**
 * @file headers.h
 *
 * @brief Arquivo com a declaração das funções do jogo
 *
 * @author Grupo 2
 *
 */

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"
#include "string"

#define RX 900
#define RY 600
#define BLOCOS_LINHA 40
#define DIMENSAO_COMANDANTE 0.2 * RY
#define TRANSLADA_COMANDANTE 0.02 * RX
#define DIVISAO_INFERIOR 0.08 * RY
#define DIMENSAO_ICONES 0.05 * RY
#define TAMANHO_TEXTO_ICONES 2.2 * DIMENSAO_ICONES
#define LARGURA_BARRAS 0.015 * RY

const int LADO = RY/BLOCOS_LINHA;
enum divisao {HUMANO = 0, MECANICO, ELETRICO, OPERARIO};
enum classe {GERADOR_DE_RECURSO = 3, GERADOR_DE_TROPA,
                DEFESA_OFENSIVA, DEFESA_PASSIVA};
enum unidades_e_base {REPLICANTE = 7, EXTERMINADOR, HATSUNE, WALL,
                    DROIDES, IRON, MERCENARIOS, CAVALEIROS,
                    CHORIS, BASE};

typedef struct Player_Data {

int comida;
int minerio;
int eletricidade;
int xp;
int nivel;

}player_data;

typedef struct Unidade_Movel {
    int vida;
    int ataque;
    int defesa;
    int alcance;
    int velocidade;
    int divisao;
    int time;
    int nivel;
    int dim;
    int i;
    int j;
    int custo_minerio;
    int custo_comida;
    int custo_eletricidade;
}unidade_movel;

typedef struct Unidade_Estatica {
    int vida;
    int ataque;
    int defesa;
    int alcance;
    int classe;
    int divisao;
    int time;
    int nivel;
    int dim;
    int i;
    int j;
    int custo_minerio;
    int custo_comida;
    int custo_eletricidade;
    int producao;
}unidade_estatica;

typedef struct Base_Principal {
    int vida;
    int time;
    int dim;
    int i;
    int j;
}base_principal;

typedef struct Cell_Mapa {
    int x;
    int y;
    int lado;
    unidade_movel *pUniMovel;
    unidade_estatica *pUniImovel;
    base_principal *pBase;
}cell_mapa;

typedef struct Imagens_Data {
    unsigned int textura_grade; 
    unsigned int textura_fundo;
    unsigned int textura_base;
    unsigned int textura_menu_principal;
    unsigned int humano_GER_REC;
    unsigned int humano_GER_TROP;
    unsigned int humano_DEF_OFS;
    unsigned int humano_DEF_PAS;
    unsigned int mecanico_GER_REC;
    unsigned int mecanico_GER_TROP;
    unsigned int mecanico_DEF_OFS;
    unsigned int mecanico_DEF_PAS;
    unsigned int eletrico_GER_REC;
    unsigned int eletrico_GER_TROP;
    unsigned int eletrico_DEF_OFS;
    unsigned int eletrico_DEF_PAS;
    unsigned int minerio;
    unsigned int raio;
    unsigned int comida;
    unsigned int operario;
}imagens_data;

typedef struct Mouse_Data {
    int x;
    int y;
    int x_mem;
    int y_mem;
}mouse_data;

typedef struct Atributos_Data {
    int classe;
    int divisao;
    int time;
    int nivel;
}atributos_data;

typedef struct Texto_Data {
    unsigned int numero_textura[101];
    unsigned int nome_textura[20];
}texto_data;

int min(int a, int b);

int max(int a, int b);

GLuint loadTexture(const std::string&fileName);

GLuint importText(const std::string &text, int font_size, int red, int green, int blue);

int cria_mapa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA]);

int carrega_interface(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data mouse, texto_data texto, player_data *player, atributos_data atributos);

int cria_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, int dim, int vida, int time);

int carrega_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens);

bool verifica_imagem(const std::string&fileName);

bool verifica_espaco(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j);

int verifica_selecao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data mouse);

int verifica_unidades(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data mouse, player_data *player, atributos_data atributos);

bool verifica_velocidade(unidade_movel* aux, int cell_i, int cell_j);

int cria_uni_estatico(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, atributos_data atributos, player_data *player);

int carrega_uni_estatico(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens);

int carrega_display_recursos (imagens_data imagens, texto_data texto);

int carrega_mapa (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data mouse);

int carrega_layout();

int colore_espacos_validos(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* aux);

int carrega_uni_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, texto_data texto);

int cria_uni_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, atributos_data atributos, player_data *player);

int carrega_numeros_recurso (texto_data texto, player_data *player);

int mostra_menu(SDL_Surface* screen, TTF_Font* font);
    
int move_unidade (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* unit, int i, int j);

int carrega_barras(imagens_data imagens);

int combate(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, unidade_movel *aux2, player_data *player);

int destruicao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, unidade_estatica *aux2, player_data *player);

int carrega_comandante(imagens_data imagens);

int carrega_caixa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data mouse, imagens_data imagens, texto_data texto);

int escolhe_imagem_estatica(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, int i, int j);

int escolhe_imagem_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, texto_data texto, int i, int j, int opcao);

int escolhe_texto_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], texto_data texto, int i, int j);

int construction(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, int cell_i, int cell_j, unidade_movel* unit, player_data *player);

void Atualizar_recursos(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], player_data *player);

int player_level(player_data *player);

//define_mov_rang(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* aux);

int evolution(unidade_estatica *aux, player_data *player);