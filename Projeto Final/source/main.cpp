#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>
#include "SDL/SDL_image.h"
#include "string"
#include "funcoes.h"

int main(int argc, char* args[]) {
    printf("Rodando programa...\n");
    SDL_Init(SDL_INIT_EVERYTHING);

    // memoria
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // nome janela
    SDL_WM_SetCaption("Meu primeiro jogo SDL", NULL);

    // tamanho janela
    SDL_SetVideoMode(RX, RY, 32, SDL_OPENGL);

    // cor
    glClearColor(1, 1, 1, 1);

    // area exibida
    glViewport(0, 0, RX, RY);

    // sombra
    glShadeModel(GL_SMOOTH);

    // 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  // desenho geometrico

    // 3D
    glDisable(GL_DEPTH_TEST);

    // para uso da imagem
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    bool executando = true;

    SDL_Event eventos;

    // exemplo de pegar textura
    unsigned int textura_exemplo = 0;
    textura_exemplo = loadTexture("grama.jpg");

    //  Carrega mapa
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    carrega_mapa(mapa, RY, LADO);

    while (executando) {
        // eventos
        while (SDL_PollEvent(&eventos)) {
            // fecha com o x da janela
            if (eventos.type == SDL_QUIT) {
                executando = false;
            }

            // esc
            if (eventos.type == SDL_KEYUP && eventos.key.keysym.sym == SDLK_ESCAPE) {
                executando = false;
            }
        }
        // RENDERIZACAO
        glClear(GL_COLOR_BUFFER_BIT);  // LIMPA O BUFFER

        /* 
        cor
        glColor3d( 1 ou 0)
        glColor3f( decimais )
        glColor3ub( R, G, B ) - 0 ATE 255
        glColor4ub(R, G, B, A) 0 ATE 255
        */

        carrega_interface(mapa);

        // animacao
        SDL_GL_SwapBuffers();
    }

    printf("Fechado com sucesso!\n");

    SDL_Quit();

    return 0;
}
