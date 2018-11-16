#include <stdio.h>

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

int carrega_mapa(cell_mapa mapa[40][40], int Y, int lado);

int carrega_interface(cell_mapa mapa[40][40], imagens_data imagens, mouse_data mouse);

int cria_base(cell_mapa mapa[40][40], int i, int j, int time);

int carrega_base(cell_mapa mapa[40][40], imagens_data imagens);
