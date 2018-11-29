/**
 * @file interacoes.cpp
 *
 * @brief Arquivo com a aplicação das funções de interação do jogo
 *
 * @author Grupo 2
 *
 */

#include "funcoes.h"

int move_unidade (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* unit, int i, int j) {
	cell_mapa* anterior = &mapa[unit->i][unit->j];
	unit->i = i;
	unit->j = j;
	anterior->pUniMovel = NULL;
	mapa[i][j].pUniMovel = unit;
	return 0;
}

int combate(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, unidade_movel *aux2, player_data *player){
 	
 	printf("Status da unidade 1:\n");
 	printf("Divisao: %d\n", aux->divisao);
    printf("Vida: %d\n", aux->vida);
    printf("Ataque: %d\n", aux->ataque);
    printf("Defesa: %d\n", aux->defesa);
    printf("Alcance: %d\n", aux->alcance);
    printf("Velocidade: %d\n", aux->velocidade);

    printf("Status da unidade 2 :\n");
    printf("Divisao: %d\n", aux2->divisao);
    printf("Vida: %d\n", aux2->vida);
    printf("Ataque: %d\n", aux2->ataque);
    printf("Defesa: %d\n", aux2->defesa);
    printf("Alcance: %d\n", aux2->alcance);
    printf("Velocidade: %d\n", aux2->velocidade);

    int ataque = aux->ataque;
    if((aux->divisao == HUMANO && aux2->divisao == MECANICO)
    	|| (aux->divisao == MECANICO && aux2->divisao == ELETRICO)
    	|| (aux->divisao == ELETRICO && aux2->divisao == HUMANO)){
    	ataque = aux->ataque + 2;
    }else if((aux->divisao == MECANICO && aux2->divisao == HUMANO)
    	|| (aux->divisao == ELETRICO && aux2->divisao == MECANICO)
    	|| (aux->divisao == HUMANO && aux2->divisao == ELETRICO)){
    	ataque = aux->ataque - 2;
    }
    printf("Ataque: %d\n", ataque);

    if(aux->divisao == 1 && aux->nivel == 2){

    aux2->vida = aux2->vida - ataque;	

    }else{

	if(aux2->defesa < ataque){
	aux2->vida = aux2->vida - (ataque - aux2->defesa);		
    } 

    }
  
    if(aux2->vida <= 0){

    mapa[aux2->i][aux2->j].pUniMovel = NULL;

    	printf("Unidade morta\n");
    	player->xp = player->xp + (aux2->nivel)*2;

    	if(aux->divisao == 1 && aux->nivel == 1){
    		player->minerio = player->minerio + (aux2->nivel)*2;
    	}

    	printf("Minerios do player:%d\n", player->minerio);
    	printf("XP do player:%d\n", player->xp);

    } else{
    	printf("Nova vida do defensor: %d\n", aux2->vida);
    }
    
    return 0;
 }

int destruicao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, unidade_estatica *aux2, player_data *player){
 	
 	printf("Status da unidade 1:\n");
 	printf("Divisao: %d\n", aux->divisao);
    printf("Vida: %d\n", aux->vida);
    printf("Ataque: %d\n", aux->ataque);
    printf("Defesa: %d\n", aux->defesa);
    printf("Alcance: %d\n", aux->alcance);
    printf("Velocidade: %d\n", aux->velocidade);

    printf("Status da unidade 2 :\n");
    printf("Divisao: %d\n", aux2->divisao);
    printf("Vida: %d\n", aux2->vida);
    printf("Ataque: %d\n", aux2->ataque);
    printf("Defesa: %d\n", aux2->defesa);
    printf("Alcance: %d\n", aux2->alcance);
    printf("Classe: %d\n", aux2->classe);
    printf("Dim: %d\n", aux2->dim);

    int ataque = aux->ataque;
    if((aux->divisao == HUMANO && aux2->divisao == MECANICO)
    	|| (aux->divisao == MECANICO && aux2->divisao == ELETRICO)
    	|| (aux->divisao == ELETRICO && aux2->divisao == HUMANO)){
    	ataque = aux->ataque + 2;
    }else if((aux->divisao == MECANICO && aux2->divisao == HUMANO)
    	|| (aux->divisao == ELETRICO && aux2->divisao == MECANICO)
    	|| (aux->divisao == HUMANO && aux2->divisao == ELETRICO)){
    	ataque = aux->ataque - 2;
    }
    printf("Ataque: %d\n", ataque);

    if(aux->divisao == 1 && aux->nivel == 2){

    aux2->vida = aux2->vida - ataque;	

    }else{

    if(aux2->defesa < ataque){
	aux2->vida = aux2->vida - (ataque - aux2->defesa);		
    } 

    }
  
    if(aux2->vida <= 0){


    	for (int p = aux2->j; p < (aux2->i + aux2->dim); p++) {
        for (int q = aux2->j; q < (aux2->j + aux2->dim); q++) {
            mapa[p][q].pUniImovel = NULL;
        }
    	}

    	mapa[aux2->i][aux2->j].pUniImovel = NULL;
    	mapa[aux2->i][aux2->j+1].pUniImovel = NULL;



    	printf("Construção destruida\n");
    	player->xp = player->xp + (aux2->classe)*2;

    	printf("Minerios do player:%d\n", player->minerio);
    	printf("XP do player:%d\n", player->xp);

    } else{
    	printf("Nova vida da construção: %d\n", aux2->vida);

    }
    
    return 0;
 }
