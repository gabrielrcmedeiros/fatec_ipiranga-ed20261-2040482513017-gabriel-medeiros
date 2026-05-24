// RA: 2040482513017 - Gabriel Reinaldo Chagas de Medeiros

#include <stdio.h>

/* Funcao auxiliar para imprimir o recuo visual baseado na profundidade */
void imprimirEspacos(int nivel) {
    for (int i = 0; i < nivel * 2; i++) {
        putchar(' ');
    }
}

/* Funcao de Hanoi com rastreamento de profundidade */
void hanoiProfundidade(int n, char origem, char destino, char auxiliar, int nivel) {
    // Caso base
    if (n == 1) {
        imprimirEspacos(nivel);
        printf("[Nivel %d] Mover disco 1 de %c para %c\n", nivel, origem, destino);
        return;
    }
    
    // Desce um nivel na recursao para o auxiliar
    hanoiProfundidade(n - 1, origem, auxiliar, destino, nivel + 1);
    
    // Imprime o movimento atual no nivel corrente
    imprimirEspacos(nivel);
    printf("[Nivel %d] Mover disco %d de %c para %c\n", nivel, n, origem, destino);
    
    // Desce um nivel na recursao para o destino
    hanoiProfundidade(n - 1, auxiliar, destino, origem, nivel + 1);
}

int main() {
    printf("--- HANOI COM RASTREAMENTO DE PILHA (n = 3) ---\n");
    // Chamada inicial partindo do nivel 0 (raiz da arvore de execucao)
    hanoiProfundidade(3, 'A', 'C', 'B', 0);
    
    return 0;
}
