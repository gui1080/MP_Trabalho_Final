#include "funcoes.h"
#include <unistd.h>

int move_unidade (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* unit, int i, int j) {
	cell_mapa* anterior = &mapa[unit->i][unit->j];
	unit->i = i;
	unit->j = j;
	anterior->pUniMovel = NULL;
	mapa[i][j].pUniMovel = unit;
	return 0;
}

/*
define_mov_rang(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* aux){
 	aux->i = i;
 	aux->j = j;
 	for(i = i - aux->velocidade/2; i < i + aux->velocidade/2; i++){
 		for(j = j - aux->velocidade/2; j < j + aux->velocidade/2; i++){
 			if(i != aux->i && j != aux->j){  
 				mapa[i][j].cor = 1;
 			}
 		}
 	}


}
*/