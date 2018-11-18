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

    carrega_layout();

    //  CARREGA ESTRUTURAS E ICONES
    glEnable(GL_TEXTURE_2D);

    carrega_display_recursos(imagens);
    carrega_mapa(mapa, imagens, mouse);
    carrega_base(mapa, imagens);
    carrega_uni_estatico(mapa, imagens);  
    carrega_uni_movel(mapa, imagens);

    // fecha matriz
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    return 0;
}

int carrega_layout(){

    //  CARREGA DIVISORIA DO MAPA
    glColor4ub(0, 0, 0, 255);

    glBegin(GL_LINES);  // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON
    glVertex2f(RY+1,0);
    glVertex2f(RY+1,RY);
    glEnd();


    //  PREENCHE FUNDO DIREITO
    glColor4ub(128, 128, 128, 255);

    glBegin(GL_QUADS);
    glVertex2f(RY+1, 0);
    glVertex2f(RX, 0);
    glVertex2f(RX, RY);
    glVertex2f(RY+1, RY);
    glEnd();
    
    //BARRA DEITADA
    glColor4ub(0, 0, 0, 255);

    glBegin(GL_LINES);

    glVertex2f(RY,RY-LARGURA_INFERIOR);
    glVertex2f(RX,RY-LARGURA_INFERIOR);

    glEnd();

    return 0;
}

int carrega_mapa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data mouse) {

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
                }else if (mapa[i][j].pUniImovel != NULL) {
                    printf("CONSTRUCAO\n");
                } else {
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

    return 0;
}

int carrega_display_recursos (imagens_data imagens) {
    int dimensao_icone = 40; //  NÃO PODE SER MAIOR QUE A LARGURA
    int tamanho_texto = 90; //  NÃO PODE SER MAIOR QUE RX-RY-dimensao_icone
    int gap_vertical = (LARGURA_INFERIOR - dimensao_icone) / 2;
    int gap_horizontal = ((RX-RY) - (3 * dimensao_icone) - (3 * tamanho_texto)) / 2;
    int flag = 0;

    int x = RY + gap_horizontal;
    int y = RY - gap_vertical;

    //ICONES

    for (int i = 0; i < 3; i++) {
        switch (flag) {
            case 0:
                glBindTexture(GL_TEXTURE_2D, imagens.comida);
                break;
            case 1:
                glBindTexture(GL_TEXTURE_2D, imagens.minerio);
                break;
            case 2:
                glBindTexture(GL_TEXTURE_2D, imagens.raio);
                break;
        }

        glColor4ub(255, 255, 255, 255);

        glBegin(GL_QUADS);    
        glTexCoord2d(0,0);  glVertex2f(x, y-dimensao_icone); // primeiro ponto
        glTexCoord2d(1,0);  glVertex2f(x+dimensao_icone, y-dimensao_icone); // segundo ponto
        glTexCoord2d(1,1);  glVertex2f(x+dimensao_icone, y);
        glTexCoord2d(0,1);  glVertex2f(x, y);
        glEnd();

        //PREPARANDO PROXIMO ICONE
        x += dimensao_icone + tamanho_texto;
        flag++;
    }

    return 0;

}


