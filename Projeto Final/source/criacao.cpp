/**
 * @file criacao.cpp
 *
 * @brief Arquivo com as funções relacionadas à criação de elementos do jogo
 *
 * @author Grupo 2
 *
 */


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

void cria_player(player_data *player, int time) {
    player->time = time;
    player->comida = COMIDA_INICIAL;
    player->minerio = MINERIO_INICIAL;
    player->eletricidade = ELETRICIDADE_INICIAL;
    player->xp = 0;
    player->nivel = 1;
    player->vida_base = VIDA_INICIAL_BASE;
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
            if (!verifica_espaco(mapa, p, q))
                return -1;
        }
    }
    for (int p = i; p <= (i + dim-1); p++) {
        for (int q = j; q <= (j + dim-1); q++) {
            mapa[p][q].pBase = Base;
        }
    }
    return 0;
}

int cria_uni_estatico(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, atributos_data atributos, player_data *player) {
    unidade_estatica *Unidade = (unidade_estatica*)malloc(sizeof(unidade_estatica));
    Unidade->i = i;
    Unidade->j = j; 
    Unidade->time = atributos.time;
    Unidade->classe = atributos.classe;
    Unidade->divisao = atributos.divisao;
    Unidade->nivel = atributos.nivel;
    Unidade->acao = true;

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
            Unidade->custo_minerio = 2;
            Unidade->custo_comida = 3;
            Unidade->custo_eletricidade = 1;
            Unidade->producao = 5;
            break;

        case GERADOR_DE_TROPA:
            Unidade->dim = 3;
            Unidade->vida = 10;
            Unidade->ataque = 0;
            Unidade->defesa = 5;
            Unidade->alcance = 0;
            Unidade->custo_minerio = 2;
            Unidade->custo_comida = 3;
            Unidade->custo_eletricidade = 1;
            Unidade->producao = 0;
            break;

        case DEFESA_OFENSIVA:
            Unidade->dim = 2;
            Unidade->vida = 10;
            Unidade->ataque = 3;
            Unidade->defesa = 5;
            Unidade->alcance = 2;
            Unidade->custo_minerio = 2;
            Unidade->custo_comida = 3;
            Unidade->custo_eletricidade = 1;
            Unidade->producao = 0;
            break;

        case DEFESA_PASSIVA:
            Unidade->dim = 1;
            Unidade->vida = 10;
            Unidade->ataque = 0;
            Unidade->defesa = 5;
            Unidade->alcance = 0;
            Unidade->custo_minerio = 2;
            Unidade->custo_comida = 3;
            Unidade->custo_eletricidade = 1;
            Unidade->producao = 0;
            break;
    }

    if(player->comida < Unidade->custo_comida ||
        player->minerio < Unidade->custo_minerio ||
        player->eletricidade < Unidade->custo_eletricidade){
        printf("Quantidade de recursos insuficientes\n");
        return 0;
    }

    player->comida = player->comida - Unidade->custo_comida;
    player->minerio = player->minerio - Unidade->custo_minerio;
    player->eletricidade = player->eletricidade - Unidade->custo_eletricidade;


    for (int p = i; p <= (i + Unidade->dim-1); p++) {
        for (int q = j; q <= (j + Unidade->dim-1); q++) {
            if (!verifica_espaco(mapa, p, q))
                return -1;
        }
    }
    for (int p = i; p <= (i + Unidade->dim-1); p++) {
        for (int q = j; q <= (j + Unidade->dim-1); q++) {
            mapa[p][q].pUniImovel = Unidade;
        }
    }
    return 0;
}

