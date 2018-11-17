#include "funcoes.h"

int cria_mapa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA]) {
    int x = 0;
    int y = 0;

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            mapa[i][j].x = x;
            mapa[i][j].y = y;
            mapa[i][j].lado = LADO;
            mapa[i][j].pBase = NULL;
            mapa[i][j].pUniMovel = NULL;
            mapa[i][j].pUniImovel = NULL;
            x += LADO;
        }
        y += LADO;
        x = 0;
    }
    return 0;
}

int cria_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, int dim, int vida, int time) {
    base_principal *Base = (base_principal*)malloc(sizeof(base_principal));
    Base->i = i;
    Base->j = j;
    Base->dim = dim;
    Base->vida = vida;
    Base->time = time;

    for (int p = i; p <= (i + dim-1); p++) {
        for (int q = j; q <= (j + dim-1); q++) {
            mapa[p][q].pBase = Base;
        }
    }
    return 0;
}
