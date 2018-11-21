#include "funcoes.h"

int move_unidade (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* unit, int i, int j) {
	cell_mapa* anterior = &mapa[unit->i][unit->j];
	unit->i = i;
	unit->j = j;
	anterior->pUniMovel = NULL;
	mapa[i][j].pUniMovel = unit;
	return 0;
}
