// RA: 2040482513017 - Gabriel Reinaldo Chagas de Medeiros

#include <stdio.h>

/* Variavel global para contar as chamadas recursivas */
int chamadas_pot = 0;

/* Calcula base^exp de forma recursiva eficiente. Complexidade: O(log exp) */
long long potenciaRapida(long long base, int exp) {
    chamadas_pot++;
    
    // Caso base: qualquer numero elevado a zero eh 1
    if (exp == 0) {
        return 1;
    }
    
    // Caso recursivo 1: expoente par. Eleva a base ao quadrado e divide o expoente.
    if (exp % 2 == 0) {
        long long metade = potenciaRapida(base, exp / 2);
        return metade * metade;
    } 
    // Caso recursivo 2: expoente impar. Multiplica a base pelo resultado da reducao do expoente.
    else {
        return base * potenciaRapida(base, exp - 1);
    }
}

/*
 * COMPARACAO DE COMPLEXIDADE:
 * A abordagem ingenua (base * base^(exp-1)) subtrai 1 do expoente a cada chamada, 
 * resultando em complexidade linear O(n). Para calcular 7^12, seriam necessarias 13 chamadas.
 * * A potenciacao rapida divide o expoente pela metade a cada passo par, 
 * resultando em complexidade logaritmica O(log n). Para calcular 7^12,
 * sao necessarias apenas 6 chamadas recursivas, reduzindo drasticamente o uso da pilha.
 */

int main() {
    // Casos de teste solicitados
    long long bases[] = {2, 3, 5, 7};
    int expoentes[] = {10, 7, 0, 12};
    
    printf("--- TESTES DE POTENCIACAO RAPIDA ---\n");
    for (int i = 0; i < 4; i++) {
        chamadas_pot = 0; // Reseta o contador para cada teste
        long long base = bases[i];
        int exp = expoentes[i];
        
        long long resultado = potenciaRapida(base, exp);
        printf("%lld^%d = %lld \t| Chamadas recursivas: %d\n", base, exp, resultado, chamadas_pot);
    }

    return 0;
}
