/**
 * @file testa_main.cpp
 *
 * @brief Arquivo com testes das funções do jogo
 *
 * @author Grupo 2
 *
 */

#include <gtest/gtest.h>
#include "funcoes.h"

TEST(Testa, gtest_instalado) {
    ASSERT_EQ(42, (40 + 2));
}

TEST(Testa, cria_mapa) {
	cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    ASSERT_EQ(0, cria_mapa(mapa));
}

TEST(Testa, foto_existe) {
    ASSERT_EQ(true, verifica_imagem("imagens/grade.png"));
}


TEST(Testa, espaco_verifica) {
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    cria_mapa(mapa);
    ASSERT_EQ(false, verifica_espaco(mapa, 7899, 1234));
}

TEST(Testa, selecao_valida) {
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    cria_mapa(mapa);
    int mouse_x = -1;
    int mouse_y = -1;
    mouse_data mouse;
    mouse.x_mem = 200;
    mouse.y_mem = 200;
    
    ASSERT_EQ(0 , verifica_selecao(mapa, mouse));
}

TEST(Testa, cria_base) {
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    cria_mapa(mapa);
    ASSERT_EQ(0, cria_base(mapa, 5, 5, 10, 42, 0));
}

TEST(Testa, minimo) {
    
    ASSERT_EQ(2, min(2, 8));
}


TEST(Testa, maximo) {
    
    ASSERT_EQ(8, max(2,8));
}

/*
TEST(Testa, cria_interface) {
	cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    cria_mapa(mapa);
  
    imagens_data imagens; 
    
        // pegar textura
    unsigned int textura_grade;
    unsigned int textura_fundo;
    unsigned int textura_base;
    unsigned int menu_principal;

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
    unsigned int operario;

    unsigned int textura_minerio;
    unsigned int textura_raio;
    unsigned int textura_comida;

    unsigned int textura_exp;
    
    textura_grade = loadTexture("imagens/grade.png");
    textura_fundo = loadTexture("imagens/sand.png");
    menu_principal = loadTexture("imagens/menu_principal.png");
    textura_base = loadTexture("imagens/base.png");
    humano_GER_REC = loadTexture("imagens/Akeno.png");
    humano_GER_TROP = loadTexture("imagens/albedo.png");
    humano_DEF_OFS = loadTexture("imagens/chitoge2.png");
    humano_DEF_PAS = loadTexture("imagens/Dva.png");
    mecanico_GER_REC = loadTexture("imagens/Eliza.png");
    mecanico_GER_TROP = loadTexture("imagens/Emilia.png");
    mecanico_DEF_OFS = loadTexture("imagens/Hatsune.png");
    mecanico_DEF_PAS = loadTexture("imagens/Lucy.png");
    eletrico_GER_REC = loadTexture("imagens/megumin.png");
    eletrico_GER_TROP = loadTexture("imagens/Rias.png");
    eletrico_DEF_OFS = loadTexture("imagens/Lucy4.png");
    eletrico_DEF_PAS = loadTexture("imagens/Rias2.png");
    textura_minerio = loadTexture("imagens/minerio.png");
    textura_comida = loadTexture("imagens/comida.png");
    textura_raio = loadTexture("imagens/raio.png");
    operario = loadTexture("imagens/Kuru.png");


    imagens.textura_grade = textura_grade;
    imagens.textura_fundo = textura_fundo;
    imagens.textura_base = textura_base;
    imagens.textura_menu_principal = menu_principal;
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
    imagens.raio = textura_raio;
    imagens.comida = textura_comida;
    imagens.minerio = textura_minerio;
    imagens.operario = operario;
    
    player_data player1;

    player1.comida = 40;
    player1.minerio = 40;
    player1.eletricidade = 40;
    player1.xp = 0;
    player1.nivel = 1;
    player_data *player = &player1;
    
    atributos_data dados_uni;
    dados_uni.classe = GERADOR_DE_RECURSO;
    dados_uni.divisao = HUMANO;
    dados_uni.time = INIMIGO;
    dados_uni.nivel = 1;
    cria_uni_movel(mapa, 5, 5, dados_uni, player);
    
    mouse_data mouse;
   	
   	imagens.textura_grade = textura_grade;
    imagens.textura_fundo = textura_fundo;
    texto_data texto;
    mouse.x = 200;
    mouse.y = 200;

    ASSERT_EQ(0, carrega_interface(mapa, imagens, mouse, texto, player, dados_uni));
}

*/

TEST(Testa, cria_uni_movel) {
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    cria_mapa(mapa);
        
    player_data player1;

    player1.comida = 40;
    player1.minerio = 40;
    player1.eletricidade = 40;
    player1.xp = 0;
    player1.nivel = 1;
    player_data *player = &player1;
    
    
    atributos_data dados_uni;
    dados_uni.classe = GERADOR_DE_RECURSO;
    dados_uni.divisao = HUMANO;
    dados_uni.time = INIMIGO;
    dados_uni.nivel = 1;
    //cria_uni_movel(mapa, 5, 5, dados_uni, player);

    ASSERT_EQ(0, cria_uni_movel(mapa, 1, 1, dados_uni, player));
}

TEST(Testa, cria_uni_movel_espaco_ocupado) {
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    cria_mapa(mapa);
        
    player_data player1;

    player1.comida = 40;
    player1.minerio = 40;
    player1.eletricidade = 40;
    player1.xp = 0;
    player1.nivel = 1;
    player_data *player = &player1;
    
    
    atributos_data dados_uni;
    dados_uni.classe = GERADOR_DE_RECURSO;
    dados_uni.divisao = HUMANO;
    dados_uni.time = INIMIGO;
    dados_uni.nivel = 1;
    cria_uni_movel(mapa, 5, 5, dados_uni, player);

    ASSERT_EQ(-1, cria_uni_movel(mapa, 5, 5, dados_uni, player));
}
 
TEST(Testa, cria_uni_movel_2) {
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    cria_mapa(mapa);
        
    player_data player1;

    player1.comida = 40;
    player1.minerio = 40;
    player1.eletricidade = 40;
    player1.xp = 0;
    player1.nivel = 1;
    player_data *player = &player1;
    
    
    atributos_data dados_uni;
    dados_uni.classe = GERADOR_DE_RECURSO;
    dados_uni.divisao = ELETRICO;
    dados_uni.time = ALIADO;
    dados_uni.nivel = 1;

    ASSERT_EQ(0, cria_uni_movel(mapa, 5, 5, dados_uni, player));
}

TEST(Testa, cria_uni_movel_3) {
    cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    cria_mapa(mapa);
        
    player_data player1;

    player1.comida = 40;
    player1.minerio = 40;
    player1.eletricidade = 40;
    player1.xp = 0;
    player1.nivel = 1;
    player_data *player = &player1;
    
    
    atributos_data dados_uni;
    dados_uni.classe = GERADOR_DE_RECURSO;
    dados_uni.divisao = MECANICO;
    dados_uni.time = ALIADO;
    dados_uni.nivel = 1;

    ASSERT_EQ(0, cria_uni_movel(mapa, 5, 5, dados_uni, player));
}
  
    
    
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
