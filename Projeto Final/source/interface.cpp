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

int carrega_interface(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data mouse) {

    //  cria matriz
    glPushMatrix();

    // dimensoes da matriz
    glOrtho(0, RX, RY, 0, -1, 1);

    glColor4ub(0, 0, 0, 255);

    glBegin(GL_LINES);  // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

    glVertex2f(RY+1,0);
    glVertex2f(RY+1,RY);
    // fecha
    glEnd();


    glColor4ub(128, 128, 128, 255);

    glBegin(GL_QUADS);  // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

    glVertex2f(RY+1, 0);
    glVertex2f(RX, 0);
    glVertex2f(RX, RY);
    glVertex2f(RY+1, RY);
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

    // CARREGANDO GRADE
    glBindTexture(GL_TEXTURE_2D, imagens.textura_grade);

    glColor4ub(255, 255, 255, 64);

    glBegin(GL_QUADS);

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            if (j == mouse.x/LADO && i == mouse.y/LADO && mouse.y != -1) {
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
            if (j == mouse.x/LADO && i == mouse.y/LADO && mouse.y != -1) {
                glColor4ub(255, 255, 255, 64);              
            }
        }
    }

    glEnd();

    carrega_base(mapa, imagens);

    glDisable(GL_TEXTURE_2D);   

    // fecha matriz
    glPopMatrix();

    return 0;
}

int carrega_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens) {

    glBindTexture(GL_TEXTURE_2D, imagens.textura_base);    

    glBegin(GL_QUADS);

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pBase != NULL) {
                if (mapa[i][j].pBase->i == i && mapa[i][j].pBase->j == j) {

                    if (mapa[i][j].pBase->time == 0) glColor4ub(0, 0, 255, 255); 
                    else glColor4ub(255, 0, 0, 255);

                    glTexCoord2d(0,0);  glVertex2f(j*LADO, i*LADO); // primeiro ponto
                    glTexCoord2d(1,0);  glVertex2f((j*LADO + mapa[i][j].pBase->dim*LADO), i*LADO); // segundo ponto
                    glTexCoord2d(1,1);  glVertex2f((j*LADO + mapa[i][j].pBase->dim*LADO), (i*LADO + mapa[i][j].pBase->dim*LADO));
                    glTexCoord2d(0,1);  glVertex2f(j*LADO, (i*LADO + mapa[i][j].pBase->dim*LADO));
                }
            }
        }
    }
    glEnd();

    return 0;
}
