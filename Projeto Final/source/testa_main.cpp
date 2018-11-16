#include <gtest/gtest.h>
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>
#include "SDL/SDL_image.h"
#include "string"
#include "funcoes.h"

TEST(Testa, cria_mapa) {
	cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    ASSERT_EQ(0, carrega_mapa(mapa, RY, LADO));
}

TEST(Testa, cria_interface) {
	cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA];
    ASSERT_EQ(0, carrega_interface(mapa));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
