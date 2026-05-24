// RA: 2040482513017 - Gabriel Reinaldo Chagas de Medeiros

#include <stdio.h>

/* Funcao recursiva para resolver as Torres de Hanoi */
void hanoi(int n, char origem, char destino, char auxiliar) {
    // Caso base: mover o ultimo disco restante diretamente para o destino
    if (n == 1) {
        printf("Mover disco 1 de %c para %c\n", origem, destino);
        return;
    }
    
    // Caso recursivo 1: Mover n-1 discos da origem para o auxiliar
    hanoi(n - 1, origem, auxiliar, destino);
    
    // Mover o disco atual para o destino
    printf("Mover disco %d de %c para %c\n", n, origem, destino);
    
    // Caso recursivo 2: Mover os n-1 discos do auxiliar para o destino
    hanoi(n - 1, auxiliar, destino, origem);
}

int main() {
    printf("--- TESTE n = 1 ---\n");
    hanoi(1, 'A', 'C', 'B');

    printf("\n--- TESTE n = 3 ---\n");
    hanoi(3, 'A', 'C', 'B');

    printf("\n--- TESTE n = 4 ---\n");
    hanoi(4, 'A', 'C', 'B');

    return 0;
}
