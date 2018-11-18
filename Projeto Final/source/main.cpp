#include "funcoes.h"

int main(int argc, char* args[]) {
    printf("Rodando programa...\n");
    SDL_Init(SDL_INIT_EVERYTHING);

    /*CRIANDO JANELA*/

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

    /*FIM DA CRIAÇÃO*/

    bool executando = true;

    SDL_Event eventos;

    // pegar textura
    unsigned int textura_grade;
    unsigned int textura_fundo;
    unsigned int textura_base;
    unsigned int humano_GER_REC;
    unsigned int humano_GER_TROP;
    unsigned int humano_DEF_OFS;
    unsigned int humano_DEF_PAS;
    unsigned int mecanico_GER_REC;
    unsigned int mecanico_GER_TROP;
    unsigned int mecanico_DEF_OFS;
    unsigned int mecanico_DEF_PAS;
    unsigned int eletrico_GER_REC;
    unsigned int eletrico_GER_TROP;
    unsigned int eletrico_DEF_OFS;
    unsigned int eletrico_DEF_PAS;
    imagens_data imagens;

    if (verifica_imagem("grade.png") == false ||
        verifica_imagem("sand.png") == false ||
        verifica_imagem("base.png") == false ||
        verifica_imagem("Akeno.png") == false ||
        verifica_imagem("albedo.png") == false ||
        verifica_imagem("chitoge2.png") == false ||
        verifica_imagem("Dva.png") == false ||
        verifica_imagem("Eliza.png") == false ||
        verifica_imagem("Emilia.png") == false ||
        verifica_imagem("Hatsune.png") == false ||
        verifica_imagem("Lucy.png") == false ||
        verifica_imagem("megumin.png") == false ||
        verifica_imagem("Rias.png") == false ||
        verifica_imagem("Lucy4.png") == false ||
        verifica_imagem("Rias2.png") == false
        ) {

        printf("FALHA AO CARREGAR IMAGEM\n");
        SDL_Quit();
        return -1;
    }

    textura_grade = loadTexture("grade.png");
    textura_fundo = loadTexture("sand.png");
    textura_base = loadTexture("base.png");
    humano_GER_REC = loadTexture("Akeno.png");
    humano_GER_TROP = loadTexture("albedo.png");
    humano_DEF_OFS = loadTexture("chitoge2.png");
    humano_DEF_PAS = loadTexture("Dva.png");
    mecanico_GER_REC = loadTexture("Eliza.png");
    mecanico_GER_TROP = loadTexture("Emilia.png");
    mecanico_DEF_OFS = loadTexture("Hatsune.png");
    mecanico_DEF_PAS = loadTexture("Lucy.png");
    eletrico_GER_REC = loadTexture("megumin.png");
    eletrico_GER_TROP = loadTexture("Rias.png");
    eletrico_DEF_OFS = loadTexture("Lucy4.png");
    eletrico_DEF_PAS = loadTexture("Rias2.png");

    imagens.textura_grade = textura_grade;
    imagens.textura_fundo = textura_fundo;
    imagens.textura_base = textura_base;
    imagens.humano_GER_REC = humano_GER_REC;
    imagens.humano_GER_TROP = humano_GER_TROP;
    imagens.humano_DEF_OFS = humano_DEF_OFS;
    imagens.humano_DEF_PAS = humano_DEF_PAS;
    imagens.mecanico_GER_REC = mecanico_GER_REC;
    imagens.mecanico_GER_TROP = mecanico_GER_TROP;
    imagens.mecanico_DEF_OFS = mecanico_DEF_OFS;
    imagens.mecanico_DEF_PAS = mecanico_DEF_PAS;
    imagens.eletrico_GER_REC = eletrico_GER_REC;
    imagens.eletrico_GER_TROP = eletrico_GER_TROP;
    imagens.eletrico_DEF_OFS = eletrico_DEF_OFS;
    imagens.eletrico_DEF_PAS = eletrico_DEF_PAS;

    //  Carrega mapa
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    cria_mapa(mapa);

    // i = 35, j = 1, dimensao = 4, vida = 20, time = 0
    if (cria_base(mapa, 35, 1, 4, 20, 0) == -1) {
        printf("FALHA AO CRIAR BASE 1\n");
        SDL_Quit();
        return -1; 
    }
    //1, 35, 4, 20, 1
    if (cria_base(mapa, 1, 35, 4, 20, 1) == -1) {
        printf("FALHA AO CRIAR BASE 2\n");
        SDL_Quit();
        return -1; 
    }

    atributos_data atributos;

    atributos.divisao = ELETRICO;
    atributos.classe = GERADOR_DE_RECURSO;
    atributos.time = 0;
    atributos.nivel = 1;

    if (cria_uni_estatico(mapa, 20, 20, atributos) == -1) {
        printf("FALHA AO CRIAR ESTRUTURA\n");
        SDL_Quit();
        return -1;   
    }

    atributos.divisao = MECANICO;
    atributos.classe = GERADOR_DE_TROPA;
    atributos.time = 0;
    atributos.nivel = 1;

    if (cria_uni_estatico(mapa, 30, 30, atributos) == -1) {
        printf("FALHA AO CRIAR ESTRUTURA\n");
        SDL_Quit();
        return -1;   
    }

    atributos.divisao = ELETRICO;
    atributos.classe = DEFESA_OFENSIVA;
    atributos.time = 0;
    atributos.nivel = 1;

    if (cria_uni_estatico(mapa, 10, 10, atributos) == -1) {
        printf("FALHA AO CRIAR ESTRUTURA\n");
        SDL_Quit();
        return -1;   
    }

    atributos.divisao = HUMANO;
    atributos.classe = DEFESA_OFENSIVA;
    atributos.time = 0;
    atributos.nivel = 1;

    if (cria_uni_estatico(mapa, 30, 10, atributos) == -1) {
        printf("FALHA AO CRIAR ESTRUTURA\n");
        SDL_Quit();
        return -1;   
    }

    atributos.divisao = ELETRICO;
    atributos.classe = DEFESA_PASSIVA;
    atributos.time = 0;
    atributos.nivel = 1;

    if (cria_uni_estatico(mapa, 10, 30, atributos) == -1) {
        printf("FALHA AO CRIAR ESTRUTURA\n");
        SDL_Quit();
        return -1;   
    }

    int mouse_x = -1;
    int mouse_y = -1;
    mouse_data mouse;

    while (executando) {
        // eventos
        while (SDL_PollEvent(&eventos)) {
            // fecha com o x da janela ou com ESC
            if (eventos.type == SDL_QUIT) {
                executando = false;
            } else if (eventos.type == SDL_KEYUP && eventos.key.keysym.sym == SDLK_ESCAPE) {
                executando = false;
            }

            if (eventos.type == SDL_MOUSEBUTTONDOWN) {
                if (eventos.button.button == SDL_BUTTON_LEFT) {
                    mouse_x = eventos.button.x;
                    mouse_y = eventos.button.y;
                    printf("x = %d y = %d\n", mouse_x, mouse_y);
                    printf("i = %d j = %d\n", mouse_y/LADO, mouse_x/LADO);
                }
            } else if (eventos.type == SDL_MOUSEBUTTONUP) {
                    mouse_x = -1;
                    mouse_y = -1;
            }
        }
        // LIMPA O BUFFER
        glClear(GL_COLOR_BUFFER_BIT);

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
