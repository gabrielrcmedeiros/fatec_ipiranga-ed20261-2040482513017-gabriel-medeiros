// RA: 2040482513017 - Gabriel Reinaldo Chagas de Medeiros

#include <stdio.h>

/* Calcula e RETORNA a media aritmetica */
float calcularMedia(float *vet, int n) {
    float soma = 0.0f;
    float *ptr;
    // Iteracao baseada exclusivamente em incremento de ponteiro
    for (ptr = vet; ptr < vet + n; ptr++) {
        soma += *ptr;
    }
    return soma / n;
}

/* Encontra o maior e o menor valor; armazena nos ponteiros recebidos */
void encontrarExtremos(float *vet, int n, float *maior, float *menor) {
    if (n <= 0) return;
    
    // Inicializa os ponteiros com o primeiro valor do vetor
    *maior = *vet;
    *menor = *vet;
    
    float *ptr;
    // O laco inicia do segundo elemento (vet + 1)
    for (ptr = vet + 1; ptr < vet + n; ptr++) {
        if (*ptr > *maior) {
            *maior = *ptr;
        }
        if (*ptr < *menor) {
            *menor = *ptr;
        }
    }
}

/* Normaliza o vetor: cada elemento eh dividido pelo valor maximo */
void normalizar(float *vet, int n) {
    if (n <= 0) return;
    
    float max, min;
    // Reutiliza a funcao para encontrar o maior valor do vetor
    encontrarExtremos(vet, n, &max, &min);
    
    if (max == 0.0f) return; // Prevencao contra divisao por zero
    
    float *ptr;
    for (ptr = vet; ptr < vet + n; ptr++) {
        // O operador '*' reescreve o valor no endereco de memoria atual
        *ptr = (*ptr) / max;
    }
}

/* Imprime o vetor formatado */
void imprimirVetor(float *vet, int n, const char *titulo) {
    printf("%s", titulo);
    float *ptr;
    for (ptr = vet; ptr < vet + n; ptr++) {
        printf("%.2f ", *ptr);
    }
    printf("\n");
}

int main() {
    float notas[] = {7.5f, 3.2f, 9.8f, 6.0f, 5.5f, 8.1f};
    int n = sizeof(notas) / sizeof(float);

    imprimirVetor(notas, n, "--- VETOR ORIGINAL ---\n");

    float media = calcularMedia(notas, n);
    printf("\nMedia Aritmetica: %.2f\n", media);

    float maximo, minimo;
    // Passagem dos enderecos das variaveis para a funcao sobrescrever os valores
    encontrarExtremos(notas, n, &maximo, &minimo);
    printf("Maior valor: %.2f\n", maximo);
    printf("Menor valor: %.2f\n\n", minimo);

    normalizar(notas, n);

    imprimirVetor(notas, n, "--- VETOR NORMALIZADO ---\n");

    /*
     * DEMONSTRACAO DE ALTERACAO POR REFERENCIA:
     * A funcao 'normalizar' alterou fisicamente o vetor original na main.
     * Isso ocorre porque, em C, ao passar um array como argumento, ele decai
     * para um ponteiro que aponta para o endereco de seu primeiro elemento. 
     * Como as modificacoes na funcao utilizam o operador de desreferenciacao (*ptr),
     * a escrita ocorre diretamente nos blocos de memoria alocados originalmente 
     * pelo escopo chamador, e nao em uma copia local.
     */

    return 0;
}
