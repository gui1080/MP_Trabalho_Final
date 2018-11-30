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
        // 1_Funcoes de Prioridades:
        // 2_Acoes de acordo com prioridade e recuros:
        mouse.x_mem = 0;
        mouse.y_mem = 0;
        carrega_interface(mapa, imagens, mouse, texto, player_CPU, atributos);
    }
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
    int count = 3+rand()%2;
    int i, j;
    atributos.classe = DEFESA_PASSIVA;
    atributos.divisao = HUMANO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    while(count--) {
    	do {
    	i = rand()%40;
    	j = rand()%40;
    	} while(i-j > 0 || j+(39-i) > 53 || !verifica_espaco(mapa, i, j));
    	cria_uni_estatico(mapa, i, j, atributos, player_CPU);
    }
    atributos.classe = DEFESA_PASSIVA;
    atributos.divisao = MECANICO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    count = 3+rand()%2;
    printf("%d\n", count);
    while(count--) {
    	do {
    	i = rand()%40;
    	j = rand()%40;
    	} while(i-j > 0 || j+(39-i) > 53 || !verifica_espaco(mapa, i, j));
    	cria_uni_estatico(mapa, i, j, atributos, player_CPU);
    }
    atributos.classe = DEFESA_PASSIVA;
    atributos.divisao = ELETRICO;
    atributos.time = INIMIGO;
    atributos.nivel = 1;
    count = 3+rand()%2;
    printf("%d\n", count);

    while(count--) {
    	do {
    	i = rand()%40;
    	j = rand()%40;
    	} while(i-j > 0 || j+(39-i) > 53 || !verifica_espaco(mapa, i, j));
    	cria_uni_estatico(mapa, i, j, atributos, player_CPU);
    }
}