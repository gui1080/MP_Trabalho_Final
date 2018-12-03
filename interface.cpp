/**
 * @file interface.cpp
 *
 * @brief Arquivo com a aplicação das funções da interface do jogo
 *
 * @author Grupo 2
 *
 */


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

int carrega_interface(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data *mouse, texto_data texto, player_data *player, atributos_data atributos) {

    //  cria matriz
    glPushMatrix();

    // dimensoes da matriz
    glOrtho(0, RX, RY, 0, -1, 1); 

    carrega_layout();
    carrega_caixa(mapa, mouse, imagens, texto, atributos, player);

    //  CARREGA ESTRUTURAS E ICONES
    glEnable(GL_TEXTURE_2D);

    carrega_display_recursos(imagens, texto);
    carrega_mapa(mapa, imagens, *mouse);
    carrega_base(mapa, imagens);
    carrega_uni_estatico(mapa, imagens, texto);  
    carrega_uni_movel(mapa, imagens, texto);
    carrega_numeros_recurso (texto, player);
    carrega_barras(imagens);
    carrega_comandante(imagens);

    // fecha matriz
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    if (verifica_selecao(mapa, *mouse) != 0) {
        colore_espacos_validos(mapa, mapa[mouse->y/LADO][mouse->x/LADO].pUniMovel, player);
        colore_espacos_validos_defesa(mapa, mapa[mouse->y/LADO][mouse->x/LADO].pUniImovel, player);
    }

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

    glVertex2f(RY,RY-DIVISAO_INFERIOR-LARGURA_BARRAS);
    glVertex2f(RX,RY-DIVISAO_INFERIOR-LARGURA_BARRAS);

    glVertex2f(RY,RY-DIVISAO_INFERIOR-2*LARGURA_BARRAS);
    glVertex2f(RX,RY-DIVISAO_INFERIOR-2*LARGURA_BARRAS);

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
                	//printf("UNID. MOVEL\n");
                } else {
                    //printf("TERRENO\n");
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


int carrega_numeros_recurso (texto_data texto, player_data *player) {
    int gap_vertical = (DIVISAO_INFERIOR - DIMENSAO_ICONES) / 2;
    int gap_horizontal = ((RX-RY) - (3 * DIMENSAO_ICONES) - (3 * TAMANHO_TEXTO_ICONES)) / 2;
    int flag = 0;

    int x = RY + 2*gap_horizontal + DIMENSAO_ICONES;
    int y = RY - gap_vertical;

    int numero;
    //ICONES

    for (int i = 0; i < 3; i++) {
        switch (flag) {
            case 0:
                numero = player->comida;
                glColor4ub(128, 0, 0, 255);
            break;
            case 1:
                glColor4ub(0, 0, 0, 255);
                numero = player->minerio;
            break;
            case 2:
                numero = player->eletricidade;
                glColor4ub(0, 0, 128, 255);
            break;
        }

        glBindTexture(GL_TEXTURE_2D, texto.numero_textura[numero]);

        glBegin(GL_QUADS);
        glTexCoord2d(0,0);  glVertex2f(x, y-DIMENSAO_ICONES); // primeiro ponto
        glTexCoord2d(1,0);  glVertex2f(x+TAMANHO_TEXTO_ICONES-2*gap_horizontal, y-DIMENSAO_ICONES); // segundo ponto
        glTexCoord2d(1,1);  glVertex2f(x+TAMANHO_TEXTO_ICONES-2*gap_horizontal, y);
        glTexCoord2d(0,1);  glVertex2f(x, y);
        glEnd();

        //PREPARANDO PROXIMO ICONE
        x += DIMENSAO_ICONES + TAMANHO_TEXTO_ICONES;
        flag++;
    }


    return 0;
}

int carrega_display_recursos (imagens_data imagens, texto_data texto) {
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

                    if (mapa[i][j].pBase->time == ALIADO) 
                        glColor4ub(255, 255, 255, 255); 
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

int carrega_uni_estatico(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, texto_data texto) {

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pUniImovel != NULL) {
                if (mapa[i][j].pUniImovel->i == i && mapa[i][j].pUniImovel->j == j) {
                    if (mapa[i][j].pUniImovel->time == ALIADO) 
                        glColor4ub(255, 255, 255, 255); 
                    else 
                        glColor4ub(255, 179, 179, 255);

                        escolhe_imagem_estatica(mapa, imagens, i, j, 0, texto);               
                        
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

int escolhe_imagem_estatica(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, int i, int j, int opcao, texto_data texto) {
    switch (mapa[i][j].pUniImovel->divisao) {
        case HUMANO:
            switch (mapa[i][j].pUniImovel->classe) {
                case GERADOR_DE_RECURSO:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.humano_GER_REC);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[GERADOR_DE_COMIDA]);
                break;
                case GERADOR_DE_TROPA:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.humano_GER_TROP);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[GERADOR_DE_TROPA_HUMANA]);
                break;
                case DEFESA_OFENSIVA:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.humano_DEF_OFS);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[TORRE_TIPO_HUMANO]);
                break;
                case DEFESA_PASSIVA:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.humano_DEF_PAS);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[DEFESA_PASSIVA]);
                break;
            }
            break;
        case MECANICO:
            switch (mapa[i][j].pUniImovel->classe) {
                case GERADOR_DE_RECURSO:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.mecanico_GER_REC);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[GERADOR_DE_MINERIO]);
                break;
                case GERADOR_DE_TROPA:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.mecanico_GER_TROP);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[GERADOR_DE_TROPA_MECANICA]);
                break;
                case DEFESA_OFENSIVA:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.mecanico_DEF_OFS);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[TORRE_TIPO_MECANICO]);
                break;
                case DEFESA_PASSIVA:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.mecanico_DEF_PAS);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[DEFESA_PASSIVA]);
                break;
            }
        break;
        case ELETRICO:
            switch (mapa[i][j].pUniImovel->classe) {
                case GERADOR_DE_RECURSO:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.eletrico_GER_REC);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[GERADOR_DE_ELETRICIDADE]);
                break;
                case GERADOR_DE_TROPA:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.eletrico_GER_TROP);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[GERADOR_DE_TROPA_MECANICA]);
                break;
                case DEFESA_OFENSIVA:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.eletrico_DEF_OFS);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[TORRE_TIPO_ELETRICO]);
                break;
                case DEFESA_PASSIVA:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.eletrico_DEF_PAS);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[DEFESA_PASSIVA]);
                break;
            }
        break;
    } 
}

