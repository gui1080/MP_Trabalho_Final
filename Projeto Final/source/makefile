GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include

IDIR =../include
CC=gcc
CCPLUS=g++	
CFLAGS=-I $(IDIR)
G_FLAGS=-I $(IDIR) -I $(GOOGLE_TEST_INCLUDE)
LD_FLAGS=-I $(IDIR) -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread
FT_FLAGS=-I $(IDIR) -g -ftest-coverage -fprofile-arcs
SDL_FLAGS=-I $(IDIR) -l SDLmain -l SDL -l GL -l SDL_image

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = funcoes.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o funcoes.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJT = testa_main.o funcoes.o
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
