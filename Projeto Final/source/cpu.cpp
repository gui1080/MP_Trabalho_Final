/**
 * @file cpu.cpp
 *
 * @brief Arquivo com a aplicação da inteligencia artificial da CPU para simular o oponente
 *
 * @author Grupo 2
 *
 */

#include "funcoes.h"
bool verificador_CPU (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j);
void criacoes_iniciais_1(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void criacoes_iniciais_2(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void criacoes_iniciais_3(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_defesa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_geradores(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_evolucoes(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_tropas(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_movimentacao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_destruicao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_combate(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_destruicao_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);
void priorizar_contra_ataque(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU);


int CPU(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],player_data *player_CPU,int contador_turno) {
    atributos_data atributos;
    struct timeval time; 
    gettimeofday(&time,NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000)); 
    if(contador_turno/2 == 0){
        criacoes_iniciais_1(mapa, atributos, player_CPU);
    }
    else if(contador_turno/2 == 1){
        criacoes_iniciais_2(mapa, atributos, player_CPU);
    }
    else if(contador_turno/2 == 2){
        criacoes_iniciais_3(mapa, atributos, player_CPU);
    }
    else if(contador_turno/2 == 3) {
        usleep(10000);
        priorizar_geradores(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_evolucoes(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_tropas(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_movimentacao(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_destruicao(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_combate(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_destruicao_base(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_contra_ataque(mapa, atributos, player_CPU);
        usleep(10000);
    }
    else{
        usleep(10000);
        if(player_CPU->vida_base < VIDA_INICIAL_BASE/2)
            priorizar_defesa(mapa, atributos, player_CPU);
        if(player_CPU->vida_base < VIDA_INICIAL_BASE/4)
            priorizar_defesa(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_evolucoes(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_tropas(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_movimentacao(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_destruicao(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_combate(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_destruicao_base(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_contra_ataque(mapa, atributos, player_CPU);
        usleep(10000);
        priorizar_geradores(mapa, atributos, player_CPU);
    }
    return 0;
}

void criacoes_iniciais_1(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU) {
    atributos.classe = GERADOR_DE_RECURSO;
    atributos.divisao = HUMANO;
    atributos.time = player_CPU->time;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 1, 30, atributos, player_CPU);
    if(player_CPU->time == ALIADO)
        cria_uni_estatico(mapa, 30, 1, atributos, player_CPU);
    atributos.classe = GERADOR_DE_RECURSO;
    atributos.divisao = MECANICO;
    atributos.time = player_CPU->time;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 6, 30, atributos, player_CPU);
    if(player_CPU->time == ALIADO)
        cria_uni_estatico(mapa, 30, 6, atributos, player_CPU);
    atributos.classe = GERADOR_DE_RECURSO;
    atributos.divisao = ELETRICO;
    atributos.time = player_CPU->time;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 6, 35, atributos, player_CPU);
    if(player_CPU->time == ALIADO)
        cria_uni_estatico(mapa, 35, 6, atributos, player_CPU);
    atributos.classe = GERADOR_DE_TROPA;
    atributos.divisao = HUMANO;
    atributos.time = player_CPU->time;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 2, 25, atributos, player_CPU);
    if(player_CPU->time == ALIADO)
        cria_uni_estatico(mapa, 25, 2, atributos, player_CPU);
    atributos.classe = GERADOR_DE_TROPA;
    atributos.divisao = MECANICO;
    atributos.time = player_CPU->time;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 9, 26, atributos, player_CPU);
    if(player_CPU->time == ALIADO)
        cria_uni_estatico(mapa, 26, 9, atributos, player_CPU);
    atributos.classe = GERADOR_DE_TROPA;
    atributos.divisao = ELETRICO;
    atributos.time = player_CPU->time;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 10, 35, atributos, player_CPU);
    if(player_CPU->time == ALIADO)
        cria_uni_estatico(mapa, 35, 10, atributos, player_CPU);
}
void criacoes_iniciais_2(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU) {
    
    atributos.classe = DEFESA_OFENSIVA;
    atributos.divisao = HUMANO;
    atributos.time = player_CPU->time;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 3, 19, atributos, player_CPU);
    if(player_CPU->time == ALIADO)
        cria_uni_estatico(mapa, 19, 3, atributos, player_CPU);
    atributos.classe = DEFESA_OFENSIVA;
    atributos.divisao = MECANICO;
    atributos.time = player_CPU->time;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 14, 22, atributos, player_CPU);
    if(player_CPU->time == ALIADO)
        cria_uni_estatico(mapa, 22, 14, atributos, player_CPU);
    atributos.classe = DEFESA_OFENSIVA;
    atributos.divisao = ELETRICO;
    atributos.time = player_CPU->time;
    atributos.nivel = 1;
    cria_uni_estatico(mapa, 15, 35, atributos, player_CPU);
    if(player_CPU->time == ALIADO)
        cria_uni_estatico(mapa, 35, 15, atributos, player_CPU);
}

void criacoes_iniciais_3(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, divisao;
    for (divisao = HUMANO; divisao <= ELETRICO; divisao++) {
        atributos.classe = DEFESA_PASSIVA;
        atributos.divisao = divisao;
        atributos.time = player_CPU->time;
        count = 3+rand()%2;
        while (count--) {
            do {
                i = rand()%40;
                j = rand()%40;
            } while (i-j > 0 || j+(39-i) > 53 || !verificador_CPU(mapa, i, j));
            if(player_CPU->time == INIMIGO)
                cria_uni_estatico(mapa, i, j, atributos, player_CPU);
            if(player_CPU->time == ALIADO)  //Desenvolvido para testes
                cria_uni_estatico(mapa, j, i, atributos, player_CPU);
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
            atributos.time = player_CPU->time;
            count = 1;
            if(player_CPU->time == INIMIGO) {
                while (count--) {
                    k = 0;
                    do {
                        i = rand()%40;
                        j = rand()%40;
                        k++;
                    } while ((i-j > 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 15);
                }
            }
            if(player_CPU->time == ALIADO) {  //Desenvolvido para testes
                while (count--) {
                    k = 0;
                    do {
                        i = rand()%40;
                        j = rand()%40;
                        k++;
                    } while ((i-j < 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 15);
                }
            }
        }
    }
}

void priorizar_geradores(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, divisao, defesa, k;
    // RECURSOS
    for (divisao = HUMANO; divisao <= ELETRICO; divisao++) {
        atributos.classe = GERADOR_DE_RECURSO;
        atributos.divisao = divisao;
        atributos.time = player_CPU->time;
        atributos.nivel = 1;
        count = 1;
        if(player_CPU->time == INIMIGO) {
            while (count--) {
                k = 0;
                do {
                    i = rand()%40;
                    j = rand()%40;
                    k++;
                } while ((i-j > 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 15);
            }
        }
        if(player_CPU->time == ALIADO) {
            while (count--) {
                k = 0;
                do {
                    i = rand()%40;
                    j = rand()%40;
                    k++;
                } while ((i-j < 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 15);
            }
        }
    }
    // TROPAS
    for (divisao = HUMANO; divisao <= ELETRICO; divisao++) {
        atributos.classe = GERADOR_DE_TROPA;
        atributos.divisao = divisao;
        atributos.time = player_CPU->time;
        atributos.nivel = 1;
        count = 1;
        if(player_CPU->time == INIMIGO) {
            while (count--) {
                k = 0;
                do {
                    i = rand()%40;
                    j = rand()%40;
                    k++;
                } while ((i-j > 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 15);
            }
        }
        if(player_CPU->time == ALIADO) {
            while (count--) {
                k = 0;
                do {
                    i = rand()%40;
                    j = rand()%40;
                    k++;
                } while ((i-j < 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 15);
            }
        }
    }
    // DEFESA
    for (defesa = DEFESA_OFENSIVA; defesa <= DEFESA_PASSIVA; defesa++) {
        for (divisao = HUMANO; divisao <= ELETRICO; divisao++) {
            atributos.classe = defesa;
            atributos.divisao = divisao;
            atributos.time = player_CPU->time;
            count = rand()%2;
            if(player_CPU->time == INIMIGO) {
                while (count--) {
                    k = 0;
                    do {
                        i = rand()%40;
                        j = rand()%40;
                        k++;
                    } while ((i-j > 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 10);
                }
            }
            if(player_CPU->time == ALIADO) {  //Desenvolvido para testes
                while (count--) {
                    k = 0;
                    do {
                        i = rand()%40;
                        j = rand()%40;
                        k++;
                    } while ((i-j < 0 || !cria_uni_estatico(mapa, i, j, atributos, player_CPU)) && k < 10);
                }
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
            mapa[i][j].pUniImovel->time == player_CPU->time &&
            mapa[i][j].pUniImovel->nivel < 3) {
                pode_evoluir = 1;
                evolution(mapa[i][j].pUniImovel, player_CPU);
            }
            k++;
        } while (pode_evoluir == 0 && k < 800);
    }
}
void priorizar_tropas(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, k;
    bool pode_gerar_tropas;
    mouse_data mouse;
    count = 3;
    while (count--) {
        k = 0;
        pode_gerar_tropas = false;
        do {
            i = rand()%40;
            j = rand()%40;
            if (mapa[i][j].pUniImovel != NULL &&
            mapa[i][j].pUniImovel->time == player_CPU->time &&
            mapa[i][j].pUniImovel->classe == GERADOR_DE_TROPA) {
                pode_gerar_tropas = true;
                mouse.y_mem = i*LADO;
                mouse.x_mem = j*LADO;
                atributos.time = player_CPU->time;
                atributos.nivel = 1+rand()%mapa[i][j].pUniImovel->nivel;
                atributos.divisao = mapa[i][j].pUniImovel->divisao;
                gera_tropa(mapa, &mouse, atributos, player_CPU);
            }
            k++;
        } while (pode_gerar_tropas == false && k < 1600);
    }
}
void priorizar_movimentacao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    int count;
    int i, j, k, new_i, new_j;
    bool pode_mover;
    count = 10;
    while (count--) {
        k = 0;
        pode_mover = false;
        do {
            i = rand()%40;
            j = rand()%40;
            if (mapa[i][j].pUniMovel != NULL &&
            mapa[i][j].pUniMovel->time == player_CPU->time) {
                pode_mover = true;
                new_i = i+rand()%mapa[i][j].pUniMovel->velocidade;
                new_j = j-rand()%mapa[i][j].pUniMovel->velocidade;
                if(player_CPU->time == ALIADO) {
                    new_i = i-rand()%mapa[i][j].pUniMovel->velocidade;
                    new_j = j+rand()%mapa[i][j].pUniMovel->velocidade;
                }
                if(verificador_CPU(mapa, new_i, new_j))
                    move_unidade(mapa, mapa[i][j].pUniMovel, new_i, new_j);
                else
                    pode_mover = false;
            }
            k++;
        } while (pode_mover == false && k < 800);
    }
}
void priorizar_destruicao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    bool loop;
    int count;
    int i, j, alcance, k, p, q;
    count = 5;
    while (count--) {
        k = 0;
        do {
            i = rand()%40;
            j = rand()%40;
            loop = true;
            if (mapa[i][j].pUniMovel != NULL &&
            mapa[i][j].pUniMovel->time == player_CPU->time) {
                alcance = mapa[i][j].pUniMovel->alcance;
                for (p = i - alcance; p <= i + alcance && loop == true; p++) {
                    for (q = j - alcance; q<= j + alcance && loop == true; q++) {
                        if(p >= 0 && p < BLOCOS_LINHA && q >= 0 && q < BLOCOS_LINHA) {
                            if (mapa[p][q].pUniImovel != NULL &&
                            mapa[p][q].pUniImovel->time != player_CPU->time) {
                                destruicao(mapa, mapa[i][j].pUniMovel, mapa[p][q].pUniImovel, player_CPU);
                                loop = false;
                            }
                        }
                    }
                }

            }
            k++;
        } while (k < 800 && loop == true);
    }
}

void priorizar_combate(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    bool loop;
    int count;
    int i, j, alcance, k, p, q;
    count = 5;
    while (count--) {
        k = 0;
        do {
            i = rand()%40;
            j = rand()%40;
            loop = true;
            if (mapa[i][j].pUniMovel != NULL &&
            mapa[i][j].pUniMovel->time == player_CPU->time) {
                alcance = mapa[i][j].pUniMovel->alcance;
                for (p = i - alcance; p <= i + alcance && loop == true; p++) {
                    for (q = j - alcance; q<= j + alcance && loop == true; q++) {
                        if(p >= 0 && p < BLOCOS_LINHA && q >= 0 && q < BLOCOS_LINHA) {
                            if (mapa[p][q].pUniMovel != NULL &&
                            mapa[p][q].pUniMovel->time != player_CPU->time) {
                                combate(mapa, mapa[i][j].pUniMovel, mapa[p][q].pUniMovel, player_CPU);
                                loop = false;
                            }
                        }
                    }
                }
            }
            k++;
        } while (k < 1600 && loop == true);
    }
}

void priorizar_destruicao_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
atributos_data atributos, player_data *player_CPU) {
    bool loop;
    int count;
    int i, j, alcance, k, p, q;
    count = 5;
    while (count--) {
        k = 0;
        do {
            i = 20+rand()%20;
            j = rand()%20;
            if(player_CPU->time == ALIADO) {
                i = rand()%20;
                j = 20+rand()%20;
            }
            loop = true;
            if (mapa[i][j].pUniMovel != NULL &&
            mapa[i][j].pUniMovel->time == player_CPU->time) {
                alcance = mapa[i][j].pUniMovel->alcance;
                for (p = i - alcance; p <= i + alcance && loop == true; p++) {
                    for (q = j - alcance; q<= j + alcance && loop == true; q++) {
                        if(p >= 0 && p < BLOCOS_LINHA && q >= 0 && q < BLOCOS_LINHA) {
                            if (mapa[p][q].pBase != NULL &&
                            mapa[p][q].pBase->time != player_CPU->time) {
                                destruicao_base(mapa, mapa[i][j].pUniMovel, mapa[p][q].pBase, player_CPU);
                                loop = false;
                            }
                        }
                    }
                }
            }
            k++;
        } while (k < 800 && loop == true);
    }
}

void priorizar_contra_ataque(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player_CPU) {
    bool loop;
    int count;
    int i, j, alcance, k, p, q;
    count = 5;
    while (count--) {
        k = 0;
        do {
            i = rand()%40;
            j = rand()%40;
            loop = true;
            if (mapa[i][j].pUniImovel != NULL &&
            mapa[i][j].pUniImovel->time == player_CPU->time &&
            mapa[i][j].pUniImovel->classe == DEFESA_OFENSIVA) {
                alcance = mapa[i][j].pUniImovel->alcance;
                for (p = i - alcance; p <= i + alcance && loop == true; p++) {
                    for (q = j - alcance; q<= j + alcance && loop == true; q++) {
                        if(p >= 0 && p < BLOCOS_LINHA && q >= 0 && q < BLOCOS_LINHA) {
                            if (mapa[p][q].pUniMovel != NULL &&
                            mapa[p][q].pUniMovel->time != player_CPU->time) {
                                combate_defensivo(mapa, mapa[i][j].pUniImovel, mapa[p][q].pUniMovel, player_CPU);
                                loop = false;
                            }
                            if (mapa[p][q].pUniImovel != NULL &&
                            mapa[p][q].pUniImovel->time != player_CPU->time) {
                                destruicao_defensiva(mapa, mapa[i][j].pUniImovel, mapa[p][q].pUniImovel, player_CPU);
                                loop = false;
                            }
                        }
                    }
                }
            }
            k++;
        } while (k < 800 && loop == true);
    }
}

bool verificador_CPU (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j) {
    if (i >= 0 && i < BLOCOS_LINHA && j >= 0 && j < BLOCOS_LINHA &&
            mapa[i][j].pUniMovel == NULL &&
            mapa[i][j].pUniImovel == NULL &&
            mapa[i][j].pBase == NULL)
        return true;
    else
        return false;
}
