#include "minhabib.h"
#include <stdio.h>
#include <stdlib.h>

/* Funções auxiliares internas */

static No* localizar_no(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;
    if (valor < raiz->valor) return localizar_no(raiz->esq, valor);
    return localizar_no(raiz->dir, valor);
}

static int obter_grau(No* no) {
    if (no == NULL) return 0;
    int grau = 0;
    if (no->esq != NULL) grau++;
    if (no->dir != NULL) grau++;
    return grau;
}

static void imprimir_nos_do_nivel(No* raiz, int nivel) {
    if (raiz == NULL) return;
    if (nivel == 0) {
        printf("%d ", raiz->valor);
    } else {
        imprimir_nos_do_nivel(raiz->esq, nivel - 1);
        imprimir_nos_do_nivel(raiz->dir, nivel - 1);
    }
}

static int verificar_ancestrais(No* raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->valor == valor) return 1;
    if (verificar_ancestrais(raiz->esq, valor) || verificar_ancestrais(raiz->dir, valor)) {
        printf("%d ", raiz->valor);
        return 1;
    }
    return 0;
}

/* Implementação das funções da especificação */

void imprimir_nos_internos(No* raiz) {
    if (raiz != NULL) {
        if (raiz->esq != NULL || raiz->dir != NULL) {
            printf("%d ", raiz->valor);
        }
        imprimir_nos_internos(raiz->esq);
        imprimir_nos_internos(raiz->dir);
    }
}

void imprimir_folhas(No* raiz) {
    if (raiz != NULL) {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            printf("%d ", raiz->valor);
        }
        imprimir_folhas(raiz->esq);
        imprimir_folhas(raiz->dir);
    }
}

void imprimir_niveis(No* raiz, int nivel_atual) {
    int altura = calcular_altura(raiz);
    for (int i = 0; i <= altura; i++) {
        printf("Nivel %d: ", i);
        imprimir_nos_do_nivel(raiz, i);
        printf("\n");
    }
}

int calcular_altura(No* no) {
    if (no == NULL) return -1;
    int h_esq = calcular_altura(no->esq);
    int h_dir = calcular_altura(no->dir);
    return (h_esq > h_dir ? h_esq : h_dir) + 1;
}

int calcular_profundidade(No* raiz, int valor, int profundidade_atual) {
    if (raiz == NULL) return -1;
    if (raiz->valor == valor) return profundidade_atual;
    if (valor < raiz->valor) return calcular_profundidade(raiz->esq, valor, profundidade_atual + 1);
    return calcular_profundidade(raiz->dir, valor, profundidade_atual + 1);
}

void imprimir_ancestrais(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return;
    verificar_ancestrais(raiz, valor);
}

void imprimir_descendentes(No* no) {
    if (no != NULL) {
        if (no->esq != NULL) {
            printf("%d ", no->esq->valor);
            imprimir_descendentes(no->esq);
        }
        if (no->dir != NULL) {
            printf("%d ", no->dir->valor);
            imprimir_descendentes(no->dir);
        }
    }
}

void analisar_arvore(No* raiz, int valorBusca) {
    if (raiz == NULL) return;

    printf("=== A. DIAGNOSTICO GERAL ===\n");
    printf("Raiz: %d\n", raiz->valor);
    
    printf("Nos Internos: ");
    imprimir_nos_internos(raiz);
    printf("\nNos Externos (Folhas): ");
    imprimir_folhas(raiz);
    printf("\nExibicao por Niveis:\n");
    imprimir_niveis(raiz, 0);

    printf("\n=== B. DIAGNOSTICO ESPECIFICO (Valor: %d) ===\n", valorBusca);
    No* alvo = localizar_no(raiz, valorBusca);
    if (alvo != NULL) {
        printf("Grau do No: %d\n", obter_grau(alvo));
        printf("Ancestrais: ");
        imprimir_ancestrais(raiz, valorBusca);
        printf("\nDescendentes: ");
        imprimir_descendentes(alvo);
        printf("\nAltura: %d\n", calcular_altura(alvo));
        printf("Profundidade: %d\n", calcular_profundidade(raiz, valorBusca, 0));

        printf("\n=== C. EXTRACAO DE SUB-ARVORE ===\n");
        imprimir_niveis(alvo, 0);
    } else {
        printf("Valor nao encontrado na estrutura.\n");
    }
}
