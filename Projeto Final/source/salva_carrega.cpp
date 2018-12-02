/**
 * @file salva_carrega.cpp
 *
 * @brief Arquivo com a opcao de salvar e carregar o estado do jogo
 *
 * @author Grupo 2
 *
 */


#include "funcoes.h"

void salva_jogo(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA]) {
    int i, j;
    FILE *arq  = fopen("jogo_salvo.txt", "w+");
    for (i = 0; i < BLOCOS_LINHA; i++) {
        for (j = 0; j < BLOCOS_LINHA; j++) {
            if (mapa[i][j].pUniMovel != NULL) {
                    if(mapa[i][j].pUniMovel->i == i && mapa[i][j].pUniMovel->j==j){
                        fprintf(arq, "%d\n", UNIDADE);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->vida);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->ataque);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->defesa);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->alcance);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->velocidade);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->divisao);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->time);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->nivel);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->dim);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->i);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->j);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->custo_minerio);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->custo_comida);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->custo_eletricidade);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->acao);
                        fprintf(arq, "%d\n", mapa[i][j].pUniMovel->cont_ataque);
                    } else{
                        fprintf(arq, "%d\n", 0);
                    }
            } else if (mapa[i][j].pUniImovel != NULL) {
                if(mapa[i][j].pUniImovel->i==i && mapa[i][j].pUniImovel->j == j) {
                    fprintf(arq, "%d\n", ESTRUTURA);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->vida);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->ataque);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->defesa);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->alcance);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->classe);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->divisao);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->time);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->nivel);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->dim);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->i);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->j);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->custo_minerio);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->custo_comida);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->custo_eletricidade);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->producao);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->acao);
                    fprintf(arq, "%d\n", mapa[i][j].pUniImovel->cont_ataque);
                } else{
                    fprintf(arq, "%d\n", 0);
                }
            } else if (mapa[i][j].pBase != NULL) {
                if( mapa[i][j].pBase->i == i && mapa[i][j].pBase->j == j) {
                    fprintf(arq, "%d\n", BASE);
                    fprintf(arq, "%d\n", mapa[i][j].pBase->vida);
                    fprintf(arq, "%d\n", mapa[i][j].pBase->time);
                    fprintf(arq, "%d\n", mapa[i][j].pBase->dim);
                    fprintf(arq, "%d\n", mapa[i][j].pBase->i);
                    fprintf(arq, "%d\n", mapa[i][j].pBase->j);
                } else{
                    fprintf(arq, "%d\n", 0);
                }
            } else{
                fprintf(arq, "%d\n", VAZIO);
            }
        }
    }
    fclose(arq);
}

void carrega_jogo(cell_mapa mapa[BLOCOS_LINHA][BLOCOS_LINHA]) {
    int i, j, leitura, tipo, p, q;
    char c;
    FILE *arq  = fopen("jogo_salvo.txt", "r");
    if(arq == NULL)
        return;
    for (i = 0; i < BLOCOS_LINHA; i++) {
        for (j = 0; j < BLOCOS_LINHA; j++) {
                mapa[i][j].pUniMovel = NULL;
                mapa[i][j].pUniImovel = NULL;
                mapa[i][j].pBase = NULL;
        }
    }
    for (i = 0; i < BLOCOS_LINHA; i++) {
        for (j = 0; j < BLOCOS_LINHA; j++) {
            fscanf(arq, "%d%c", &tipo, &c);
            if (tipo == UNIDADE) {
                unidade_movel *Unidade = (unidade_movel*)malloc(sizeof(unidade_movel));
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->vida = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->ataque = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->defesa = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->alcance = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->velocidade = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->divisao = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->time = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->nivel = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->dim = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->i = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->j = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->custo_minerio = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->custo_comida = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->custo_eletricidade = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->acao = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->cont_ataque = leitura;
                mapa[i][j].pUniMovel = Unidade;
                mapa[i][j].pUniImovel = NULL;
                mapa[i][j].pBase = NULL;
            } else if (tipo == ESTRUTURA) {
                unidade_estatica *Unidade = (unidade_estatica*)malloc(sizeof(unidade_estatica));
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->vida = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->ataque = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->defesa = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->alcance = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->classe = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->divisao = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->time = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->nivel = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->dim = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->i = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->j = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->custo_minerio = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->custo_comida = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->custo_eletricidade = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->producao = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->acao = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Unidade->cont_ataque = leitura;
                mapa[i][j].pUniMovel = NULL;
                mapa[i][j].pUniImovel = Unidade;
                mapa[i][j].pBase = NULL;
                for (int p = i; p <= (i + Unidade->dim-1); p++) {
                    for (int q = j; q <= (j + Unidade->dim-1); q++) {
                        mapa[p][q].pUniImovel = Unidade;
                    }
                }
            } else if (tipo == BASE) {
                base_principal *Base = (base_principal*)malloc(sizeof(base_principal));
                fscanf(arq, "%d%c", &leitura, &c);
                Base->vida = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Base->time = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Base->dim = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Base->i = leitura;
                fscanf(arq, "%d%c", &leitura, &c);
                Base->j = leitura;
                mapa[i][j].pUniMovel = NULL;
                mapa[i][j].pUniImovel = NULL;
                mapa[i][j].pBase = Base;
                for (int p = i; p <= (i + Base->dim-1); p++) {
                    for (int q = j; q <= (j + Base->dim-1); q++) {
                        mapa[p][q].pBase = Base;
                    }
                }
            } else if (tipo == VAZIO){
                mapa[i][j].pUniMovel = NULL;
                mapa[i][j].pUniImovel = NULL;
                mapa[i][j].pBase = NULL;
            }
        }
    }
    
    fclose(arq);
}
