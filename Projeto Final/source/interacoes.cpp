/**
 * @file interacoes.cpp
 *
 * @brief Arquivo com a aplicação das funções da interação entre elementos do jogo
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
    printf("Velocidade: %d\n\n", aux->velocidade);

    printf("Status da unidade 2 :\n");
    printf("Divisao: %d\n", aux2->divisao);
    printf("Vida: %d\n", aux2->vida);
    printf("Ataque: %d\n", aux2->ataque);
    printf("Defesa: %d\n", aux2->defesa);
    printf("Alcance: %d\n", aux2->alcance);
    printf("Velocidade: %d\n\n", aux2->velocidade);

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
    printf("Ataque: %d\n\n", ataque);

    if( aux->nivel == 2){

    aux2->vida = aux2->vida - ataque;	

    }else{

	if(aux2->defesa < ataque){
	aux2->vida = aux2->vida - (ataque - aux2->defesa);		
    } 

    }
  
    if(aux2->vida <= 0){

    mapa[aux2->i][aux2->j].pUniMovel = NULL;

    	printf("Unidade morta\n\n");
    	player->xp = player->xp + (aux2->nivel)*2;
        player_level(player);

    	if(aux->divisao == HUMANO && aux->nivel == 1){
    		player->comida = player->comida + (aux2->nivel)*2;
    	}
        if(aux->divisao == MECANICO && aux->nivel == 1){
            player->minerio = player->minerio + (aux2->nivel)*2;
        }
        if(aux->divisao == ELETRICO && aux->nivel == 1){
            player->eletricidade = player->eletricidade + (aux2->nivel)*2;
        }

    	printf("XP do player:%d\n", player->xp);
        printf("nivel do player: %d\n", player->nivel);

    } else{
    	printf("Nova vida do defensor: %d\n\n", aux2->vida);
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
    printf("Velocidade: %d\n\n", aux->velocidade);

    printf("Status da unidade 2 :\n");
    printf("Divisao: %d\n", aux2->divisao);
    printf("Vida: %d\n", aux2->vida);
    printf("Ataque: %d\n", aux2->ataque);
    printf("Defesa: %d\n", aux2->defesa);
    printf("Alcance: %d\n", aux2->alcance);
    printf("Classe: %d\n", aux2->classe);
    printf("Dim: %d\n\n", aux2->dim);

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
    printf("Ataque Total: %d\n", ataque);

    if(aux->divisao == HUMANO && aux->nivel == 2){

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
        player_level(player);
        printf("nivel do player: %d\n", player->nivel);

    	printf("XP do player:%d\n", player->xp);

    } else{
    	printf("Nova vida da construção: %d\n", aux2->vida);

    }
    
    return 0;
 }

void Atualizar_recursos(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], player_data *player){

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pUniImovel != NULL &&  mapa[i][j].pUniImovel->classe == GERADOR_DE_RECURSO) {
            if (mapa[i][j].pUniImovel->i == i && mapa[i][j].pUniImovel->j == j){
               if(mapa[i][j].pUniImovel->divisao == HUMANO){

                printf("comida do jogador: %d\n", player->comida);
                printf("produção: %d\n", mapa[i][j].pUniImovel->producao);
                printf("nivel da unidade de produção: %d\n", mapa[i][j].pUniImovel->nivel);
                player->comida = player->comida + (mapa[i][j].pUniImovel->producao*mapa[i][j].pUniImovel->nivel);
                printf("comida do jogador após produção: %d\n\n", player->comida);

               }
               if(mapa[i][j].pUniImovel->divisao == MECANICO){

                printf("minerio do jogador: %d\n", player->minerio);
                printf("produção: %d\n", mapa[i][j].pUniImovel->producao);
                printf("nivel da unidade de produção: %d\n", mapa[i][j].pUniImovel->nivel);
                player->minerio = player->minerio + (mapa[i][j].pUniImovel->producao*mapa[i][j].pUniImovel->nivel);
                printf("minerio do jogador após produção: %d\n\n", player->minerio);

               }
               if(mapa[i][j].pUniImovel->divisao == ELETRICO){

                printf("eletricidade do jogador: %d\n", player->eletricidade);
                printf("produção: %d\n", mapa[i][j].pUniImovel->producao);
                printf("nivel da unidade de produção: %d\n", mapa[i][j].pUniImovel->nivel);
                player->eletricidade = player->eletricidade + (mapa[i][j].pUniImovel->producao*mapa[i][j].pUniImovel->nivel);
                printf("eletricidade do jogador após produção: %d\n\n\n", player->eletricidade);

               }
        }
    }
}
}
}

int player_level(player_data *player){

int level_up = 50;

if(player->xp >= level_up && player->nivel == 1){

    player->nivel = 2;
    player->xp = 0;

} else if(player->xp >= level_up && player->nivel == 2){

    player->nivel = 3;
    player->xp = 0;
}
} 

int evolution(unidade_estatica *aux, player_data *player){

if(aux->nivel == 3){
    printf("Nivel Máximo alcançado\n\n");
    return 0;
}

if(player->comida < (aux->custo_comida*3) ||
        player->minerio < (aux->custo_minerio*3) ||
        player->eletricidade < (aux->custo_eletricidade*3)){
        printf("Quantidade de recursos insuficientes\n\n");
    return 0;
    }

aux->nivel = aux->nivel + 1;
aux->vida = aux->vida + 10;    

printf("Construção Aprimorada com sucesso\n\n");

}

