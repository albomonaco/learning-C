#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void copia_mapa(MAPA* destino, MAPA* origem){
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    aloca_mapa(destino);
    for (int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]);
    }

}

void anda_no_mapa(MAPA* m, int x_origem, int y_origem,
    int x_destino, int y_destino){
    
    char personagem = m->matriz[x_origem][y_origem];
    m->matriz[x_destino][y_destino] = personagem;
    m->matriz[x_origem][y_origem] = VAZIO;
    
}

int eh_valida(MAPA* m, int x, int y){
    if (x >= m->linhas)
        return 0;
    if (y >= m->colunas)
        return 0;

    return 1;   

}

int eh_vazia(MAPA* m, int x, int y){
    return m->matriz[x][y] == VAZIO;
}

int encontra_mapa(MAPA* m, POSICAO* p, char c){

    for (int i = 0; i < m->linhas; i++){
        for (int j = 0; j < m->colunas; j++){
            if(m->matriz[i][j] == c){
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
}

int eh_parede(MAPA* m, int x, int y){
    return m->matriz[x][y] == PAREDE_VERTICAL ||
        m->matriz[x][y] == PAREDE_HORIZONTAL;
}

int eh_personagem(MAPA* m, char personagem, int x, int y){

    return m->matriz[x][y] == personagem;
}

int pode_andar(MAPA* m, char personagem, int x, int y){
    return
        eh_valida(m, x, y) && 
        !eh_parede(m, x, y) &&
        !eh_personagem(m, personagem, x, y);
}

void libera_mapa(MAPA* m){
    for (int i = 0; i < m->linhas; i++){
        free(m->matriz[i]);
    }
    free(m->matriz);

}

void aloca_mapa(MAPA* m){
    m->matriz = malloc(sizeof(char*) * m->linhas);

    for (int i = 0; i < m->linhas; i++){
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
    }
}

void le_mapa(MAPA* m){
    FILE* f;

    f = fopen("mapa.txt","r");
    if(f == 0){
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    fscanf(f, "%d %d",&(m->linhas), &(m->colunas));

    aloca_mapa(m);
    
    for (int i = 0; i < m->linhas; i++){
        fscanf(f, "%s", m->matriz[i]);
    }

    fclose(f);
}


void imprime_mapa(MAPA* m){
    for (int i = 0; i < m->linhas; i++){
        printf("%s\n", m->matriz[i]);
    }
}