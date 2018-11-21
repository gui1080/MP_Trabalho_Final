#include "funcoes.h"
#include <unistd.h>

int move_unis_mapa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data mouse) {
	unidade_movel* aux = NULL;
	int cell_i = mouse.y/LADO;
	int cell_j = mouse.x/LADO;

	for (int i = 0; i < BLOCOS_LINHA; i++) {
		for (int j = 0; j < BLOCOS_LINHA; j++) {
			if (mapa[i][j].pUniMovel != NULL) {
				aux = mapa[i][j].pUniMovel;
				if (mouse.x != -1 && mouse.y != -1 && cell_j < 40 && cell_i < 40 &&
					verifica_espaco(mapa, cell_i, cell_j) && (aux->i != cell_i || aux->j != cell_j)) {

					move_unidade(mapa, aux, cell_i, cell_j);
				}
			}
		}
	}
	return 0;
}

int move_unidade (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* unit, int i, int j) {
	cell_mapa* anterior = &mapa[unit->i][unit->j];
	unit->i = i;
	unit->j = j;
	anterior->pUniMovel = NULL;
	mapa[i][j].pUniMovel = unit;
	return 0;
}
