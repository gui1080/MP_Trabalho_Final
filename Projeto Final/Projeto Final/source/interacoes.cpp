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
	if (unit -> acao == true) {
        cell_mapa* anterior = &mapa[unit->i][unit->j];
    	unit->i = i;
    	unit->j = j;
    	anterior->pUniMovel = NULL;
    	mapa[i][j].pUniMovel = unit;
        unit -> acao = false;
    }
	return 0;
}

int combate(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, unidade_movel *aux2, player_data *player){
 	
    if(aux->cont_ataque == false){
        printf("Essa unidade já atacou esse turno\n");
        return 0;
    }


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
    if ((aux->divisao == HUMANO && aux2->divisao == MECANICO)
    	|| (aux->divisao == MECANICO && aux2->divisao == ELETRICO)
    	|| (aux->divisao == ELETRICO && aux2->divisao == HUMANO)) {

    	ataque = aux->ataque + 2;

    } else if ((aux->divisao == MECANICO && aux2->divisao == HUMANO)
    	|| (aux->divisao == ELETRICO && aux2->divisao == MECANICO)
    	|| (aux->divisao == HUMANO && aux2->divisao == ELETRICO)) {

    	ataque = aux->ataque - 2;
    }

    printf("Ataque: %d\n\n", ataque);

    if (aux->nivel == 2){

        aux2->vida = aux2->vida - ataque;	

    } else if (aux2->defesa < ataque) {
	   aux2->vida = aux2->vida - (ataque - aux2->defesa);		
    }
  
    if(aux2->vida <= 0){

        mapa[aux2->i][aux2->j].pUniMovel = NULL;
    	player->xp = player->xp + (aux2->nivel)*2;
        player_level(player);

        printf("Unidade morta\n\n");

        if (aux->nivel == 1) {
        	if(aux->divisao == HUMANO){
        		player->comida = player->comida + (aux2->nivel)*2;
        	}
            if(aux->divisao == MECANICO){
                player->minerio = player->minerio + (aux2->nivel)*2;
            }
            if(aux->divisao == ELETRICO){
                player->eletricidade = player->eletricidade + (aux2->nivel)*2;
            }
        }

    	printf("XP do player:%d\n", player->xp);
        printf("nivel do player: %d\n", player->nivel);

    } else{
    	printf("Nova vida do defensor: %d\n\n", aux2->vida);
    }
    
    aux->cont_ataque = false;
    return 0;
 }

int combate_defensivo(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_estatica *aux, unidade_movel *aux2, player_data *player){
    
    if(aux->cont_ataque == false){
        printf("Essa unidade já atacou esse turno\n");
        return 0;
    }

    printf("Status da unidade 1:\n");
    printf("Divisao: %d\n", aux->divisao);
    printf("Vida: %d\n", aux->vida);
    printf("Ataque: %d\n", aux->ataque);
    printf("Defesa: %d\n", aux->defesa);
    printf("Alcance: %d\n", aux->alcance);

    printf("Status da unidade 2 :\n");
    printf("Divisao: %d\n", aux2->divisao);
    printf("Vida: %d\n", aux2->vida);
    printf("Ataque: %d\n", aux2->ataque);
    printf("Defesa: %d\n", aux2->defesa);
    printf("Alcance: %d\n", aux2->alcance);
    printf("Velocidade: %d\n\n", aux2->velocidade);

    int ataque = aux->ataque;
    if ((aux->divisao == HUMANO && aux2->divisao == MECANICO)
        || (aux->divisao == MECANICO && aux2->divisao == ELETRICO)
        || (aux->divisao == ELETRICO && aux2->divisao == HUMANO)) {

        ataque = aux->ataque + 2;

    } else if ((aux->divisao == MECANICO && aux2->divisao == HUMANO)
        || (aux->divisao == ELETRICO && aux2->divisao == MECANICO)
        || (aux->divisao == HUMANO && aux2->divisao == ELETRICO)) {

        ataque = aux->ataque - 2;
    }

    printf("Ataque: %d\n\n", ataque);

    if (aux->nivel == 2){

        aux2->vida = aux2->vida - ataque;   

    } else if (aux2->defesa < ataque) {
       aux2->vida = aux2->vida - (ataque - aux2->defesa);       
    }
  
    if(aux2->vida <= 0){

        mapa[aux2->i][aux2->j].pUniMovel = NULL;
        player->xp = player->xp + (aux2->nivel)*2;
        player_level(player);

        printf("Unidade morta\n\n");

        if (aux->nivel == 1) {
            if(aux->divisao == HUMANO){
                player->comida = player->comida + (aux2->nivel)*2;
            }
            if(aux->divisao == MECANICO){
                player->minerio = player->minerio + (aux2->nivel)*2;
            }
            if(aux->divisao == ELETRICO){
                player->eletricidade = player->eletricidade + (aux2->nivel)*2;
            }
        }

        printf("XP do player:%d\n", player->xp);
        printf("nivel do player: %d\n", player->nivel);

    } else{
        printf("Nova vida do defensor: %d\n\n", aux2->vida);
    }
    
    aux->cont_ataque = false;
    return 0;
 }


