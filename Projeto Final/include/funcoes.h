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
}base_principal;

typedef struct Cell_Mapa {
    int x;
    int y;
    int lado;
    unidade_movel *pUniMovel;
    unidade_estatica *pUniImovel;
}cell_mapa;

GLuint loadTexture(const std::string&fileName);

int carrega_mapa(cell_mapa mapa[40][40], int Y, int lado);

int carrega_interface(cell_mapa mapa[40][40]);
