//  g++ -o main main.cpp -lSDLmain -lSDL -lGL -lSDL_image

#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>
#include "SDL/SDL_image.h"
#include "string"

#define BLOCOS 18 //quantidade

GLuint loadTexture(const std::string&fileName)
{
	SDL_Surface *imagem = IMG_Load(fileName.c_str()); // carrega imagem
	SDL_DisplayFormatAlpha(imagem); // formato alpha
	unsigned objetct(0); // cria textura
	glGenTextures(1, &objetct); // gera textura
	glBindTexture(GL_TEXTURE_2D, objetct); // tipo de textura, 2D

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagem->w, imagem->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagem->pixels);

	SDL_FreeSurface(imagem);

	return objetct;
}

// A - elemento 1 - inimigo
// B - elemento 2 - personagem o outro elemento

bool colisao(float Ax, float Ay, float Acomp, float Aalt, float Bx, float By, float Bcomp, float Balt)
{
	if(Ax > Bx+Bcomp) return false;	
	else if(Ax+Acomp < Bx) return false;
	else if (Ay+Aalt < By) return false;
	else if(Ay > By+Balt) return false; 

	return true; // houve colisao	
}

struct Bloco
{
	float x;
	float y;
	float comp;
	float alt;
	bool vivo;
};

int main(int argc, char* args[])
{
	
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
	SDL_SetVideoMode(600, 400, 32, SDL_OPENGL);

	// cor
	glClearColor(1,1,1,1);

	// area exibida
	glViewport(0,0,600,400);

	// sombra
	glShadeModel(GL_SMOOTH);

	// 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // desenho geometrico

	//3D
	glDisable(GL_DEPTH_TEST);

	// para uso da imagem
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bool executando = true;

	SDL_Event eventos;
 
 	// personagem
	float personX = 5;
	float personY = 185;
	float personComp = 50;
	float personAlt = 60;

	// inimigo
	float inimigoX = 60;
	float inimigoY = 200;
	float inimigoCA = 30;

	float velX = 3;
	float velY = 3;

	Bloco blocos[BLOCOS];

	// criacao dos blocos

	for (int n = 0, x = 450, y = 2; n < BLOCOS; n++, y += 66)
	{
		if (y > 360)
		{
			x += 21;
			y = 2;
		}

		blocos[n].x = x;
		blocos[n].y = y;
		blocos[n].comp = 20;
		blocos[n].alt = 65;
		blocos[n].vivo = true;
	}

	bool sobe = false, desce = false;

	unsigned int person_textura = 0;
	person_textura = loadTexture("sand.png");

	// loop do jogo
	while(executando)
	{
		// eventos
		while(SDL_PollEvent(&eventos))
		{
			// fecha com o x da janela
			if(eventos.type == SDL_QUIT)
			{
				executando = false;
			}

			// esc
			if (eventos.type == SDL_KEYUP && eventos.key.keysym.sym == SDLK_ESCAPE)
			{
				executando = false;
			}

			// anda ou nao
			if (eventos.type == SDL_KEYDOWN)// tecla pressionada
			{
				if (eventos.key.keysym.sym == SDLK_UP)
				{
					sobe = true;
				}
				else if (eventos.key.keysym.sym == SDLK_DOWN)
				{
					desce = true;
				}
			}
			else if (eventos.type == SDL_KEYUP)
			{
				if (eventos.key.keysym.sym == SDLK_UP)
				{
					sobe = false;
				}
				else if (eventos.key.keysym.sym == SDLK_DOWN)
				{
					desce = false;
				}
			}
		}

		// LOGICA

		// movimento do personagem
		if (sobe == true)// se seta esquerda for pressionada
		{
			personY -= 8;
		}
		else if (desce == true)
		{
			personY += 8;
		}

		if (personY < 0)
		{
			personY = 0;
		}
		else if (personY + personAlt > 400)
		{
			personY = 400 - personAlt;
		}

		// movimento inimigo
		inimigoX += velX;

		for (int n = 0; n < BLOCOS; n++)
		{
			if (blocos[n].vivo == true)
			{
				if (colisao(inimigoX, inimigoY, inimigoCA, inimigoCA, blocos[n].x, blocos[n].y, blocos[n].comp, blocos[n].alt) == true)
				{
					velX = -velX;
					blocos[n].vivo = false;
					break;
				}
			}
		}

		inimigoY -= velY;

		for (int n = 0; n < BLOCOS; n++)
		{
			if (blocos[n].vivo == true)
			{
				if (colisao(inimigoX, inimigoY, inimigoCA, inimigoCA, blocos[n].x, blocos[n].y, blocos[n].comp, blocos[n].alt) == true)
				{
					velY = -velY;
					blocos[n].vivo = false;
					break;
				}
			}
		}

		// logica inimigo
		if (inimigoX < 0)
		{
			velX = -velX;
		}
		else if (inimigoX + inimigoCA > 600)
		{
			velX = -velX;
		}
		else if (inimigoY < 0)
		{
			velY = -velY;
		}
		else if (inimigoY + inimigoCA > 400)
		{
			velY = -velY;
		}

		if (colisao(inimigoX, inimigoY, inimigoCA, inimigoCA, personX, personY, personComp, personAlt) == true)
		{
			velX = -velX;
		}

		// RENDERIZACAO
		glClear(GL_COLOR_BUFFER_BIT);// LIMPA O BUFFER

		// inicia matriz
		glPushMatrix();

		// dimensoes da matriz
		glOrtho(0, 600, 400, 0, -1, 1);

		//cor
		//glColor3d( 1 ou 0)
		//glColor3f( decimais )
		//glColor3ub( R, G, B ) - 0 ATE 255
		//glColor4ub(R, G, B, A) 0 ATE 255

		glColor4ub(255, 255, 255, 255); // branco

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, person_textura);
		 
		// inicia desenho do personagem
		glBegin(GL_QUADS); // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

		glTexCoord2d(0,0);			glVertex2f(personX, personY); // primeiro ponto
		glTexCoord2d(1,0);			glVertex2f(personX+personComp, personY); // segundo ponto
		glTexCoord2d(1,1);			glVertex2f(personX+personComp, personY+personAlt);
		glTexCoord2d(0,1);			glVertex2f(personX, personY+personAlt);

		// fecha
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glColor4ub(0, 255, 0, 255);

		// inicia o desenho do inimigo
		glBegin(GL_QUADS); // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

		glVertex2f(inimigoX, inimigoY); // primeiro ponto
		glVertex2f(inimigoX+inimigoCA, inimigoY); // segundo ponto
		glVertex2f(inimigoX+inimigoCA, inimigoY+inimigoCA);
		glVertex2f(inimigoX, inimigoY+inimigoCA);

		// fecha
		glEnd();

		glBegin(GL_QUADS);

		glColor4ub(0, 0, 255, 255);

		for (int n = 0; n < BLOCOS; n++)
		{
			if (blocos[n].vivo == true)
			{
				glVertex2f(blocos[n].x, blocos[n].y);
				glVertex2f(blocos[n].x + blocos[n].comp, blocos[n].y);
				glVertex2f(blocos[n].x + blocos[n].comp, blocos[n].y + blocos[n].alt);
				glVertex2f(blocos[n].x, blocos[n].y + blocos[n].alt);
			}	
		}

		glEnd();

		// fecha matrix
		glPopMatrix();

		//animacao
		SDL_GL_SwapBuffers();

	}
	

	printf("\n Executando \n");

	SDL_Quit();	

	return 0;
}