int carrega_uni_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, texto_data texto) {

    for (int i = 0; i < BLOCOS_LINHA; i++) {
        for (int j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pUniMovel != NULL) {
                if (mapa[i][j].pUniMovel->i == i && mapa[i][j].pUniMovel->j == j) {
                    if (mapa[i][j].pUniMovel->time == ALIADO) glColor4ub(255, 255, 255, 255); 
                    else glColor4ub(255, 179, 179, 255);

                    escolhe_imagem_movel(mapa, imagens, texto, i, j, 0);

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

int escolhe_imagem_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, texto_data texto, int i, int j, int opcao) {
    switch (mapa[i][j].pUniMovel->divisao) {
        case HUMANO:
            switch (mapa[i][j].pUniMovel->nivel) {
                case 1:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.mercenario);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[MERCENARIOS]);
                break;
                case 2:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.cavaleiro_estelar);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[CAVALEIROS]);
                break;
                case 3:
                    if (!opcao)glBindTexture(GL_TEXTURE_2D, imagens.choris);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[CHORIS]);
                break;
            }
        break;
        case MECANICO:
            switch (mapa[i][j].pUniMovel->nivel) {
                case 1:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.wall_e);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[WALL]);
                break;
                case 2:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.droids);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[DROIDES]);
                break;
                case 3:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.iron_giant);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[IRON]);
                break;
            }
        break;
        case ELETRICO:
            switch (mapa[i][j].pUniMovel->nivel) {
                case 1:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.replicantes);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[REPLICANTE]);
                break;
                case 2:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.exterminador);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[EXTERMINADOR]);
                break;
                case 3:
                    if (!opcao)glBindTexture(GL_TEXTURE_2D, imagens.hatsune);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[HATSUNE]);
                break;
            }
        break;
        case OPERARIO:
                    if (!opcao) glBindTexture(GL_TEXTURE_2D, imagens.operario);
                    else glBindTexture(GL_TEXTURE_2D, texto.nome_textura[OPERARIO]);
        break;

    }  
}

