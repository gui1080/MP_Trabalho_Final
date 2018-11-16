#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>
#include "SDL/SDL_image.h"
#include "string"
#include "funcoes.h"

GLuint loadTexture(const std::string&fileName) {
    SDL_Surface *imagem = IMG_Load(fileName.c_str());  // carrega imagem
    SDL_DisplayFormatAlpha(imagem);  // formato alpha
    unsigned object(0);  // cria textura
    glGenTextures(1, &object);  // gera textura
    glBindTexture(GL_TEXTURE_2D, object);  // tipo de textura, 2D

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagem->w, imagem->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagem->pixels);

    SDL_FreeSurface(imagem);

    return object;
}

int carrega_mapa(cell_mapa mapa[40][40], int Y, int lado) {

    int x = 0;
    int y = 0;

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            mapa[i][j].x = x;
            mapa[i][j].y = y;
            mapa[i][j].lado = lado;
            mapa[i][j].pBase = NULL;
            mapa[i][j].pUniMovel = NULL;
            mapa[i][j].pUniImovel = NULL;
            x += lado;
        }
        y += lado;
        x = 0;
    }
    return 0;
}


int carrega_interface(cell_mapa mapa[40][40], imagens_data imagens, mouse_data mouse) {

    //  cria matriz
    glPushMatrix();

    // dimensoes da matriz
    glOrtho(0, RX, RY, 0, -1, 1);

    glColor4ub(0, 0, 0, 255);

    glBegin(GL_LINES);  // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

    glVertex2f(801,0);
    glVertex2f(801,800);
    // fecha
    glEnd();


    glColor4ub(128, 128, 128, 255);

    glBegin(GL_QUADS);  // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

    glVertex2f(801,0);
    glVertex2f(1200,0);
    glVertex2f(1200,800);
    glVertex2f(801,800);
    // fecha
    glEnd();    

    glEnable(GL_TEXTURE_2D);

    // CARREGANDO FUNDO
    glBindTexture(GL_TEXTURE_2D, imagens.textura_fundo);

    glColor4ub(255, 255, 255, 255);    

    glBegin(GL_QUADS);

    glTexCoord2d(0,0);  glVertex2f(0, 0); // primeiro ponto
    glTexCoord2d(1,0);  glVertex2f(RY, 0); // segundo ponto
    glTexCoord2d(1,1);  glVertex2f(RY, RY);
    glTexCoord2d(0,1);  glVertex2f(0, RY);

    glEnd();

    carrega_base(mapa, imagens);

    /*
    //CARREGANDO BASE

    glBindTexture(GL_TEXTURE_2D, imagens.textura_base);

    glColor4ub(255, 255, 255, 255);    

    glBegin(GL_QUADS);

    glTexCoord2d(0,0);  glVertex2f(20, 720); // primeiro ponto
    glTexCoord2d(1,0);  glVertex2f(89, 720); // segundo ponto
    glTexCoord2d(1,1);  glVertex2f(89, 779);
    glTexCoord2d(0,1);  glVertex2f(20, 779);

    glEnd();
    */
    // CARREGANDO GRADE
    glBindTexture(GL_TEXTURE_2D, imagens.textura_grade);

    glColor4ub(255, 255, 255, 64);

    glBegin(GL_QUADS);

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            if (j == mouse.x/20 && i == mouse.y/20 && mouse.y != -1) {
                glColor4ub(0, 0, 255, 255);         
                if (mapa[i][j].pBase != NULL) {
                    printf("BASE\n");   
                }else{
                    printf("TERRENO\n");
                }
            }
            glTexCoord2d(0,0);  glVertex2f(mapa[i][j].x, mapa[i][j].y); // primeiro ponto
            glTexCoord2d(1,0);  glVertex2f(mapa[i][j].x + mapa[i][j].lado, mapa[i][j].y); // segundo ponto
            glTexCoord2d(1,1);  glVertex2f(mapa[i][j].x + mapa[i][j].lado, mapa[i][j].y + mapa[i][j].lado);
            glTexCoord2d(0,1);  glVertex2f(mapa[i][j].x, mapa[i][j].y + mapa[i][j].lado);
            if (j == mouse.x/20 && i == mouse.y/20 && mouse.y != -1) {
                glColor4ub(255, 255, 255, 64);              
            }
        }
    }

    glEnd();

    glDisable(GL_TEXTURE_2D);   

    //glDisable(GL_TEXTURE_2D);

    // fecha matriz
    glPopMatrix();

    return 0;
}

int cria_base(cell_mapa mapa[40][40], int i, int j, int time) {
    base_principal *Base = (base_principal*)malloc(sizeof(base_principal));
    Base->vida = 20;
    Base->i = i;
    Base->j = j;
    Base->time = time;
    for (int p = i; p <= (i + 2); p++) {
        for (int q = j; q <= (j + 2); q++) {
            mapa[p][q].pBase = Base;
        }
    }
    return 0;
}

int carrega_base(cell_mapa mapa[40][40], imagens_data imagens) {

    int lado = 20;
    int dimensao = 3;

    glBindTexture(GL_TEXTURE_2D, imagens.textura_base);

    glColor4ub(255, 255, 255, 255);    

    glBegin(GL_QUADS);

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            if (mapa[i][j].pBase != NULL) {
                if (mapa[i][j].pBase->i == i && mapa[i][j].pBase->j == j) {
                    glTexCoord2d(0,0);  glVertex2f(j*lado, i*lado); // primeiro ponto
                    glTexCoord2d(1,0);  glVertex2f((j*lado + dimensao*lado)-1, i*lado); // segundo ponto
                    glTexCoord2d(1,1);  glVertex2f((j*lado + dimensao*lado)-1, (i*lado + dimensao*lado)-1);
                    glTexCoord2d(0,1);  glVertex2f(j*lado, (i*lado + dimensao*lado)-1);
                }
            }
        }
    }
    glEnd();

    return 0;
}
