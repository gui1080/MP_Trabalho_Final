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

    // pegar textura
    unsigned int textura_grade = 0;
    unsigned int textura_fundo = 0;
    unsigned int textura_base = 0;
    textura_grade = loadTexture("grade.png");
    textura_fundo = loadTexture("sand.png");
    textura_base = loadTexture("base.png");

    //  Carrega mapa
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    carrega_mapa(mapa, RY, LADO);


    // i = 36, j = 1 time = 0
    cria_base(mapa, 36, 1, 0);
    
    int mouse_x = -1;
    int mouse_y = -1;

    imagens_data imagens; 
    mouse_data mouse;

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

            if (eventos.type == SDL_MOUSEBUTTONDOWN) {
                if (eventos.button.button == SDL_BUTTON_LEFT) {
                    mouse_x = eventos.button.x;
                    mouse_y = eventos.button.y;
                    printf("x = %d y = %d\n", mouse_x, mouse_y);
                    printf("i = %d j = %d\n", mouse_y/20, mouse_x/20);
                }
            } 
            else if (eventos.type == SDL_MOUSEBUTTONUP) {
                    mouse_x = -1;
                    mouse_y = -1;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);  // LIMPA O BUFFER

        /* 
        cor
        glColor3d( 1 ou 0)
        glColor3f( decimais )
        glColor3ub( R, G, B ) - 0 ATE 255
        glColor4ub(R, G, B, A) 0 ATE 255
        */
        imagens.textura_grade = textura_grade;
        imagens.textura_fundo = textura_fundo;
        imagens.textura_base = textura_base;

        mouse.x = mouse_x;
        mouse.y = mouse_y;

        carrega_interface(mapa, imagens, mouse);

        // animacao
        SDL_GL_SwapBuffers();
    }

    printf("Fechado com sucesso!\n");

    SDL_Quit();

    return 0;
}
