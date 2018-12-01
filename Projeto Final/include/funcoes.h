/**
 * @file headers.h
 *
 * @brief Arquivo com a declaração das funções do jogo
 *
 * @author Grupo 2
 *
 */

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"
#include "string"

#define RX 900
#define RY 600
#define BLOCOS_LINHA 40
#define DIMENSAO_COMANDANTE 0.2 * RY
#define TRANSLADA_COMANDANTE 0.02 * RX
#define DIVISAO_INFERIOR 0.08 * RY
#define DIMENSAO_ICONES 0.05 * RY
#define TAMANHO_TEXTO_ICONES 2.2 * DIMENSAO_ICONES
#define LARGURA_BARRAS 0.015 * RY
#define VIDA_INICIAL_BASE 20
#define COMIDA_INICIAL 40
#define MINERIO_INICIAL 40
#define ELETRICIDADE_INICIAL 40

const int LADO = RY/BLOCOS_LINHA;
enum divisao {HUMANO = 0, MECANICO, ELETRICO, OPERARIO};
enum classe {GERADOR_DE_RECURSO = 4, GERADOR_DE_TROPA,
                DEFESA_OFENSIVA, DEFESA_PASSIVA};
enum unidades_e_base {REPLICANTE = 8, EXTERMINADOR, HATSUNE, WALL,
                    DROIDES, IRON, MERCENARIOS, CAVALEIROS,
                    CHORIS, BASE, CUSTO};
enum criacao {GERAR_OPERARIO = 19, CRIAR_GER_REC, CRIAR_GER_TRO, CRIAR_MUR, GERAR_TROPA};
enum niveis {EVOLUIR = 24, NIVEL_MAXIMO, NIVEL_1, NIVEL_2, NIVEL_3};
enum time {ALIADO = 0, INIMIGO};

typedef struct Player_Data {
    int time;
    int comida;
    int minerio;
    int eletricidade;
    int xp;
    int nivel;
    int vida_base;
}player_data;

typedef struct Unidade_Movel {
    int vida;
    int ataque;
    int defesa;
    int alcance;
    int velocidade;
    int divisao;
    int time;
    int nivel;
    int dim;
    int i;
    int j;
    int custo_minerio;
    int custo_comida;
    int custo_eletricidade;
    bool acao;
}unidade_movel;

typedef struct Unidade_Estatica {
    int vida;
    int ataque;
    int defesa;
    int alcance;
    int classe;
    int divisao;
    int time;
    int nivel;
    int dim;
    int i;
    int j;
    int custo_minerio;
    int custo_comida;
    int custo_eletricidade;
    int producao;
    bool acao;
}unidade_estatica;

typedef struct Base_Principal {
    int vida;
    int time;
    int dim;
    int i;
    int j;
}base_principal;

typedef struct Cell_Mapa {
    int x;
    int y;
    int lado;
    unidade_movel *pUniMovel;
    unidade_estatica *pUniImovel;
    base_principal *pBase;
}cell_mapa;

typedef struct Imagens_Data {
    unsigned int textura_grade; 
    unsigned int textura_fundo;
    unsigned int textura_base;
    unsigned int textura_menu_principal;
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
    unsigned int minerio;
    unsigned int raio;
    unsigned int comida;
    unsigned int operario;
    unsigned int botao1;
    unsigned int botao2;
}imagens_data;

typedef struct Mouse_Data {
    int x;
    int y;
    int x_mem;
    int y_mem;
    int x_agr;
    int y_agr;
    int x_botao;
    int y_botao;
    int botao_mem;
}mouse_data;

typedef struct Atributos_Data {
    int classe;
    int divisao;
    int time;
    int nivel;
}atributos_data;

typedef struct Texto_Data {
    unsigned int numero_textura[101];
    unsigned int nome_textura[30];
}texto_data;


int min(int a, int b);

int max(int a, int b);

/**
 * @brief Carrega Texturas.
 * Função que carrega as texturas atribuídas.
 *
 * @param const std::string&fileName - Nome de arquivo. 
 *
 * @return Imagem- O objeto renderizado.
 */
GLuint loadTexture(const std::string&fileName);

/**
 * @brief Carrega Texto.
 * Função que carrega os textos atribuídos.
 *
 * @param const std::string &text - Texto a ser renderizado. 
 *
 * @param int font_size - Tamanho do texto. 
 *
 * @param int red - Valor de vermelho. 
 *
 * @param int green - Valor de verde. 
 *
 * @param int blue - Valor de azul. 
 *
 * @return Texto- O texto renderizado.
 */
GLuint importText(const std::string &text, int font_size, int red, int green, int blue);

