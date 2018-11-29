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

    if (x >= 0 && x <= RY && y >= 0 && y <= RY &&
            mapa[i][j].pUniMovel == NULL &&
            mapa[i][j].pUniImovel == NULL &&
            mapa[i][j].pBase == NULL) {
        return true;
    }
    /*
    if(x >= 0 && x <= RY && y >= 0 && y <= RY 
        && mapa[i][j].pUniMovel != NULL){
            //printf("Unidade encontrada\n");
            return false;
    }
    */
     else{
    printf("Posicao x = %d y = %d cheia ou invalida!\n", x, y);
    return false;

    }

    //printf("Posicao x = %d y = %d cheia ou invalida!\n", x, y);
    //return false;
}

int verifica_selecao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data mouse) {

    int i = mouse.y_mem/LADO;
    int j = mouse.x_mem/LADO;

    if (mapa[i][j].pUniMovel != NULL) {
        return 1;
    } else if (mapa[i][j].pUniImovel != NULL) {
        return 2;
    } else if (mapa[i][j].pBase != NULL) {
        return 3;
    }

    return 0;
}

int verifica_unidades(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data mouse, player_data *player, atributos_data atributos) {
    if (verifica_selecao(mapa, mouse) == 1) {
        
        SDL_Event evento;
        int cell_i = mouse.y/LADO;
        int cell_j = mouse.x/LADO;
        unidade_movel* aux = mapa[cell_i][cell_j].pUniMovel;

        while (evento.type != SDL_MOUSEBUTTONDOWN && evento.button.button != SDL_BUTTON_LEFT) {
            if (evento.type == SDL_KEYUP && evento.key.keysym.sym == SDLK_x) {
                break;
            }
            
            SDL_PollEvent(&evento);
            if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT) {
                cell_i = evento.button.y/LADO;
                cell_j = evento.button.x/LADO;

                if (verifica_espaco(mapa, cell_i, cell_j) && (aux->i != cell_i || aux->j != cell_j)) {
                    if(aux->divisao == OPERARIO){
                        construction(mapa, atributos, cell_i, cell_j, aux, player);
                        move_unidade(mapa, aux, cell_i - 1, cell_j - 1);  
                        break;
                    } else{
                     move_unidade(mapa, aux, cell_i, cell_j);   
                    }
                    
                }
                if (mapa[cell_i][cell_j].pUniMovel != NULL && (aux->i != cell_i || aux->j != cell_j)) {
                    printf("INICIAR COMBATE\n");
                    unidade_movel* aux2 = mapa[cell_i][cell_j].pUniMovel;
                    combate(mapa, aux, aux2, player);

                }
                if (mapa[cell_i][cell_j].pUniImovel != NULL && (aux->i != cell_i || aux->j != cell_j)) {
                    printf("INICIAR ATAQUE\n");
                    unidade_estatica* aux2 = mapa[cell_i][cell_j].pUniImovel;
                    destruicao(mapa, aux, aux2, player);
                }
            }
        }
    }
    if(verifica_selecao(mapa, mouse) == 2){
        int cell_i = mouse.y/LADO;
        int cell_j = mouse.x/LADO;
        unidade_estatica* aux = mapa[cell_i][cell_j].pUniImovel;
        evolution(aux, player);
        //Atualizar_recursos(mapa, player);
    }
    return 0;
}