int carrega_barras(imagens_data imagens) {

    glDisable(GL_TEXTURE_2D);
    glColor4ub(32, 200, 32, 255);

    int exp_neg = 60;
    int vida_neg = 30;

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  glVertex2f(RY+1, RY-DIVISAO_INFERIOR-LARGURA_BARRAS); // primeiro ponto
    glTexCoord2d(1,0);  glVertex2f(RX-exp_neg, RY-DIVISAO_INFERIOR-LARGURA_BARRAS); // segundo ponto
    glTexCoord2d(1,1);  glVertex2f(RX-exp_neg, RY-DIVISAO_INFERIOR-1);
    glTexCoord2d(0,1);  glVertex2f(RY+1, RY-DIVISAO_INFERIOR-1);
    glEnd();   

    glColor4ub(204, 0, 0, 255);

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  glVertex2f(RY+1, RY-DIVISAO_INFERIOR-2*LARGURA_BARRAS); // primeiro ponto
    glTexCoord2d(1,0);  glVertex2f(RX-vida_neg, RY-DIVISAO_INFERIOR-2*LARGURA_BARRAS); // segundo ponto
    glTexCoord2d(1,1);  glVertex2f(RX-vida_neg, RY-DIVISAO_INFERIOR-LARGURA_BARRAS-1);
    glTexCoord2d(0,1);  glVertex2f(RY+1, RY-DIVISAO_INFERIOR-LARGURA_BARRAS-1);
    glEnd();
    glEnable(GL_TEXTURE_2D);

}

int carrega_comandante(imagens_data imagens) {

    glBindTexture(GL_TEXTURE_2D, imagens.comandante);
    glColor4ub(255, 255, 255, 255);

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  glVertex2f(RY+TRANSLADA_COMANDANTE+1, RY-DIVISAO_INFERIOR-2*LARGURA_BARRAS-DIMENSAO_COMANDANTE); // primeiro ponto
    glTexCoord2d(1,0);  glVertex2f(RY+TRANSLADA_COMANDANTE+DIMENSAO_COMANDANTE, RY-DIVISAO_INFERIOR-2*LARGURA_BARRAS-DIMENSAO_COMANDANTE); // segundo ponto
    glTexCoord2d(1,1);  glVertex2f(RY+TRANSLADA_COMANDANTE+DIMENSAO_COMANDANTE, RY-DIVISAO_INFERIOR-2*LARGURA_BARRAS-1);
    glTexCoord2d(0,1);  glVertex2f(RY+TRANSLADA_COMANDANTE+1, RY-DIVISAO_INFERIOR-2*LARGURA_BARRAS-1);
    glEnd();

}