/**
 * @brief Cria Mapa..
 * Função que carrega o mapa do jogo.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int cria_mapa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA]);

/**
 * @brief Carrega Texto.
 * Função que carrega os textos atribuídos.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param imagens_data imagens - Imagens carregadas. 
 *
 * @param mouse_data mouse - Informações de localização do mouse do usuário. 
 *
 * @param texto_data texto - Texto a ser carregado. 
 *
 * @param  player_data *player - Informações de jogador. 
 *
 * @param  atributos_data atributos - Atributos do jogador.
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_interface(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data *mouse, texto_data texto, player_data *player, atributos_data atributos);

/**
 * @brief Carrega a base do jogador.
 * Função que carrega a base de cada participante do jogo, com seus devidos atributos.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param int i - Auxiliar de coordenada da base. 
 *
 * @param int j - Auxiliar de coordenada da base. 
 *
 * @param int dim - Dimensão. 
 *
 * @param  int vida - Vida da base. 
 *
 * @param  int time - O time a qual a base é atribuída.
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int cria_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, int dim, int vida, int time);

/**
 * @brief Carrega base.
 * Função que carrega a base do jogador, com seus atributos.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param imagens_data imagens - Imagens carregadas. 
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens);

/**
 * @brief Verifica a imagem.
 * Função que verifica se uma imagem foi carregada corretamente.
 *
 * @param const std::string&fileName - Arquivo que se deseja verificar. 
 *
 * @return true - Se o procedimento foi bem sucedido.
 */
bool verifica_imagem(const std::string&fileName);

/**
 * @brief Verifica espaço do mapa.
 * Função que verifica se um um espaço no mapa está livre.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param int i - Auxiliar de coordenada da posição. 
 *
 * @param int j - Auxiliar de coordenada da posição. 
 *
 * @return true - Se o procedimento foi bem sucedido.
 */
bool verifica_espaco(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j);

/**
 * @brief Verifica conteúdo espaço do mapa.
 * Função que verifica se um espaço no mapa está ocupado por estrutura determinada.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param mouse_data mouse - Informações de localização do mouse do usuário. 
 *
 * @return 0 - Se o espaço não está ocupado por nenhuma estrutura definida.
 */
int verifica_selecao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data mouse);

/**
 * @brief Verifica unidades.
 * Função que verifica um ações entre unidades, como locomoção, combate e destruição.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param mouse_data mouse - Informações de localização do mouse do usuário.
 *
 * @param  player_data *player - Informações de jogador.  
 *
 * @param  atributos_data atributos - Atributos do jogador.
 *
 * @return 0 - Se tudo ocorre dentro do esperado.
 */
int verifica_unidades(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data *mouse, player_data *player, atributos_data atributos, imagens_data imagens, texto_data texto);

bool verifica_velocidade(unidade_movel* aux, int cell_i, int cell_j);

bool verifica_alcance (unidade_movel* aux, int cell_i, int cell_j);

bool verifica_oposicao (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* aux, int i, int j);

/**
 * @brief Cria unidade estática.
 * Função que cria a unidade estática desejada (predios).
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param int i - Auxiliar de coordenada da posição. 
 *
 * @param int j - Auxiliar de coordenada da posição. 
 *
 * @param  atributos_data atributos - Atributos do jogador.
 *
 * @param  player_data *player - Informações de jogador.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int cria_uni_estatico(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, atributos_data atributos, player_data *player);

/**
 * @brief Carrega unidade estática.
 * Função que renderiza a unidade estática desejada (predios).
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param imagens_data imagens - Imagens carregadas. 
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_uni_estatico(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens);

/**
 * @brief Carrega informações de recursos.
 * Função que carrega os recursos do jogador.
 *
 * @param imagens_data imagens - Imagens carregadas. 
 *
 * @param texto_data texto - Texto a ser carregado. 
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_display_recursos (imagens_data imagens, texto_data texto);

/**
 * @brief Carrega o mapa.
 * Função que carrega o mapa do jogo.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param imagens_data imagens - Imagens carregadas. 
 *
 * @param mouse_data mouse - Informações de localização do mouse do usuário. 
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_mapa (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data mouse);

/**
 * @brief Carrega layout.
 * Função que carrega o layout para a criação de outros elementos do jogo.
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_layout();

int colore_espacos_validos(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* aux, player_data* player);

/**
 * @brief Carrega a unidade movel.
 * Função que carrega as imagens de unidades móveis no mapa.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param imagens_data imagens - Imagens carregadas. 
 *
 * @param texto_data texto - Texto a ser carregado.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_uni_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, texto_data texto);

/**
 * @brief Cria a unidade movel.
 * Função que cria as unidades móveis no mapa, com seus atributos respectivos.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param int i - Auxiliar de coordenada da posição. 
 *
 * @param int j - Auxiliar de coordenada da posição. 
 *
 * @param  atributos_data atributos - Atributos do jogador.
 *
 * @param  player_data *player - Informações de jogador.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int cria_uni_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], int i, int j, atributos_data atributos, player_data *player);

/**
 * @brief Carrega quantidade de recurso.
 * Função que carrega a quantidade de recursos do jogador.
 *
 * @param texto_data texto - Texto a ser carregado.  
 *
 * @param  player_data *player - Informações de jogador.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_numeros_recurso (texto_data texto, player_data *player);

/**
 * @brief Carrega quantidade de recurso.
 * Função que carrega a quantidade de recursos do jogador.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param  unidade_movel* unit - A unidade móvel selecionada. 
 *
 * @param int i - Auxiliar de coordenada da posição. 
 *
 * @param int j - Auxiliar de coordenada da posição. 
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */    
int move_unidade (cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* unit, int i, int j);