int destruicao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, unidade_estatica *aux2, player_data *player){

    if(aux->cont_ataque == false){
        printf("Essa unidade já atacou esse turno\n");
        return 0;
    }
 	
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
    	|| (aux->divisao == ELETRICO && aux2->divisao == HUMANO)) {

    	ataque = aux->ataque + 2;

    }else if((aux->divisao == MECANICO && aux2->divisao == HUMANO)
    	|| (aux->divisao == ELETRICO && aux2->divisao == MECANICO)
    	|| (aux->divisao == HUMANO && aux2->divisao == ELETRICO)) {

    	ataque = aux->ataque - 2;
    }
    printf("Ataque Total: %d\n", ataque);

    if (aux->divisao == HUMANO && aux->nivel == 2) {

        aux2->vida = aux2->vida - ataque;	

    } else if (aux2->defesa < ataque) {
	   aux2->vida = aux2->vida - (ataque - aux2->defesa);		
    }
  
    if (aux2->vida <= 0) {


    	for (int p = aux2->i; p < (aux2->i + aux2->dim); p++) {
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
    aux->cont_ataque = false;
    return 0;
 }

 int destruicao_defensiva(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_estatica *aux, unidade_estatica *aux2, player_data *player){

    if(aux->cont_ataque == false){
        printf("Essa unidade já atacou esse turno\n");
        return 0;
    }

    printf("Status da unidade 1:\n");
    printf("Divisao: %d\n", aux->divisao);
    printf("Vida: %d\n", aux->vida);
    printf("Ataque: %d\n", aux->ataque);
    printf("Defesa: %d\n", aux->defesa);
    printf("Alcance: %d\n", aux->alcance);

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
        || (aux->divisao == ELETRICO && aux2->divisao == HUMANO)) {

        ataque = aux->ataque + 2;

    }else if((aux->divisao == MECANICO && aux2->divisao == HUMANO)
        || (aux->divisao == ELETRICO && aux2->divisao == MECANICO)
        || (aux->divisao == HUMANO && aux2->divisao == ELETRICO)) {

        ataque = aux->ataque - 2;
    }
    printf("Ataque Total: %d\n", ataque);

    if (aux->divisao == HUMANO && aux->nivel == 2) {

        aux2->vida = aux2->vida - ataque;   

    } else if (aux2->defesa < ataque) {
       aux2->vida = aux2->vida - (ataque - aux2->defesa);       
    }
  
    if (aux2->vida <= 0) {


        for (int p = aux2->i; p < (aux2->i + aux2->dim); p++) {
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
    aux->cont_ataque = false;
    return 0;
 }


int destruicao_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, base_principal *aux2, player_data *player){
    
    printf("Status da unidade 1:\n");
    printf("Divisao: %d\n", aux->divisao);
    printf("Vida: %d\n", aux->vida);
    printf("Ataque: %d\n", aux->ataque);
    printf("Defesa: %d\n", aux->defesa);
    printf("Alcance: %d\n", aux->alcance);
    printf("Velocidade: %d\n\n", aux->velocidade);

    printf("Status da unidade 2 %d:\n", aux2->vida);

    int ataque = aux->ataque;
  
    aux2->vida = aux2->vida - ataque;       

    if (aux2->vida <= 0) {

        for (int p = aux2->i; p < (aux2->i + aux2->dim); p++) {
            for (int q = aux2->j; q < (aux2->j + aux2->dim); q++) {
                mapa[p][q].pBase = NULL;
            }
        }

        printf("Base destruida destruida\n");
        if(aux2->time == INIMIGO){
            printf("PARABÉNS, VOCÊ VENCEU\n\n");
        }else{
            printf("DERROTA\n\n");
        }


    } else{
        printf("Nova vida da construção: %d\n", aux2->vida);

    }
    
    return 0;
 }



void Atualizar_recursos(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], player_data *player){

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pUniImovel != NULL &&  mapa[i][j].pUniImovel->classe == GERADOR_DE_RECURSO && mapa[i][j].pUniImovel->time == player->time) {
                if (mapa[i][j].pUniImovel->i == i && mapa[i][j].pUniImovel->j == j){
                   if (mapa[i][j].pUniImovel->divisao == HUMANO) {

                    printf("comida do jogador: %d\n", player->comida);
                    printf("produção: %d\n", mapa[i][j].pUniImovel->producao);
                    printf("nivel da unidade de produção: %d\n", mapa[i][j].pUniImovel->nivel);
                    player->comida = player->comida + (mapa[i][j].pUniImovel->producao*mapa[i][j].pUniImovel->nivel);
                    printf("comida do jogador após produção: %d\n\n", player->comida);

                   }
                   if (mapa[i][j].pUniImovel->divisao == MECANICO) {

                    printf("minerio do jogador: %d\n", player->minerio);
                    printf("produção: %d\n", mapa[i][j].pUniImovel->producao);
                    printf("nivel da unidade de produção: %d\n", mapa[i][j].pUniImovel->nivel);
                    player->minerio = player->minerio + (mapa[i][j].pUniImovel->producao*mapa[i][j].pUniImovel->nivel);
                    printf("minerio do jogador após produção: %d\n\n", player->minerio);

                   }
                   if (mapa[i][j].pUniImovel->divisao == ELETRICO) {

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

    if (player->xp >= level_up && player->nivel == 1) {

        player->nivel = 2;
        player->xp = 0;

    } else if (player->xp >= level_up && player->nivel == 2) {

        player->nivel = 3;
        player->xp = 0;
    }
    return 0;
} 

int evolution(unidade_estatica *aux, player_data *player) {

    if(aux->nivel == 3){
        printf("Nivel Máximo alcançado\n\n");
        return 0;
    }

    if (player->comida < (aux->custo_comida*3) ||
        player->minerio < (aux->custo_minerio*3) ||
        player->eletricidade < (aux->custo_eletricidade*3)) {

        printf("Quantidade de recursos insuficientes\n\n");
        return 0;
    }

    if( player->nivel <= aux->nivel ){
        printf("Nivel Insuficiente\n\n");
        return 0;
    }


    aux->nivel = aux->nivel + 1;
    aux->vida = aux->vida + 10;    
    player->comida = player->comida - (aux->custo_comida*3); 
    player->minerio = player->minerio - (aux->custo_minerio*3);
    player->eletricidade = player->eletricidade - (aux->custo_eletricidade*3); 

    printf("Construção Aprimorada com sucesso\n\n");
    return 0;

}

int gera_operario(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data *mouse, atributos_data atributos, player_data *player){
    int x;
    int y;
    int i = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pBase->i;
    int j = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pBase->j;
    int dim = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pBase->dim;
    int aux1 = i - 1;
    int aux2 = j - 1;
    int aux3 = i + (dim + 1);
    int aux4 = j + (dim + 1);
    atributos.divisao = OPERARIO;

    while (1) {
        for(x = aux1; x <  aux3; x++){
            for(y = aux2; y < aux4; y++){
                if(mapa[x][y].pUniImovel == NULL && mapa[x][y].pUniMovel == NULL && mapa[x][y].pBase == NULL ){
                    cria_uni_movel(mapa, x, y, atributos, player);
                    return 0;
                }
            }
        }
        aux1--;
        aux2--;
        aux3++;
        aux4++;
    }      
} 

int gera_tropa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data *mouse, atributos_data atributos, player_data *player){
    int x;
    int y;
    int i = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel->i;
    int j = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel->j;
    int dim = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel->dim;
    int aux1 = i - 1;
    int aux2 = j - 1;
    int aux3 = i + (dim + 1);
    int aux4 = j + (dim + 1);

    if(mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel->divisao == HUMANO){
        atributos.divisao = HUMANO;
    }
    if(mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel->divisao == MECANICO){
        atributos.divisao = MECANICO;
    }
    if(mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel->divisao == ELETRICO){
        atributos.divisao = ELETRICO;
    }

    while (1) {
        for(x = aux1; x <  aux3; x++){
            for(y = aux2; y < aux4; y++){
                if(mapa[x][y].pUniImovel == NULL && mapa[x][y].pUniMovel == NULL && mapa[x][y].pBase == NULL ){
                    cria_uni_movel(mapa, x, y, atributos, player);
                    return 0;
                }
            }
        }
        aux1--;
        aux2--;
        aux3++;
        aux4++;
    }      
} 

void restaurar_acoes(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA]) {
    int i, j;
    for (i = 0; i < BLOCOS_LINHA; i++) {
        for (j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pUniMovel != NULL) {
                mapa[i][j].pUniMovel->acao = true;
                mapa[i][j].pUniMovel->cont_ataque = true;
            }
            if (mapa[i][j].pUniImovel != NULL){
                mapa[i][j].pUniImovel->cont_ataque = true;
            }
            
        }
    }
}