int carrega_caixa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data *mouse, imagens_data imagens, texto_data texto, atributos_data atributos, player_data *player) {

    //printf("x_mem: %d\n", mouse.x_mem);
    //printf("y_mem: %d\n", mouse.y_mem);

    int valor = verifica_selecao(mapa, *mouse);
    if (valor == 0)
        return 0;    

    int gap_x = 0.02 * RX;
    int gap_y = 0.03 * RY;
    int comprimento = 0.3 * RY;
    int tamanho_titulo = 0.05 * RY;
    int tamanho_imagem = comprimento-tamanho_titulo;

    int gap_titulo_x = 0.05 * RX;
    int gap_titulo_y = 0.003 * RY;
    int gap_imagem = 0.02 * RY;

    glColor4ub(0, 0, 0, 255);

    glBegin(GL_LINES);


    glVertex2f(RY+gap_x,gap_y);
    glVertex2f(RX-gap_x,gap_y);

    glVertex2f(RY+gap_x,gap_y);
    glVertex2f(RY+gap_x,comprimento+gap_y);

    glVertex2f(RX-gap_x,gap_y);
    glVertex2f(RX-gap_x,comprimento+gap_y);

    glVertex2f(RY+gap_x,comprimento+gap_y);
    glVertex2f(RX-gap_x,comprimento+gap_y);

    glVertex2f(RY+gap_x,gap_y+tamanho_titulo);
    glVertex2f(RX-gap_x,gap_y+tamanho_titulo);

    glVertex2f(RY+gap_x+tamanho_imagem,gap_y+tamanho_titulo);
    glVertex2f(RY+gap_x+tamanho_imagem,comprimento+gap_y);

    glEnd();

    glColor4ub(0, 0, 0, 255);

    glBegin(GL_QUADS);
    glVertex2f(RY+gap_x,gap_y+tamanho_titulo);
    glVertex2f(RY+gap_x+tamanho_imagem-1,gap_y+tamanho_titulo);
    glVertex2f(RY+gap_x+tamanho_imagem-1,comprimento+gap_y-1);
    glVertex2f(RY+gap_x,comprimento+gap_y-1);
    glEnd();

    glEnable(GL_TEXTURE_2D);

    int i = mouse->y_mem/LADO;
    int j = mouse->x_mem/LADO;

    switch (valor) {
        case 1:
            escolhe_imagem_movel(mapa, imagens, texto, i, j, 1);
        break;
        case 2:
            escolhe_imagem_estatica(mapa, imagens, i, j, 1, texto);
        break;
        case 3:
            glBindTexture(GL_TEXTURE_2D, texto.nome_textura[BASE]);
            gap_titulo_x = 2.5 * tamanho_titulo;
            break;
        case 0:
            return 0;
    }
    glColor4ub(0, 0, 0, 255);

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  glVertex2f(RY+gap_x+gap_titulo_x, gap_y+gap_titulo_y); // primeiro ponto
    glTexCoord2d(1,0);  glVertex2f(RX-gap_x-gap_titulo_x, gap_y+gap_titulo_y); // segundo ponto
    glTexCoord2d(1,1);  glVertex2f(RX-gap_x-gap_titulo_x, gap_y+tamanho_titulo-gap_titulo_y);
    glTexCoord2d(0,1);  glVertex2f(RY+gap_x+gap_titulo_x, gap_y+tamanho_titulo-gap_titulo_y);
    glEnd();

    if (valor == 1) escolhe_imagem_movel(mapa, imagens, texto, i, j, 0);
    if (valor == 2) escolhe_imagem_estatica(mapa, imagens, i, j, 0, texto);
    if (valor == 3) glBindTexture(GL_TEXTURE_2D, imagens.textura_base); 

    glColor4ub(255, 255, 255, 255);

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  glVertex2f(RY+gap_x+gap_imagem,gap_y+tamanho_titulo+gap_imagem);
    glTexCoord2d(1,0);  glVertex2f(RY+gap_x+tamanho_imagem-gap_imagem,gap_y+tamanho_titulo+gap_imagem);
    glTexCoord2d(1,1);  glVertex2f(RY+gap_x+tamanho_imagem-gap_imagem,comprimento+gap_y-gap_imagem);
    glTexCoord2d(0,1);  glVertex2f(RY+gap_x+gap_imagem,comprimento+gap_y-gap_imagem);
    glEnd();    

    //CARREGA BOTOES
    
    if (valor == 1) {
        if (mapa[i][j].pUniMovel->divisao == OPERARIO) {
             if(mouse->botao_mem == -1) {
                carrega_botao(imagens, texto, mouse, 0, CRIAR_GER_REC, mapa, atributos, player);
                carrega_botao(imagens, texto, mouse, 1, CRIAR_GER_TRO, mapa, atributos, player);
                carrega_botao(imagens, texto, mouse, 2, CRIAR_DEFESA, mapa, atributos, player);      
            } else if(mouse->botao_mem == 4)  {

                carrega_botao(imagens, texto, mouse, 0, CRIAR_MUR, mapa, atributos, player);
                carrega_botao(imagens, texto, mouse, 1, CRIAR_DEFESA_OF, mapa, atributos, player);

            } else {
                carrega_botao(imagens, texto, mouse, 0, HUMANO, mapa, atributos, player);
                carrega_botao(imagens, texto, mouse, 1, MECANICO, mapa, atributos, player);
                carrega_botao(imagens, texto, mouse, 2, ELETRICO, mapa, atributos, player);
            } 
        }
    }

    if (valor == 2) {
        if(mouse->botao_mem == -1) {

        if(player->nivel <= mapa[i][j].pUniImovel->nivel){

        carrega_botao(imagens, texto, mouse, 0, EVOLUIR_NIVEL_INSUFICIENTE, mapa, atributos, player);   

        } else {   

        if (mapa[i][j].pUniImovel->nivel < 3) {

        carrega_botao(imagens, texto, mouse, 0, EVOLUIR, mapa, atributos, player);

        } else {

        carrega_botao(imagens, texto, mouse, 0, NIVEL_MAXIMO, mapa, atributos, player);

        }

    }

        if (mapa[i][j].pUniImovel->classe == GERADOR_DE_TROPA) {

                carrega_botao(imagens, texto, mouse, 1, GERAR_TROPA, mapa, atributos, player);
   
        } 

    }  else {

        carrega_botao(imagens, texto, mouse, 0, NIVEL_1, mapa, atributos, player);

        if (mapa[i][j].pUniImovel->nivel >= 2){

        carrega_botao(imagens, texto, mouse, 1, NIVEL_2, mapa, atributos, player);
            
        }

        if (mapa[i][j].pUniImovel->nivel == 3){

        carrega_botao(imagens, texto, mouse, 2, NIVEL_3, mapa, atributos, player);

        }

    }
    }
        
    if (valor == 3) carrega_botao(imagens, texto, mouse, 0, GERAR_OPERARIO, mapa, atributos, player);

    glDisable(GL_TEXTURE_2D);
}

