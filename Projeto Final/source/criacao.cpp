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
            if (verifica_espaco(mapa, p, q) == true)
                mapa[p][q].pBase = Base;
            else
                return -1;
        }
    }
    return 0;
}

int cria_uni_estatico(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, atributos_data atributos) {
    unidade_estatica *Unidade = (unidade_estatica*)malloc(sizeof(unidade_estatica));
    Unidade->i = i;
    Unidade->j = j; 
    Unidade->time = atributos.time;
    Unidade->classe = atributos.classe;
    Unidade->divisao = atributos.divisao;
    Unidade->nivel = atributos.nivel;

    /*  
        CLASSE 1: GERADOR DE RECURSO
        CLASSE 2: GERADOR DE TROPA
        CLASSE 3: DEFESA OFENSIVA
        CLASSE 4: DEFESA PASSIVA
    */
    
    switch (atributos.classe) {
        case GERADOR_DE_RECURSO:
            Unidade->dim = 3;
            Unidade->vida = 10;
            Unidade->ataque = 0;
            Unidade->defesa = 5;
            Unidade->alcance = 0;
            break;
        case GERADOR_DE_TROPA:
            Unidade->dim = 3;
            Unidade->vida = 10;
            Unidade->ataque = 0;
            Unidade->defesa = 5;
            Unidade->alcance = 0;
            break;
        case DEFESA_OFENSIVA:
            Unidade->dim = 2;
            Unidade->vida = 10;
            Unidade->ataque = 3;
            Unidade->defesa = 5;
            Unidade->alcance = 2;
            break;
        case DEFESA_PASSIVA:
            Unidade->dim = 1;
            Unidade->vida = 10;
            Unidade->ataque = 0;
            Unidade->defesa = 5;
            Unidade->alcance = 0;
            break;
    }

    for (int p = i; p <= (i + Unidade->dim-1); p++) {
        for (int q = j; q <= (j + Unidade->dim-1); q++) {
            if (verifica_espaco(mapa, p, q) == true)
                mapa[p][q].pUniImovel = Unidade;
            else
                return -1;
        }
    }
    return 0;
}

int cria_uni_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, atributos_data atributos) {
    unidade_movel *Unidade = (unidade_movel*)malloc(sizeof(unidade_movel));
    Unidade->i = i;
    Unidade->j = j; 
    Unidade->time = atributos.time;
    Unidade->divisao = atributos.divisao;
    Unidade->nivel = atributos.nivel;
    Unidade->dim = 1;

    switch (Unidade->divisao) {
        case HUMANO:
            switch (Unidade->nivel) {
                case 1:
                    Unidade->vida = 3;
                    Unidade->ataque = 5;
                    Unidade->defesa = 1;
                    Unidade->alcance = 4;
                    Unidade->velocidade = 5;
                    break;
                case 2:
                    Unidade->vida = 5;
                    Unidade->ataque = 6;
                    Unidade->defesa = 2;
                    Unidade->alcance = 1;
                    Unidade->velocidade = 6;
                    break;
                case 3:
                    Unidade->vida = 6;
                    Unidade->ataque = 6;
                    Unidade->defesa = 1;
                    Unidade->alcance = 1;
                    Unidade->velocidade = 10;
                    break;
                }
            break;
        case MECANICO:
            switch (Unidade->nivel) {
                case 1:
                    Unidade->vida = 8;
                    Unidade->ataque = 2;
                    Unidade->defesa = 2;
                    Unidade->alcance = 1;
                    Unidade->velocidade = 6;
                    break;
                case 2:
                    Unidade->vida = 4;
                    Unidade->ataque = 4;
                    Unidade->defesa = 1;
                    Unidade->alcance = 1;
                    Unidade->velocidade = 5;
                    break;
                case 3:
                    Unidade->vida = 10;
                    Unidade->ataque = 10;
                    Unidade->defesa = 3;
                    Unidade->alcance = 2;
                    Unidade->velocidade = 3;
                    break;
                }
            break;
        case ELETRICO:
            switch (Unidade->nivel) {
                case 1:
                    Unidade->vida = 4;
                    Unidade->ataque = 3;
                    Unidade->defesa = 1;
                    Unidade->alcance = 3;
                    Unidade->velocidade = 8;
                    break;
                case 2:
                    Unidade->vida = 7;
                    Unidade->ataque = 5;
                    Unidade->defesa = 2;
                    Unidade->alcance = 2;
                    Unidade->velocidade = 4;
                    break;
                case 3:
                    Unidade->vida = 5;
                    Unidade->ataque = 8;
                    Unidade->defesa = 1;
                    Unidade->alcance = 1;
                    Unidade->velocidade = 6;
                    break;
                }
            break;    
    }
    for (int p = i; p <= (i + Unidade->dim-1); p++) {
        for (int q = j; q <= (j + Unidade->dim-1); q++) {
            if (verifica_espaco(mapa, p, q) == 1)
                mapa[p][q].pUniMovel = Unidade;
            else
                return -1;
        }
    }
    return 0;
}
