// RA: 2040482513017 - Gabriel Reinaldo Chagas de Medeiros

#include <stdio.h>
#include <stdlib.h>

/* ==========================================================
 * ESTRUTURAS E FUNCOES BASE (Reutilizadas do Ex05)
 * ========================================================== */
typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

No* inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (valor < raiz->dado) raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

int alturaNo(No *no) {
    if (no == NULL) return -1;
    int altEsq = alturaNo(no->esq);
    int altDir = alturaNo(no->dir);
    return (altEsq > altDir ? altEsq : altDir) + 1;
}

int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado) return profundidadeNo(raiz->esq, valor, prof + 1);
    return profundidadeNo(raiz->dir, valor, prof + 1);
}

int grauNo(No *no) {
    if (no == NULL) return 0;
    int grau = 0;
    if (no->esq != NULL) grau++;
    if (no->dir != NULL) grau++;
    return grau;
}

No* buscarNo(No *raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor) return raiz;
    if (valor < raiz->dado) return buscarNo(raiz->esq, valor);
    return buscarNo(raiz->dir, valor);
}

/* ==========================================================
 * PARTE A - FUNCOES DE PARENTESCO
 * ========================================================== */

/* Imprime todos os ancestrais recursivamente (Pai -> Raiz) */
/* Imprime todos os ancestrais recursivamente (Pai -> Raiz) */
void imprimirAncestral(No *raiz, int valor) {
    // Caso base: se a raiz for nula ou se encontramos o alvo, paramos de descer
    if (raiz == NULL || raiz->dado == valor) {
        return;
    }
    
    // Tira proveito da propriedade da Arvore Binaria de Busca (ABB) para descer no caminho certo
    if (valor < raiz->dado) {
        imprimirAncestral(raiz->esq, valor);
    } else {
        imprimirAncestral(raiz->dir, valor);
    }
    
    // Imprimir DEPOIS da chamada recursiva garante que a exibicao ocorra 
    // no desempilhamento, ou seja, na ordem exata: Pai -> ... -> Raiz
    printf("%d ", raiz->dado);
}

/* Funcao auxiliar para percorrer em-ordem */
void inOrdemAux(No *no) {
    if (no != NULL) {
        inOrdemAux(no->esq);
        printf("%d ", no->dado);
        inOrdemAux(no->dir);
    }
}

/* Imprime descendentes em-ordem (ignorando o proprio no) */
void imprimirDescendentes(No *raiz, int valor) {
    No *alvo = buscarNo(raiz, valor);
    if (alvo != NULL) {
        // Percorre a subarvore esquerda e depois a direita, pulando a raiz atual (o alvo)
        if (alvo->esq != NULL) inOrdemAux(alvo->esq);
        if (alvo->dir != NULL) inOrdemAux(alvo->dir);
    }
}

/* Conta quantos descendentes o no possui recursivamente */
int contarDescendentes(No *no) {
    if (no == NULL) return 0;
    int cont = 0;
    if (no->esq != NULL) cont += 1 + contarDescendentes(no->esq);
    if (no->dir != NULL) cont += 1 + contarDescendentes(no->dir);
    return cont;
}

/* ==========================================================
 * PARTE B - RELATORIO COMPLETO DE NO
 * ========================================================== */
void relatorioNo(No *raiz, int valor) {
    No *alvo = buscarNo(raiz, valor);
    
    // Requisito: exibir mensagem de erro apropriada se nao existir
    if (alvo == NULL) {
        printf("ERRO: O valor %d nao existe na arvore.\n\n", valor);
        return;
    }

    int profundidade = profundidadeNo(raiz, valor, 0);
    int altura = alturaNo(alvo);
    int grau = grauNo(alvo);
    int qtdDesc = contarDescendentes(alvo);

    printf("+---------------------------------------+\n");
    printf("| RELATORIO DO NO: %-20d |\n", valor);
    printf("+---------------------------------------+\n");
    printf("  Profundidade : %d\n", profundidade);
    printf("  Altura       : %d\n", altura);
    printf("  Grau         : %d\n", grau);
    
    printf("  Ancestrais   : ");
    if (alvo == raiz) {
        printf("Nenhum (Raiz)");
    } else {
        imprimirAncestral(raiz, valor);
    }
    printf("\n");

    printf("  Descendentes : ");
    if (qtdDesc == 0) {
        printf("Nenhum (Folha)");
    } else {
        imprimirDescendentes(raiz, valor);
    }
    printf("\n");
    
    printf("  Qtd Descend. : %d\n", qtdDesc);
    printf("+---------------------------------------+\n\n");
}

/* Funcao obrigatoria para liberar memoria ao final */
void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

/* ==========================================================
 * PARTE C - TESTE SISTEMATICO (MAIN)
 * ========================================================== */
int main() {
    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int n = sizeof(valores) / sizeof(int);

    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    // Chamadas de teste exigidas pelo PDF
    relatorioNo(raiz, 50); // Raiz
    relatorioNo(raiz, 30); // No intermediario
    relatorioNo(raiz, 10); // Folha
    relatorioNo(raiz, 70); // No intermediario
    
    // Testando o tratamento de erro
    relatorioNo(raiz, 999);

    liberarArvore(raiz);
    return 0;
}
