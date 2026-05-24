// RA: 2040482513017 - Gabriel Reinaldo Chagas de Medeiros

#include <stdio.h>

/* Variavel global para contar as chamadas recursivas */
int chamadas_busca = 0;

/* Retorna o INDICE do elemento se encontrado, ou -1 caso contrario. */
int buscaBinaria(int *vet, int inicio, int fim, int alvo) {
    chamadas_busca++;
    
    // Caso base: os ponteiros se cruzaram, logo o alvo nao esta no vetor
    if (inicio > fim) {
        return -1;
    }
    
    // Calcula o meio prevenindo overflow de inteiros
    int meio = inicio + (fim - inicio) / 2;
    
    // Caso base: elemento encontrado no meio
    if (vet[meio] == alvo) {
        return meio;
    }
    
    // Caso recursivo 1: o alvo eh menor, entao busca na metade esquerda
    if (vet[meio] > alvo) {
        return buscaBinaria(vet, inicio, meio - 1, alvo);
    }
    
    // Caso recursivo 2: o alvo eh maior, entao busca na metade direita
    return buscaBinaria(vet, meio + 1, fim, alvo);
}

int main() {
    int dados[] = {2, 5, 8, 12, 16, 23, 38, 45, 72, 91};
    int n = sizeof(dados) / sizeof(int);
    
    // Testes solicitados: presente (23), ausente (100) e primeiro elemento (2)
    int alvos_teste[] = {23, 100, 2};
    
    printf("--- TESTES DE BUSCA BINARIA RECURSIVA ---\n");
    for (int i = 0; i < 3; i++) {
        chamadas_busca = 0; // Reseta o contador para cada teste
        int alvo = alvos_teste[i];
        int indice = buscaBinaria(dados, 0, n - 1, alvo);
        
        if (indice != -1) {
            printf("Alvo %3d ENCONTRADO no indice %d | Chamadas recursivas: %d\n", alvo, indice, chamadas_busca);
        } else {
            printf("Alvo %3d NAO ENCONTRADO        | Chamadas recursivas: %d\n", alvo, chamadas_busca);
        }
    }

    return 0;
}