int carrega_botao(imagens_data imagens, texto_data texto, mouse_data *mouse, int local, int tipo, cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player) {

    int posicao_comeco;
    int botao_largura = 0.06 * RY;
    int dimensao_icones = 0.03 * RY;
    int gap_y = 0.025 * RY;

    posicao_comeco = 0.33 * RY;

    for (int i = 0; i<local; i++) {
        posicao_comeco += botao_largura+dimensao_icones+gap_y;        
    }

    int gap_x = 0.02 * RX;
    posicao_comeco += gap_y;

    glColor4ub(255, 255, 255, 255);

    //BOTÃO

    if (mouse->x_agr > RY+gap_x && mouse->x_agr < RX-gap_x && mouse->y_agr > posicao_comeco && mouse->y_agr < posicao_comeco+botao_largura) {
        glBindTexture(GL_TEXTURE_2D, imagens.botao2);
        if (mouse->x_botao > RY+gap_x && mouse->x_botao < RX-gap_x && mouse->y_botao > posicao_comeco && mouse->y_botao < posicao_comeco+botao_largura) {        
            switch (tipo) {

                    if (mouse->botao_mem == 0) {
                    case CRIAR_GER_REC:
                        mouse->botao_mem = 1;
                        printf("gera recurso\n");
                    break;
                    case CRIAR_GER_TRO:
                        mouse->botao_mem = 2;
                        printf("gera tropa\n");
                    break;
                    case CRIAR_DEFESA:

                        mouse->botao_mem = 4;

                    /*
                    if (mouse->botao_mem != 1){

                        printf("gera muralha\n");
                    

                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = DEFESA_PASSIVA;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);

                        }
                    */  
                        //funcao

                    break;
                    case GERAR_OPERARIO:
                        //funcao
                        gera_operario(mapa, mouse, atributos, player);
                        printf("gera operario\n");
                    break;

                    case EVOLUIR:

                    if (mouse->botao_mem != 1){
                        
                        unidade_estatica *aux = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel;

                        evolution(aux , player);

                        }

                    break;

                    case GERAR_TROPA:
                    mouse->botao_mem = 3;
                    break;

                } else {
                    printf("ok\n");
                    case HUMANO:
                        if (mouse->botao_mem == 1){
                            //funcao
                            printf("gera ger recurso tipo humano\n");
    
                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = GERADOR_DE_RECURSO;
                        atributos.divisao = HUMANO;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);
                        
                        }

                        else if (mouse->botao_mem == 5){
    
                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = DEFESA_OFENSIVA;
                        atributos.divisao = HUMANO;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);
                        
                        }

                        else{
                            //funcao
                            printf("gera ger tropa tipo humano\n");

                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = GERADOR_DE_TROPA;
                        atributos.divisao = HUMANO;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);
                        }

                    mouse->botao_mem = -1;
                    break;
                    case MECANICO:
                        if (mouse->botao_mem == 1){
                            //funcao
                            printf("gera ger recurso tipo mecanico\n");
                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = GERADOR_DE_RECURSO;
                        atributos.divisao = MECANICO;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);
                        }

                        else if (mouse->botao_mem == 5){
    
                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = DEFESA_OFENSIVA;
                        atributos.divisao = MECANICO;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);
                        
                        }

                        else{
                            //funcao
                            printf("gera ger tropa tipo mecanico\n");

                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = GERADOR_DE_TROPA;
                        atributos.divisao = MECANICO;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);

                        }
                    mouse->botao_mem = -1;
                    break;
                    case ELETRICO:
                        if (mouse->botao_mem == 1){
                            //funcao
                            printf("gera ger recurso tipo eletrico\n");
                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = GERADOR_DE_RECURSO;
                        atributos.divisao = ELETRICO;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);
                        
                        }

                        else if (mouse->botao_mem == 5){
    
                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = DEFESA_OFENSIVA;
                        atributos.divisao = ELETRICO;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);
                        
                        }

                        else{
                            //funcao
                            printf("gera ger tropa tipo eletrico\n");

                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = GERADOR_DE_TROPA;
                        atributos.divisao = ELETRICO;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);

                        }
                    mouse->botao_mem = -1;
                    break;

                    case NIVEL_1:
                        if (mouse->botao_mem == 3){
                            //funcao
                        printf("gera unidade nivel 1\n");

                        unidade_estatica *aux = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel;
                        atributos.divisao = aux->divisao;
                        atributos.nivel = 1;

                        gera_tropa(mapa, mouse, atributos, player);

                        
                        }
                    mouse->botao_mem = -1;
                    break;

                    case NIVEL_2:
                        if (mouse->botao_mem == 3){
                            //funcao
                        printf("gera unidade nivel 1\n");

                        unidade_estatica *aux = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel;
                        atributos.divisao = aux->divisao;
                        atributos.nivel = 2;

                        gera_tropa(mapa, mouse, atributos, player);

                        
                        }
                    mouse->botao_mem = -1;
                    break;

                    case NIVEL_3:
                        if (mouse->botao_mem == 3){
                            //funcao
                        printf("gera unidade nivel 1\n");

                        unidade_estatica *aux = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniImovel;
                        atributos.divisao = aux->divisao;
                        atributos.nivel = 3;

                        gera_tropa(mapa, mouse, atributos, player);

                        
                        }
                    mouse->botao_mem = -1;
                    break;

                    case CRIAR_MUR:
                    if (mouse->botao_mem != 1){

                        printf("gera muralha\n");
                    

                        int x_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->i;
                        int y_c = mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel->j;

                        mapa[mouse->y_mem/LADO][mouse->x_mem/LADO].pUniMovel = NULL;

                        atributos.classe = DEFESA_PASSIVA;
                        cria_uni_estatico(mapa, x_c, y_c, atributos, player);

                        }
                        mouse->botao_mem = -1;
                        break;

                    case CRIAR_DEFESA_OF:
                    mouse->botao_mem = 5;
                    break;    

                }
            }
            //printf("oi querida\n");
            mouse->x_botao = -1;
            mouse->y_botao = -1;
        }
    } else {
        glBindTexture(GL_TEXTURE_2D, imagens.botao1);
    }

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  glVertex2f(RY+gap_x,posicao_comeco);
    glTexCoord2d(1,0);  glVertex2f(RX-gap_x,posicao_comeco);
    glTexCoord2d(1,1);  glVertex2f(RX-gap_x,posicao_comeco+botao_largura);
    glTexCoord2d(0,1);  glVertex2f(RY+gap_x,posicao_comeco+botao_largura);
    glEnd();

    glColor4ub(0, 0, 0, 255);

    //TEXTO BOTÃO

    int gap_texto = 0.2 * botao_largura;

    glBindTexture(GL_TEXTURE_2D, texto.nome_textura[tipo]);

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  glVertex2f(RY+gap_x+2*gap_texto,posicao_comeco+gap_texto);
    glTexCoord2d(1,0);  glVertex2f(RX-gap_x-2*gap_texto,posicao_comeco+gap_texto);
    glTexCoord2d(1,1);  glVertex2f(RX-gap_x-2*gap_texto,posicao_comeco+botao_largura-gap_texto);
    glTexCoord2d(0,1);  glVertex2f(RY+gap_x+2*gap_texto,posicao_comeco+botao_largura-gap_texto);
    glEnd();

    //TEXTO CUSTO

    int gap_cust_x = 0.02 * RX;
    int x = RY + gap_x + gap_cust_x;
    int y = posicao_comeco + botao_largura;
    int tam_texto_cust_x = 0.06 * RX;
    int tam_texto_cust_y = dimensao_icones;

    glColor4ub(48, 38, 128, 255);
    
    glBindTexture(GL_TEXTURE_2D, texto.nome_textura[CUSTO]);

    glBegin(GL_QUADS);
    glTexCoord2d(0,0);  glVertex2f(x,y);
    glTexCoord2d(1,0);  glVertex2f(x+tam_texto_cust_x,y);
    glTexCoord2d(1,1);  glVertex2f(x+tam_texto_cust_x,y + tam_texto_cust_y);
    glTexCoord2d(0,1);  glVertex2f(x,y + tam_texto_cust_y);
    glEnd();

    //RECURSOS NECESSÁRIOS

    int flag = 0;
    int tamanho_texto_icones = 0.04 * RX;
    int gap_inicio_rec = 0.5 * gap_cust_x;
    x += tam_texto_cust_x + gap_inicio_rec;  

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
        glTexCoord2d(0,0);  glVertex2f(x, y); // primeiro ponto
        glTexCoord2d(1,0);  glVertex2f(x+dimensao_icones, y); // segundo ponto
        glTexCoord2d(1,1);  glVertex2f(x+dimensao_icones, y+tam_texto_cust_y);
        glTexCoord2d(0,1);  glVertex2f(x, y+tam_texto_cust_y);
        glEnd();

        //PREPARANDO PROXIMO ICONE
        x += dimensao_icones + tamanho_texto_icones;
        flag++;
    }

    //CARREGA NUMEROS

    int numero;
    flag = 2;

    int gap_texto_num = 0.005 * RX;
    x -= tamanho_texto_icones;

    for (int i = 0; i < 3; i++) {
        switch (flag) {
            case 0:
                numero = 2;
                glColor4ub(128, 0, 0, 255);
            break;
            case 1:
                numero = 13;
                glColor4ub(0, 0, 0, 255);
            break;
            case 2:
                numero = 22;
                glColor4ub(0, 0, 128, 255);
            break;
        }

        glBindTexture(GL_TEXTURE_2D, texto.numero_textura[numero]);

        glBegin(GL_QUADS);
        glTexCoord2d(0,0);  glVertex2f(x+gap_texto_num, y); // primeiro ponto
        glTexCoord2d(1,0);  glVertex2f(x+tamanho_texto_icones-2*gap_texto_num, y); // segundo ponto
        glTexCoord2d(1,1);  glVertex2f(x+tamanho_texto_icones-2*gap_texto_num, y+dimensao_icones);
        glTexCoord2d(0,1);  glVertex2f(x+gap_texto_num, y+dimensao_icones);
        glEnd();

        //PREPARANDO PROXIMO ICONE
        x -= dimensao_icones + tamanho_texto_icones;
        flag--;
    }

}


