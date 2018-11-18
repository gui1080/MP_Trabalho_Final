#include <stdlib.h>
#include "funcoes.h"


bool verifica_imagem(const std::string&fileName) {

    FILE *imagem = fopen(fileName.c_str(), "r");
    if (!imagem) {
        printf("arquivo: %s não encontrado!\n", fileName.c_str());
        return false;
    }
    fclose(imagem);

    return true;
}

bool verifica_espaco(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j) {

    int x = (j+1)*LADO;
    int y = (i+1)*LADO;

    if (x >= 0 && x < RY && y >= 0 && y < RY &&
            mapa[i][j].pUniMovel == NULL &&
            mapa[i][j].pUniImovel == NULL &&
            mapa[i][j].pBase == NULL) {
        return true;
    }

    printf("Posicao x = %d y = %d cheia ou invalida!\n", x, y);
    return false;
}