int cria_uni_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, atributos_data atributos, player_data *player) {
    unidade_movel *Unidade = (unidade_movel*)malloc(sizeof(unidade_movel));
    Unidade->i = i;
    Unidade->j = j; 
    Unidade->time = atributos.time;
    Unidade->divisao = atributos.divisao;
    Unidade->nivel = atributos.nivel;
    Unidade->dim = 1;
    Unidade->acao = true;

    switch (Unidade->divisao) {

        case HUMANO:
            switch (Unidade->nivel) {

                case 1:
                    Unidade->vida = 3;
                    Unidade->ataque = 5;
                    Unidade->defesa = 1;
                    Unidade->alcance = 4;
                    Unidade->velocidade = 5;
                    Unidade->custo_minerio = 2;
                    Unidade->custo_comida = 3;
                    Unidade->custo_eletricidade = 1;
                    break;

                case 2:
                    Unidade->vida = 5;
                    Unidade->ataque = 6;
                    Unidade->defesa = 2;
                    Unidade->alcance = 1;
                    Unidade->velocidade = 6;
                    Unidade->custo_minerio = 2;
                    Unidade->custo_comida = 3;
                    Unidade->custo_eletricidade = 1;
                    break;

                case 3:
                    Unidade->vida = 6;
                    Unidade->ataque = 6;
                    Unidade->defesa = 1;
                    Unidade->alcance = 1;
                    Unidade->velocidade = 10;
                    Unidade->custo_minerio = 2;
                    Unidade->custo_comida = 3;
                    Unidade->custo_eletricidade = 1;
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
                    Unidade->custo_minerio = 2;
                    Unidade->custo_comida = 3;
                    Unidade->custo_eletricidade = 1;
                    break;

                case 2:
                    Unidade->vida = 4;
                    Unidade->ataque = 4;
                    Unidade->defesa = 1;
                    Unidade->alcance = 1;
                    Unidade->velocidade = 5;
                    Unidade->custo_minerio = 2;
                    Unidade->custo_comida = 3;
                    Unidade->custo_eletricidade = 1;
                    break;

                case 3:
                    Unidade->vida = 10;
                    Unidade->ataque = 10;
                    Unidade->defesa = 3;
                    Unidade->alcance = 2;
                    Unidade->velocidade = 3;
                    Unidade->custo_minerio = 2;
                    Unidade->custo_comida = 3;
                    Unidade->custo_eletricidade = 1;
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
                    Unidade->custo_minerio = 2;
                    Unidade->custo_comida = 3;
                    Unidade->custo_eletricidade = 1;
                    break;

                case 2:
                    Unidade->vida = 7;
                    Unidade->ataque = 5;
                    Unidade->defesa = 2;
                    Unidade->alcance = 2;
                    Unidade->velocidade = 4;
                    Unidade->custo_minerio = 2;
                    Unidade->custo_comida = 3;
                    Unidade->custo_eletricidade = 1;
                    break;

                case 3:
                    Unidade->vida = 5;
                    Unidade->ataque = 8;
                    Unidade->defesa = 1;
                    Unidade->alcance = 1;
                    Unidade->velocidade = 6;
                    Unidade->custo_minerio = 2;
                    Unidade->custo_comida = 3;
                    Unidade->custo_eletricidade = 1;
                    break;
                }
                break;

        case OPERARIO:
            Unidade->vida = 5;
            Unidade->ataque = 0;
            Unidade->defesa = 0;
            Unidade->alcance = 0;
            Unidade->velocidade = 10;
            Unidade->custo_minerio = 0;
            Unidade->custo_comida = 0;
            Unidade->custo_eletricidade = 0;
            break;  
    }

    if(player->comida < Unidade->custo_comida ||
        player->minerio < Unidade->custo_minerio ||
        player->eletricidade < Unidade->custo_eletricidade){
        printf("Quantidade de recursos insuficientes\n");
        return 0;
    }

    player->comida = player->comida - Unidade->custo_comida;
    player->minerio = player->minerio - Unidade->custo_minerio;
    player->eletricidade = player->eletricidade - Unidade->custo_eletricidade;


    for (int p = i; p <= (i + Unidade->dim-1); p++) {
        for (int q = j; q <= (j + Unidade->dim-1); q++) {
            if (!verifica_espaco(mapa, p, q))
                return -1;
        }
    }
    for (int p = i; p <= (i + Unidade->dim-1); p++) {
        for (int q = j; q <= (j + Unidade->dim-1); q++) {
            mapa[p][q].pUniMovel = Unidade;
        }
    }
    return 0;
}

int construction(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, int cell_i, int cell_j, unidade_movel* unit, player_data *player){
    char optionSN;
    int option; 

    printf("Deseja construir algo?(S/N)\n");
    scanf("%c", &optionSN);
    getchar();

    if( optionSN == 'N' || optionSN == 'n'){
        return 0;
    }
    if( optionSN != 'S' && optionSN != 's'){
        printf("caractere invalido\n");
        return 0;
    }

    printf("O que deseja construir?\n"); 
    printf("1 - GERADOR_DE_RECURSO\n");
    printf("2 - GERADOR DE TROPA\n");
    printf("3 - DEFESA OFENSIVA\n");
    printf("4 - DEFESA_PASSIVA\n");
    printf("5 - CANCELAR\n");
    scanf("%d", &option);
    getchar();

    switch (option) {
        case 1:
            atributos.classe = GERADOR_DE_RECURSO;
            break;

        case 2:
            atributos.classe = GERADOR_DE_TROPA;
            break;

        case 3:
            atributos.classe = DEFESA_OFENSIVA;
            break;

        case 4:
            atributos.classe = DEFESA_PASSIVA;
            break;

        default:
            return 0;
    }

    cria_uni_estatico(mapa, cell_i, cell_j, atributos, player);
    optionSN = 'N';
//    move_unidade(mapa, unit, cell_i+3, cell_j+3);
  
    return 0;
}