int colore_espacos_validos(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* aux, player_data* player) {

    if (aux == NULL || player->time != aux->time) {
        return 1;
    }

    //  cria matriz
    glPushMatrix();

    // dimensoes da matriz
    glOrtho(0, RX, RY, 0, -1, 1); 

    for (int i = max(aux->i - aux->velocidade, 0); i <= min(aux->i + aux->velocidade, 39); i++) {
        for (int j = max(aux->j - aux->velocidade, 0); j <= min(aux->j + aux->velocidade, 39); j++) {

            glColor4ub(0, 102, 0, 128);

            if (mapa[i][j].pUniMovel == NULL &&
                mapa[i][j].pUniImovel == NULL &&
                mapa[i][j].pBase == NULL) {
                // colore de verde
                glColor4ub(0, 255, 0, 64);
                if(verifica_alcance(aux, i, j)){
                    glColor4ub(0, 0, 255, 64);
                }
            }

            if (mapa[i][j].pUniMovel != NULL) {
                // colore para inimigos e deixa branco para aliados
                if (verifica_oposicao(mapa, aux, i, j)) {
                    glColor4ub(255, 255, 0, 128);
                    if (verifica_alcance(aux, i, j)) {
                        glColor4ub(255, 0, 0, 80);
                    }
                }
            }

            if (mapa[i][j].pUniImovel != NULL) {
                // colore para inimigos e deixa branco para aliados
                if (verifica_oposicao(mapa, aux, i, j)) {
                    glColor4ub(255, 255, 0, 128);
                    if (verifica_alcance(aux, i, j)) {
                        glColor4ub(255, 0, 0, 80);
                    }
                }
            }

            if (mapa[i][j].pBase != NULL) {
                // colore para inimigos e deixa branco para aliados
                if (verifica_oposicao(mapa, aux, i, j)) {
                    glColor4ub(255, 255, 0, 128);
                    if (verifica_alcance(aux, i, j)) {
                        glColor4ub(255, 0, 0, 80);
                    }
                }
            }

            glBegin(GL_QUADS);
            glVertex2f(LADO*j, LADO*i);
            glVertex2f(LADO*(j+1), LADO*i);
            glVertex2f(LADO*(j+1), LADO*(i+1));
            glVertex2f(LADO*j, LADO*(i+1));
            glEnd();
        }
    }

    // fecha matriz
    glPopMatrix();

    return 0;
}

