#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>
#include "SDL/SDL_image.h"
#include "string"

#define RX 1200
#define RY 800
#define LADO 20
#define BLOCOS_LINHA 40

typedef struct Posicao {
    int x;
    int y;
    struct Posicao *prox;
}posicao;

typedef struct Unidade_Movel {
    int vida;
    int ataque;
    int defesa;
    int alcance;
    int velocidade;
    int divisao;
    int time;
    int nivel;
    posicao local;
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
    posicao local;
}unidade_estatica;

typedef struct Base_Principal {
    int vida;
    int i;
    int j;
    int time;
    int dim;
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
}imagens_data;

typedef struct Mouse_Data {
    int x;
    int y;
}mouse_data;

GLuint loadTexture(const std::string&fileName);

int cria_mapa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA]);

int carrega_interface(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data mouse);

int cria_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, int dim, int vida, int time);

int carrega_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens);

bool verifica_imagem(const std::string&fileName);