int carrega_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens) {

    glBindTexture(GL_TEXTURE_2D, imagens.textura_base);    

    glBegin(GL_QUADS);

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pBase != NULL) {
                if (mapa[i][j].pBase->i == i && mapa[i][j].pBase->j == j) {

                    if (mapa[i][j].pBase->time == 0) 
                        glColor4ub(128, 128, 255, 255); 
                    else 
                        glColor4ub(255, 128, 128, 255);

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

int carrega_uni_estatico(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens) {

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pUniImovel != NULL) {
                if (mapa[i][j].pUniImovel->i == i && mapa[i][j].pUniImovel->j == j) {
                    if (mapa[i][j].pUniImovel->time == 0) 
                        glColor4ub(255, 255, 255, 255); 
                    else 
                        glColor4ub(255, 255, 255, 255);

                        switch (mapa[i][j].pUniImovel->divisao) {
                            case HUMANO:
                                switch (mapa[i][j].pUniImovel->classe) {
                                    case GERADOR_DE_RECURSO:
                                        glBindTexture(GL_TEXTURE_2D, imagens.humano_GER_REC);
                                        break;
                                    case GERADOR_DE_TROPA:
                                        glBindTexture(GL_TEXTURE_2D, imagens.humano_GER_TROP);
                                        break;
                                    case DEFESA_OFENSIVA:
                                        glBindTexture(GL_TEXTURE_2D, imagens.humano_DEF_OFS);
                                        break;
                                    case DEFESA_PASSIVA:
                                        glBindTexture(GL_TEXTURE_2D, imagens.humano_DEF_PAS);
                                        break;
                                }
                                break;
                            case MECANICO:
                                switch (mapa[i][j].pUniImovel->classe) {
                                    case GERADOR_DE_RECURSO:
                                        glBindTexture(GL_TEXTURE_2D, imagens.mecanico_GER_REC);
                                        break;
                                    case GERADOR_DE_TROPA:
                                        glBindTexture(GL_TEXTURE_2D, imagens.mecanico_GER_TROP);
                                        break;
                                    case DEFESA_OFENSIVA:
                                        glBindTexture(GL_TEXTURE_2D, imagens.mecanico_DEF_OFS);
                                        break;
                                    case DEFESA_PASSIVA:
                                        glBindTexture(GL_TEXTURE_2D, imagens.mecanico_DEF_PAS);
                                        break;
                                }
                                break;
                            case ELETRICO:
                                switch (mapa[i][j].pUniImovel->classe) {
                                    case GERADOR_DE_RECURSO:
                                        glBindTexture(GL_TEXTURE_2D, imagens.eletrico_GER_REC);
                                        break;
                                    case GERADOR_DE_TROPA:
                                        glBindTexture(GL_TEXTURE_2D, imagens.eletrico_GER_TROP);
                                        break;
                                    case DEFESA_OFENSIVA:
                                        glBindTexture(GL_TEXTURE_2D, imagens.eletrico_DEF_OFS);
                                        break;
                                    case DEFESA_PASSIVA:
                                        glBindTexture(GL_TEXTURE_2D, imagens.eletrico_DEF_PAS);
                                        break;
                                }
                                break;
                        }                    
                    glBegin(GL_QUADS);
                    glTexCoord2d(0,0);  glVertex2f(j*LADO, i*LADO); // primeiro ponto
                    glTexCoord2d(1,0);  glVertex2f((j*LADO + mapa[i][j].pUniImovel->dim*LADO), i*LADO); // segundo ponto
                    glTexCoord2d(1,1);  glVertex2f((j*LADO + mapa[i][j].pUniImovel->dim*LADO), (i*LADO + mapa[i][j].pUniImovel->dim*LADO));
                    glTexCoord2d(0,1);  glVertex2f(j*LADO, (i*LADO + mapa[i][j].pUniImovel->dim*LADO));
                    glEnd();
                }
            }
        }
    }

    return 0;
}

int carrega_uni_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens) {

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pUniMovel != NULL) {
                if (mapa[i][j].pUniMovel->i == i && mapa[i][j].pUniMovel->j == j) {
                    if (mapa[i][j].pUniMovel->time == 0) glColor4ub(255, 255, 255, 255); 
                    else glColor4ub(255, 255, 255, 255);

                        switch (mapa[i][j].pUniMovel->divisao) {
                            case HUMANO:
                                switch (mapa[i][j].pUniMovel->nivel) {
                                    case 1:
                                        glBindTexture(GL_TEXTURE_2D, imagens.humano_GER_REC);
                                        break;
                                    case 2:
                                        glBindTexture(GL_TEXTURE_2D, imagens.humano_GER_TROP);
                                        break;
                                    case 3:
                                        glBindTexture(GL_TEXTURE_2D, imagens.humano_DEF_OFS);
                                        break;
                                }
                                break;
                            case MECANICO:
                                switch (mapa[i][j].pUniMovel->nivel) {
                                    case 1:
                                        glBindTexture(GL_TEXTURE_2D, imagens.mecanico_GER_REC);
                                        break;
                                    case 2:
                                        glBindTexture(GL_TEXTURE_2D, imagens.mecanico_GER_TROP);
                                        break;
                                    case 3:
                                        glBindTexture(GL_TEXTURE_2D, imagens.mecanico_DEF_OFS);
                                        break;
                                }
                                break;
                            case ELETRICO:
                                switch (mapa[i][j].pUniMovel->nivel) {
                                    case 1:
                                        glBindTexture(GL_TEXTURE_2D, imagens.eletrico_GER_REC);
                                        break;
                                    case 2:
                                        glBindTexture(GL_TEXTURE_2D, imagens.eletrico_GER_TROP);
                                        break;
                                    case 3:
                                        glBindTexture(GL_TEXTURE_2D, imagens.eletrico_DEF_OFS);
                                        break;
                                }
                                break;
                        }                    
                    glBegin(GL_QUADS);
                    glTexCoord2d(0,0);  glVertex2f(j*LADO, i*LADO); // primeiro ponto
                    glTexCoord2d(1,0);  glVertex2f((j*LADO + mapa[i][j].pUniMovel->dim*LADO), i*LADO); // segundo ponto
                    glTexCoord2d(1,1);  glVertex2f((j*LADO + mapa[i][j].pUniMovel->dim*LADO), (i*LADO + mapa[i][j].pUniMovel->dim*LADO));
                    glTexCoord2d(0,1);  glVertex2f(j*LADO, (i*LADO + mapa[i][j].pUniMovel->dim*LADO));
                    glEnd();
                }
            }
        }
    }

    return 0;
}