int colore_espacos_validos_defesa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_estatica* aux, player_data* player) {

    if (aux == NULL || player->time != aux->time) {
        return 1;
    }

    //  cria matriz
    glPushMatrix();

    // dimensoes da matriz
    glOrtho(0, RX, RY, 0, -1, 1); 

    for (int i = max(aux->i - aux->alcance, 0); i <= min(aux->i + aux->alcance, 39); i++) {
        for (int j = max(aux->j - aux->alcance, 0); j <= min(aux->j + aux->alcance, 39); j++) {

            glColor4ub(0, 102, 0, 128);

            if (mapa[i][j].pUniMovel == NULL &&
                mapa[i][j].pUniImovel == NULL &&
                mapa[i][j].pBase == NULL) {
                // colore de verde
                glColor4ub(0, 0, 255, 64);
            }

            if (mapa[i][j].pUniMovel != NULL) {
                // colore para inimigos e deixa branco para aliados
                if (verifica_oposicao_defesa(mapa, aux, i, j)) {
                    glColor4ub(255, 255, 0, 128);
                    if (verifica_alcance_defesa(aux, i, j)) {
                        glColor4ub(255, 0, 0, 80);
                    }
                }
            }

            if (mapa[i][j].pUniImovel != NULL) {
                // colore para inimigos e deixa branco para aliados
                if (verifica_oposicao_defesa(mapa, aux, i, j)) {
                    glColor4ub(255, 255, 0, 128);
                    if (verifica_alcance_defesa(aux, i, j)) {
                        glColor4ub(255, 0, 0, 80);
                    }
                }
            }

            if (mapa[i][j].pBase != NULL) {
                // colore para inimigos e deixa branco para aliados
                if (verifica_oposicao_defesa(mapa, aux, i, j)) {
                    glColor4ub(255, 255, 0, 128);
                    if (verifica_alcance_defesa(aux, i, j)) {
                        glColor4ub(255, 0, 0, 80);
                    }
                }
            }

            glBegin(GL_QUADS);
            glVertex2f(LADO*j, LADO*i);
            glVertex2f(LADO*(j+1), LADO*i);
            glVertex2f(LADO*(j+1), LADO*(i+1));
            glVertex2f(LADO*j, LADO*(i+1));
            glEnd();
        }
    }

    // fecha matriz
    glPopMatrix();

    return 0;
}


