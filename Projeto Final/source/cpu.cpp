/**
 * @file cpu.cpp
 *
 * @brief Arquivo com a aplicação da inteligencia artificial da CPU para simular o oponente
 *
 * @author Grupo 2
 *
 */

#include "funcoes.h"
void criacoes_iniciais_1(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void criacoes_iniciais_2(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void criacoes_iniciais_3(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_defesa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_recursos(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_evolucoes(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_tropas(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_movimentacao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_destruicao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_ataque(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);

void CPU(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data mouse,
texto_data texto, player_data *player_CPU, atributos_data atributos, int contador_turno) {
    srand(time(NULL));
    if(contador_turno == 1){
        criacoes_iniciais_1(mapa, atributos, player_CPU);
    }
    else if(contador_turno == 3){
        criacoes_iniciais_2(mapa, atributos, player_CPU);
    }
    else if(contador_turno == 5){
        criacoes_iniciais_3(mapa, atributos, player_CPU);
    }
    else{
        if(player_CPU->vida_base < VIDA_INICIAL_BASE/2)
            priorizar_defesa(mapa, atributos, player_CPU);
        if(player_CPU->vida_base < VIDA_INICIAL_BASE/4)
            priorizar_defesa(mapa, atributos, player_CPU);
        priorizar_recursos(mapa, atributos, player_CPU);
        priorizar_evolucoes(mapa, atributos, player_CPU);
        priorizar_tropas(mapa, atributos, player_CPU);
        priorizar_movimentacao(mapa, atributos, player_CPU);
        priorizar_destruicao(mapa, atributos, player_CPU);
        priorizar_ataque(mapa, atributos, player_CPU);
    }
    mouse.x_mem = -1;
    mouse.y_mem = -1;
    carrega_interface(mapa, imagens, &mouse, texto, player_CPU, atributos);
}

void criacoes_iniciais_1(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU) {
    atributos.classe = GERADOR_DE_RECURSO;
    atributos.divisao = HUMANO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 1, 30, atributos, player_CPU);
    atributos.classe = GERADOR_DE_RECURSO;
    atributos.divisao = MECANICO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 6, 30, atributos, player_CPU);
    atributos.classe = GERADOR_DE_RECURSO;
    atributos.divisao = ELETRICO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 6, 35, atributos, player_CPU);
    atributos.classe = GERADOR_DE_TROPA;
    atributos.divisao = HUMANO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 2, 25, atributos, player_CPU);
    atributos.classe = GERADOR_DE_TROPA;
    atributos.divisao = MECANICO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 9, 26, atributos, player_CPU);
    atributos.classe = GERADOR_DE_TROPA;
    atributos.divisao = ELETRICO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 10, 35, atributos, player_CPU);
}
void criacoes_iniciais_2(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU) {
    
    atributos.classe = DEFESA_OFENSIVA;
    atributos.divisao = HUMANO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 3, 19, atributos, player_CPU);
    atributos.classe = DEFESA_OFENSIVA;
    atributos.divisao = MECANICO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 14, 22, atributos, player_CPU);
    atributos.classe = DEFESA_OFENSIVA;
    atributos.divisao = ELETRICO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 15, 35, atributos, player_CPU);
}

void criacoes_iniciais_3(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, divisao;
    for (divisao = HUMANO; divisao <= ELETRICO; divisao++) {
        atributos.classe = DEFESA_PASSIVA;
        atributos.divisao = divisao;
        atributos.time = INIMIGO;
        count = 3+rand()%2;
        while (count--) {
            do {
                i = rand()%40;
                j = rand()%40;
            } while (i-j > 0 || j+(39-i) > 53 || !verifica_espaco(mapa, i, j));
            cria_uni_estatico(mapa, i, j, atributos, player_CPU);
        }
    }
}
void priorizar_defesa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, divisao, defesa, k;
    for (defesa = DEFESA_OFENSIVA; defesa <= DEFESA_PASSIVA; defesa++) {
        for (divisao = HUMANO; divisao <= ELETRICO; divisao++) {
            atributos.classe = defesa;
            atributos.divisao = divisao;
            atributos.time = INIMIGO;
            count = 1;
            while (count--) {
                k = 0;
                do {
                    i = rand()%40;
                    j = rand()%40;
                    k++;
                } while ((i-j > 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 15);
                if (k > 15)
                    break;
            }
        }
    }
}

void priorizar_recursos(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, divisao, defesa, k;
    // RECURSOS
    for (divisao = HUMANO; divisao <= ELETRICO; divisao++) {
        atributos.classe = GERADOR_DE_RECURSO;
        atributos.divisao = divisao;
        atributos.time = INIMIGO;
        atributos.nivel = 1;
        count = 0;
        if (divisao == HUMANO && player_CPU->comida < COMIDA_INICIAL/2)
            count = 1;
        if (divisao == MECANICO && player_CPU->minerio < MINERIO_INICIAL/2)
            count = 1;
        if (divisao == ELETRICO && player_CPU->eletricidade < ELETRICIDADE_INICIAL/2)
            count = 1;
        while (count--) {
            k = 0;
            do {
                i = rand()%40;
                j = rand()%40;
                k++;
            } while ((i-j > 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 15);
            if (k > 15)
                break;
        }
    }
    // DEFESA
    for (defesa = DEFESA_OFENSIVA; defesa <= DEFESA_PASSIVA; defesa++) {
        for (divisao = HUMANO; divisao <= ELETRICO; divisao++) {
            atributos.classe = defesa;
            atributos.divisao = divisao;
            atributos.time = INIMIGO;
            count = 1;
            while (count--) {
                k = 0;
                do {
                    i = rand()%40;
                    j = rand()%40;
                    k++;
                } while ((i-j > 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 15);
                if (k > 15)
                    break;
            }
        }
    }
}

void priorizar_evolucoes(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, k, pode_evoluir;
    count = 3;
    while (count--) {
        k = 0;
        pode_evoluir = 0;
        do {
            i = rand()%40;
            j = rand()%40;
            if (mapa[i][j].pUniImovel != NULL &&
            mapa[i][j].pUniImovel->time == INIMIGO &&
            mapa[i][j].pUniImovel->nivel < 3) {
                pode_evoluir = 1;
                evolution(mapa[i][j].pUniImovel, player_CPU);
            }
            k++;
        } while (pode_evoluir == 0 && k < 25);
    }
}
void priorizar_tropas(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, k, pode_gerar_tropas;
    mouse_data mouse;
    count = 3;
    while (count--) {
        k = 0;
        pode_gerar_tropas = 0;
        do {
            i = rand()%40;
            j = rand()%40;
            if (mapa[i][j].pUniImovel != NULL &&
            mapa[i][j].pUniImovel->time == INIMIGO &&
            mapa[i][j].pUniImovel->classe == GERADOR_DE_TROPA) {
                pode_gerar_tropas = 1;
                mouse.x = j*LADO;
                mouse.y = i*LADO;
                atributos.time = INIMIGO;
                //gera_tropa(mapa, mouse, atributos, player_CPU);
            }
            k++;
        } while (pode_gerar_tropas == 0 && k < 25);
    }
}
void priorizar_movimentacao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, classe, defesa, k;
}
void priorizar_destruicao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, classe, defesa, k;
}
void priorizar_ataque(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, classe, defesa, k;
}
