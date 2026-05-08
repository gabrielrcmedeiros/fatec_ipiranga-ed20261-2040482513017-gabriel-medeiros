#include <stdio.h>
#include <stdlib.h>

// Estrutura do no da arvore binaria.
struct No {
    int valor;
    int altura;
    struct No* esq;
    struct No* dir;
};

// Aloca memoria e inicializa um novo no.
struct No* criarNo(int valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = valor;
    novoNo->altura = 0; 
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

// Retorna o maior valor entre dois inteiros.
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula a altura de um no de forma recursiva.
// Retorna -1 para nos nulos.
int calcularAltura(struct No* n) {
    if (n == NULL) {
        return -1; 
    }
    return 1 + max(calcularAltura(n->esq), calcularAltura(n->dir));
}

// Calcula o Fator de Balanceamento (FB) de um no.
// Formula: FB = altura(esq) - altura(dir).
int obterFB(struct No* n) {
    if (n == NULL) {
        return 0;
    }
    return calcularAltura(n->esq) - calcularAltura(n->dir);
}

int main() {
    // Instanciacao dos nos.
    struct No* no20 = criarNo(20);
    struct No* no10 = criarNo(10);
    struct No* no5  = criarNo(5);
    struct No* no2  = criarNo(2);

    // Conexao dos nos (formato de escada linear a esquerda).
    no20->esq = no10;
    no10->esq = no5;
    no5->esq = no2;

    // Calculo do FB do no raiz.
    int fb_raiz = obterFB(no20);

    // Saida do resultado.
    printf("Fator de Balanceamento da raiz (no 20): %d\n", fb_raiz);
    
    // Desalocacao de memoria.
    free(no2);
    free(no5);
    free(no10);
    free(no20);

    return 0;
}