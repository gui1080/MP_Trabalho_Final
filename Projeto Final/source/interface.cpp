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

GLuint importText(const std::string &text,int font_size,int red,int green,int blue){
    SDL_Color font_color = {blue,green,red};
    TTF_Font* font=TTF_OpenFont("arial.ttf",font_size);
    SDL_Surface *image = TTF_RenderText_Blended(font,text.c_str(),font_color);
    SDL_DisplayFormatAlpha(image);

    unsigned object(0);

    glGenTextures(1,&object);
    glBindTexture(GL_TEXTURE_2D, object);
    
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA,image->w,image->h,0,GL_RGBA,GL_UNSIGNED_BYTE,image->pixels);

    SDL_FreeSurface(image);
    
    TTF_CloseFont(font);
    
    return object;
}

int carrega_interface(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data mouse, texto_data texto) {

    //  cria matriz
    glPushMatrix();

    // dimensoes da matriz
    glOrtho(0, RX, RY, 0, -1, 1); 

    carrega_layout();

    //  CARREGA ESTRUTURAS E ICONES
    glEnable(GL_TEXTURE_2D);

    carrega_display_recursos(imagens, texto);
    carrega_mapa(mapa, imagens, mouse);
    carrega_base(mapa, imagens);
    carrega_uni_estatico(mapa, imagens);  
    carrega_uni_movel(mapa, imagens);
    carrega_numeros_recurso (texto);

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

    glVertex2f(RY,RY-DIVISAO_INFERIOR);
    glVertex2f(RX,RY-DIVISAO_INFERIOR);

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
                } else if (mapa[i][j].pUniMovel != NULL) {
                	printf("UNID. MOVEL\n");
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


int carrega_numeros_recurso (texto_data texto) {
     //  NÃO PODE SER MAIOR QUE A LARGURA
     //  NÃO PODE SER MAIOR QUE RX-RY-DIMENSAO_ICONES
    int gap_vertical = (DIVISAO_INFERIOR - DIMENSAO_ICONES) / 2;
    int gap_horizontal = ((RX-RY) - (3 * DIMENSAO_ICONES) - (3 * TAMANHO_TEXTO_ICONES)) / 2;
    int flag = 0;

    int x = RY + 2*gap_horizontal + DIMENSAO_ICONES;
    int y = RY - gap_vertical;

    texto.tamanho = 100;
    texto.area.a.y = y-DIMENSAO_ICONES;
    texto.area.b.y = y-DIMENSAO_ICONES;
    texto.area.c.y = y;
    texto.area.d.y = y;


    //ICONES

    for (int i = 0; i < 3; i++) {
        texto.area.a.x = x;
        texto.area.b.x = x+TAMANHO_TEXTO_ICONES-2*gap_horizontal;
        texto.area.c.x = x+TAMANHO_TEXTO_ICONES-2*gap_horizontal;
        texto.area.d.x = x;
        switch (flag) {
            case 0:
                texto.string = "99999";
                texto.r = 128;
                texto.g = 0;
                texto.b = 0;
                break;
            case 1:
                texto.string = "99999";
                texto.r = 0;
                texto.g = 0;
                texto.b = 0;
                break;
            case 2:
                texto.string = "99999";
                texto.r = 0;
                texto.g = 0;
                texto.b = 128;
                break;
        }

        carrega_texto(texto);

        //PREPARANDO PROXIMO ICONE
        x += DIMENSAO_ICONES + TAMANHO_TEXTO_ICONES;
        flag++;
    }


    return 0;
}

int carrega_display_recursos (imagens_data imagens, texto_data texto) {
    //  NÃO PODE SER MAIOR QUE A LARGURA
     //  NÃO PODE SER MAIOR QUE RX-RY-DIMENSAO_ICONES
    int gap_vertical = (DIVISAO_INFERIOR - DIMENSAO_ICONES) / 2;
    int gap_horizontal = ((RX-RY) - (3 * DIMENSAO_ICONES) - (3 * TAMANHO_TEXTO_ICONES)) / 2;
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
        glTexCoord2d(0,0);  glVertex2f(x, y-DIMENSAO_ICONES); // primeiro ponto
        glTexCoord2d(1,0);  glVertex2f(x+DIMENSAO_ICONES, y-DIMENSAO_ICONES); // segundo ponto
        glTexCoord2d(1,1);  glVertex2f(x+DIMENSAO_ICONES, y);
        glTexCoord2d(0,1);  glVertex2f(x, y);
        glEnd();

        //PREPARANDO PROXIMO ICONE
        x += DIMENSAO_ICONES + TAMANHO_TEXTO_ICONES;
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

//CARREGA_TEXTO NÃO ESTÁ 100% FUNCIONAL

int carrega_texto(texto_data texto) {

    //unsigned int teste = importText(texto.string,texto.tamanho,texto.r,texto.g,texto.b);   

    glColor4ub(255, 255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, texto.imagem_prov);

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  glVertex2f(texto.area.a.x, texto.area.a.y); // primeiro ponto
    glTexCoord2d(1,0);  glVertex2f(texto.area.b.x, texto.area.b.y); // segundo ponto
    glTexCoord2d(1,1);  glVertex2f(texto.area.c.x, texto.area.c.y);
    glTexCoord2d(0,1);  glVertex2f(texto.area.d.x, texto.area.d.y);
    glEnd();

    //glDeleteTextures(1, &teste);

}