/**
 * @file verificacao.cpp
 *
 * @brief Arquivo com as funções de verificação de atos no jogo
 *
 * @author Grupo 2
 *
 */


#include <stdlib.h>
#include "funcoes.h"


int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

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
    } else {
        printf("Posicao x = %d y = %d cheia ou invalida!\n", x, y);
        return false;
    }
}

int verifica_selecao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data mouse) {

    int i = mouse.y_mem/LADO;
    int j = mouse.x_mem/LADO;

    //printf("mouse x mem: %d\n", mouse.x_mem);
    //printf("mouse y mem: %d\n", mouse.y_mem);

    if (mapa[i][j].pUniMovel != NULL) {
        return 1;

    } else if (mapa[i][j].pUniImovel != NULL) {
        return 2;

    } else if (mapa[i][j].pBase != NULL) {
        return 3;
    }

    return 0;
}

int verifica_unidades(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data *mouse, player_data *player, atributos_data atributos, imagens_data imagens, texto_data texto) {
    
    if (verifica_selecao(mapa, *mouse) == 1) { // caso unidade movel

        bool stop = false;
        SDL_Event evento;
        int cell_i = mouse->y/LADO;
        int cell_j = mouse->x/LADO;

        unidade_movel* aux = mapa[cell_i][cell_j].pUniMovel;

        if (aux == NULL) {
            return -1;
        }

        if (player->time != aux->time) {
            return 0;
        }

        while (!stop) {
            while (SDL_PollEvent(&evento)) {
                //carrega_interface(mapa, imagens, mouse, texto, player, atributos);
                /*
                if (aux->divisao == OPERARIO) {
                    carrega_botao(imagens, texto, mouse, 0, CRIAR_GER_REC);
                    carrega_botao(imagens, texto, mouse, 1, CRIAR_GER_TRO);
                    carrega_botao(imagens, texto, mouse, 2, CRIAR_MUR);
                }
                */
                if (evento.type == SDL_MOUSEBUTTONDOWN && evento.button.button == SDL_BUTTON_LEFT) {
                    cell_i = evento.button.y/LADO;
                    cell_j = evento.button.x/LADO;

                    if (verifica_velocidade(aux, cell_i, cell_j)) {
                        if (verifica_espaco(mapa, cell_i, cell_j) && (aux->i != cell_i || aux->j != cell_j)) {
                            if (aux->divisao == OPERARIO) {
                                //construction(mapa, atributos, cell_i, cell_j, aux, player);
                                //cell_i--;
                                //cell_j--;
                            }
                            move_unidade(mapa, aux, cell_i, cell_j);
                        }
                    } else {
                        printf("Essa unidade nao alcanca toda essa distancia!\n");
                    }

                    if (verifica_alcance(aux, cell_i, cell_j)) {
                        if (mapa[cell_i][cell_j].pUniMovel != NULL
                            && (aux->i != cell_i || aux->j != cell_j)
                            && verifica_oposicao(mapa, aux, cell_i, cell_j)) {

                            printf("INICIAR COMBATE\n");
                            unidade_movel* aux2 = mapa[cell_i][cell_j].pUniMovel;
                            printf("%d %d\n", cell_i, cell_j);
                            combate(mapa, aux, aux2, player);
                        }
                        if (mapa[cell_i][cell_j].pUniImovel != NULL
                            && (aux->i != cell_i || aux->j != cell_j)
                            && verifica_oposicao(mapa, aux, cell_i, cell_j)) {

                            printf("INICIAR ATAQUE\n");
                            unidade_estatica* aux2 = mapa[cell_i][cell_j].pUniImovel;
                            printf("%d %d\n", cell_i, cell_j);
                            destruicao(mapa, aux, aux2, player);
                        }
                    }
                    stop = true;
                    mouse->x = -1;
                    mouse->y = -1;
                }
                /*
                if (evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_x) {
                    stop = true;
                    mouse->x_mem = evento.button.x;
                    mouse->y_mem = evento.button.y;
                }
                */
            }
        }
    } else if (verifica_selecao(mapa, *mouse) == 2) { //caso unidade estatica

        int cell_i = mouse->y_mem/LADO;
        int cell_j = mouse->x_mem/LADO;
        unidade_estatica* aux = mapa[cell_i][cell_j].pUniImovel;

        if (player->time != aux->time) {
            return 0;
        }

        evolution(aux, player);
        //Atualizar_recursos(mapa, player);
    }
    return 0;
}

bool verifica_velocidade (unidade_movel* aux, int cell_i, int cell_j) {
    if (cell_i <= min(aux->i + aux->velocidade, 39) && cell_i >= max(aux->i - aux->velocidade, 0)
        && cell_j <= min(aux->j + aux->velocidade, 39) && cell_j >= max(aux->j - aux->velocidade, 0)) {
        return true;
    } else {
        return false;
    }
}

bool verifica_alcance (unidade_movel* aux, int cell_i, int cell_j) {
    if (cell_i <= min(aux->i + aux->alcance, 39) && cell_i >= max(aux->i - aux->alcance, 0)
        && cell_j <= min(aux->j + aux->alcance, 39) && cell_j >= max(aux->j - aux->alcance, 0)) {
        return true;
    } else {
        return false;
    } 
}

bool verifica_oposicao (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA],
                        unidade_movel* aux, int i, int j) {
    if (mapa[i][j].pUniMovel != NULL
        && mapa[i][j].pUniMovel->time != aux->time) {

        return true;

    } else if (mapa[i][j].pUniImovel != NULL
        && mapa[i][j].pUniImovel->time != aux->time) {

        return true;

    } else if (mapa[i][j].pBase != NULL
        && mapa[i][j].pBase->time != aux->time) {

        return true;

    } else {
        return false;
    }
}