/**
 * @brief Carrega barras.
 * Função que carrega a barra lateral da interface do jogador, onde ficam as principais informações.
 *
 * @param imagens_data imagens - Imagens carregadas.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_barras(imagens_data imagens);

/**
 * @brief Combate.
 * Função que executa a atualização de informações de combate entre unidade móveis.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param unidade_movel *aux - Unidade envolvida no combate
 *
 * @param unidade_movel *aux2 - Unidade envolvida no combate
 *
 * @param player_data *player - Informações de jogador.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int combate(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, unidade_movel *aux2, player_data *player);


/**
 * @brief Destruição de construção.
 * Função que executa a atualização de informações de combate entre uma unidade e um prédio.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param unidade_movel *aux - Unidade envolvida no combate.
 *
 * @param unidade_estatica *aux2 - Unidade envolvida no combate.
 *
 * @param  player_data *player - Informações de jogador.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int destruicao(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, unidade_estatica *aux2, player_data *player);

/**
 * @brief Carrega comandante.
 * Função que carrega a imagem de um comandante.
 *
 * @param imagens_data imagens - Imagens carregadas.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_comandante(imagens_data imagens);

/**
 * @brief Carrega a caixa.
 * Função que carrega a caixa do jogador.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param mouse_data mouse - Informações de localização do mouse do usuário. 
 *
 * @param imagens_data imagens - Imagens carregadas. 
 * 
 * @param texto_data texto - Texto a ser carregado.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int carrega_caixa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data *mouse, imagens_data imagens, texto_data texto, atributos_data atributos, player_data *player);

/**
 * @brief Escolhe imagem estática.
 * Função que define a imagem de unidade estática desejada.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param imagens_data imagens - Imagens carregadas. 
 *
 * @param int i - Auxiliar de coordenada da posição. 
 *
 * @param int j - Auxiliar de coordenada da posição. 
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int escolhe_imagem_estatica(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, int i, int j);

/**
 * @brief Escolhe imagem móvel.
 * Função que define a imagem de unidade móvel desejada.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param imagens_data imagens - Imagens carregadas. 
 *
 * @param texto_data texto - Texto a ser carregado.
 *
 * @param int i - Auxiliar de coordenada da posição. 
 *
 * @param int j - Auxiliar de coordenada da posição. 
 *
 * @param int opcao - Auxiliar que define caso de execução
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int escolhe_imagem_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, texto_data texto, int i, int j, int opcao);

/**
 * @brief Escolhe texto.
 * Função que define o texto a ser exibido.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param texto_data texto - Texto a ser carregado. 
 *
 * @param int i - Auxiliar de coordenada da posição. 
 *
 * @param int j - Auxiliar de coordenada da posição. 
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int escolhe_texto_movel(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], texto_data texto, int i, int j);

/**
 * @brief Construção.
 * Função que constrói determinada unidade.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param  atributos_data atributos - Atributos do jogador.
 *
 * @param int cell_i - Auxiliar de coordenada da posição. 
 *
 * @param int cell_j - Auxiliar de coordenada da posição. 
 *
 * @param unidade_movel* unit -Unidade movel emvolvida na construção .
 *
 * @param player_data *player - Informações de jogador.      
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int construction(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, int cell_i, int cell_j, unidade_movel* unit, player_data *player);

/**
 * @brief Atualização de recursos.
 * Função que recursos de determinado jogador.
 *
 * @param cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA] - Mapa quadriculado do jogo. 
 *
 * @param  player_data *player - Informações de jogador.
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
void Atualizar_recursos(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], player_data *player);

/**
 * @brief Definição de nível.
 * Função que define nível de determinado jogador.
 *
 * @param  player_data *player - Informações de jogador.
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int player_level(player_data *player);

//define_mov_rang(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel* aux);

/**
 * @brief Evolui construções.
 * Função que evolui determinada construção.
 *
 * @param unidade_estatica aux2 - Unidade envolvida na evolução.
 *
 * @param  player_data *player - Informações de jogador.  
 *
 * @return 0 - Se o procedimento foi bem sucedido.
 */
int evolution(unidade_estatica *aux, player_data *player);

int carrega_botao(imagens_data imagens, texto_data texto, mouse_data *mouse, int local, int tipo, cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], atributos_data atributos, player_data *player);

int gera_operario(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data *mouse, atributos_data atributos, player_data *player);

int gera_tropa(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data *mouse, atributos_data atributos, player_data *player);

/**
 * @file cpu.cpp
 *
 * @brief Inteligencia artificial da CPU para simular o oponente
 *
 * @author Grupo 2
 *
 */

void CPU(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], imagens_data imagens, mouse_data mouse, texto_data texto, player_data *player_CPU, atributos_data atributos, int contador_turno);
//int gera_operario(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], mouse_data mouse, atributos_data atributos, player_data *player);
void cria_player(player_data *player, int time);

void restaurar_acoes(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA]);

int destruicao_base(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA], unidade_movel *aux, base_principal *aux2, player_data *player);