/*
int mostra_menu(SDL_Surface* screen, TTF_Font* font){
    Uint32 time;
    int x, y;
    const int NUMMENU=2;
    const char* labels[NUMMENU] = {"Continuar",  "Sair"};
    SDL_Surface* menu[NUMMENU];
    bool selected[NUMMENU] = {0, 0}
    SDL_Color color[2] = {{255, 255, 255}, {255, 0, 0}};
    
    menu[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
    menu[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
    
    pos[0].x = 300;
    pos[0].y = 400;
    pos[1].x = 900;
    pos[1].y = 400;
    
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    
    SDL_Event event;
    while(1){
        time = SDL_GetTicks();
        while(SDL_PollEvent(&event)){
            switch(event.type){
                
                case SDL_QUIT:
                    SDL_FreeSurface(menu[0]);
                    SDL_FreeSurface(menu[1]);
                    return 1;
                
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for(int i = 0; i<NUMMENU; i++){
                        if((x>=pos[i].x) && (x<=pos[i].x + pos[i].w) && (y>pos[i].y) && (y<=pos[i].y + pos[i].h)){
                            if(!selected){
                                selected[i] = 1;
                                SDLFreeSurface(menu[i]));
                                menu[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
                            }
                        }else{
                                if(selected[i]){
                                selected[i] = 0;
                                SDLFreeSurface(menu[i]));
                                menu[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
                                }
                            }
                        }
                 // break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for(i = 0; i<NUMMENU ; i++){
                        if((x>=pos[i].x) && (x<=pos[i].x + pos[i].w) && (y>pos[i].y) && (y<=pos[i].y + pos[i].h)){
                           SDL_FreeSurface(menu[0]);
                            SDL_FreeSurface(menu[1]);
                            return i;
                        }
                        break;
                    }
                case SDL_KEYDOWN:
                    if(event.key.keyssym.sym = SDL_ESCAPE){
                        SDL_FreeSurface(menu[0]);
                        SDL_FreeSurface(menu[1]);
                        return 0;
                    }
               }                                        
           }
           
           for(int k = 0; i<NUMMENU; k++){
                SDL_BlitSurface(menu[k], NULL, screen, &pos[k]);
            }
           SDL_Flip(screen);
           if(1000/30 > (SDL_GetTicks()- time)){
               SDL_Delay(1000/3-(SDL_GetTicks()- time));
        }
      }
}

*/


