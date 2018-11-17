#include <gtest/gtest.h>
#include "funcoes.h"


TEST(Testa, cria_mapa) {
	cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    ASSERT_EQ(0, cria_mapa(mapa));
}

/*
TEST(Testa, cria_interface) {
	cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
	unsigned int textura_grade = 0;
    unsigned int textura_fundo = 0;
    textura_grade = loadTexture("grade.png");
    textura_fundo = loadTexture("sand.png");
    
    imagens_data imagens; 
    mouse_data mouse;
   	
   	imagens.textura_grade = textura_grade;
    imagens.textura_fundo = textura_fundo;

    mouse.x = 200;
    mouse.y = 200;

    ASSERT_EQ(0, carrega_interface(mapa, imagens, mouse));
}
*/


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
