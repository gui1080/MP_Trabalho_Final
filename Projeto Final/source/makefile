GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include

IDIR =../include
CC=gcc
CCPLUS=g++
CFLAGS=-I $(IDIR) -I $(GL_INCLUDE)
G_FLAGS=-I $(IDIR) -I $(GOOGLE_TEST_INCLUDE)
LD_FLAGS=-I $(IDIR) -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread
FT_FLAGS= -g -ftest-coverage -fprofile-arcs
SDL_FLAGS=-l SDLmain -l SDL -l GL -l SDL_image -l SDL_ttf

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = funcoes.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o criacao.o interface.o verificacao.o interacoes.o cpu.o salva_carrega.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJT = testa_main.o criacao.o interface.o verificacao.o interacoes.o cpu.o salva_carrega.o
OBJT = $(patsubst %,$(ODIR)/%,$(_OBJT))

all: jogo testa_jogo

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(FT_FLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CCPLUS) -c -o $@ $< $(G_FLAGS) $(SDL_FLAGS) $(FT_FLAGS)

jogo: $(OBJ)
	$(CCPLUS) -o $@ $^ $(CFLAGS) $(LIBS) $(LD_FLAGS) $(SDL_FLAGS) $(FT_FLAGS) 

testa_jogo: $(OBJT)
	$(CCPLUS) -o $@ $^ $(LD_FLAGS) $(SDL_FLAGS) $(FT_FLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
