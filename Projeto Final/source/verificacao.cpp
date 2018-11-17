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
