// RA: 2040482513017 - Gabriel Reinaldo Chagas de Medeiros

#include <stdio.h>
#include <stdlib.h>

/* ==========================================================
 * PARTE A - IMPLEMENTACAO DA ESTRUTURA
 * ========================================================== */

/* Definicao do no da arvore */
typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

/* Insere um novo valor na ABB */
No* inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (valor < raiz->dado) {
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->dado) {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

/* Calcula a altura de um no (-1 se ponteiro nulo, conforme requisito) */
int alturaNo(No *no) {
    if (no == NULL) return -1;
    int altEsq = alturaNo(no->esq);
    int altDir = alturaNo(no->dir);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}

/* Calcula a profundidade de um no (-1 se o valor nao existir) */
int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado) return profundidadeNo(raiz->esq, valor, prof + 1);
    return profundidadeNo(raiz->dir, valor, prof + 1);
}

/* Retorna o grau do no (0, 1 ou 2) */
int grauNo(No *no) {
    if (no == NULL) return 0;
    int grau = 0;
    if (no->esq != NULL) grau++;
    if (no->dir != NULL) grau++;
    return grau;
}

/* Busca auxiliar para localizar um no e calcular sua altura depois */
No* buscarNo(No *raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor) return raiz;
    if (valor < raiz->dado) return buscarNo(raiz->esq, valor);
    return buscarNo(raiz->dir, valor);
}

/* Imprime o grau de todos os nos em-ordem (Esq -> Raiz -> Dir) */
void imprimirGrausEmOrdem(No *raiz) {
    if (raiz != NULL) {
        imprimirGrausEmOrdem(raiz->esq);
        printf("No %d: Grau %d\n", raiz->dado, grauNo(raiz));
        imprimirGrausEmOrdem(raiz->dir);
    }
}

/* Libera a memoria alocada (Requisito obrigatorio) */
void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

/* ==========================================================
 * PARTE C - VERIFICACAO MANUAL E DESENHO (ASCII ART)
 * ========================================================== 
 * DESENHO DA ARVORE RESULTANTE:
 * * 50
 * /        \
 * 30          70
 * /    \      /    \
 * 20      40  60      80
 * /  \       \   \
 * 10    25     45   65
 * * VERIFICACAO MANUAL (3 NOS):
 * 1. No 50 (Raiz): Altura 3 (caminho mais longo vai ate 10, 25, 45 ou 65), Profundidade 0.
 * 2. No 30: Altura 2 (caminho mais longo vai ate 10, 25 ou 45), Profundidade 1.
 * 3. No 10: Altura 0 (eh uma folha), Profundidade 3.
 * Os calculos manuais batem exatamente com as saidas geradas pelo programa.
 * ========================================================== */

/* ==========================================================
 * PARTE B - CONSULTAS ESTRUTURAIS (MAIN)
 * ========================================================== */
int main() {
    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int n = sizeof(valores) / sizeof(int);

    // Construcao da arvore
    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    printf("--- a) ALTURA DOS NOS ---\n");
    int nosA[] = {50, 30, 70, 20, 10};
    for (int i = 0; i < 5; i++) {
        No *alvo = buscarNo(raiz, nosA[i]);
        printf("Altura do no %d: %d\n", nosA[i], alturaNo(alvo));
    }

    printf("\n--- b) PROFUNDIDADE DOS NOS ---\n");
    int nosB[] = {50, 30, 70, 45, 10};
    for (int i = 0; i < 5; i++) {
        printf("Profundidade do no %d: %d\n", nosB[i], profundidadeNo(raiz, nosB[i], 0));
    }

    printf("\n--- c) GRAU DOS NOS (EM-ORDEM) ---\n");
    imprimirGrausEmOrdem(raiz);

    printf("\n--- d) ALTURA TOTAL DA ARVORE ---\n");
    printf("Altura total da arvore: %d\n", alturaNo(raiz));

    // Liberacao de memoria
    liberarArvore(raiz);
    
    return 0;
}
