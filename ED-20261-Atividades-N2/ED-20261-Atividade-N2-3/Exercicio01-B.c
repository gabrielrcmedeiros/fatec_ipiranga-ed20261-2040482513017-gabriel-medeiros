// RA: 2040482513017 - Gabriel Reinaldo Chagas de Medeiros

#include <stdio.h>

int main() {
    int v[] = {10, 20, 30, 40, 50};
    
    // Calculo do tamanho do vetor dividindo o tamanho total em bytes pelo tamanho do tipo de dado.
    int n = sizeof(v) / sizeof(int); 
    
    // Declaracao de ponteiro auxiliar para iterar pelos enderecos do vetor.
    int *ptr;

    printf("--- a) ELEMENTOS E ENDERECOS ---\n");
    // O laco itera por meio da aritmetica de ponteiros (ptr++), sem utilizacao de indices numerais.
    for (ptr = v; ptr < v + n; ptr++) {
        // O operador '*' (desreferenciacao) acessa o valor contido no endereco apontado por 'ptr'.
        printf("Valor: %d | Endereco: %p\n", *ptr, (void*)ptr);
    }

    printf("\n--- b) SOMA DOS ELEMENTOS ---\n");
    int soma = 0;
    // O ponteiro 'ptr' e redefinido para o endereco base do vetor para uma nova iteracao.
    for (ptr = v; ptr < v + n; ptr++) {
        // O operador '*' extrai o valor do bloco de memoria atual para ser acumulado na variavel 'soma'.
        soma += *ptr;
    }
    printf("Soma total: %d\n", soma);

    printf("\n--- c) INVERSAO IN-PLACE ---\n");
    // 'inicio' recebe o endereco base do vetor (primeiro elemento).
    int *inicio = v;
    
    // 'fim' recebe o endereco do ultimo elemento somando (n-1) ao endereco base.
    int *fim = v + n - 1;

    // A estrutura condicional garante a execucao ate que os enderecos se encontrem no centro lógico da alocação.
    while (inicio < fim) {
        // O operador '*' acessa o valor no endereco de 'inicio' e o armazena na variavel temporaria de troca.
        int temp = *inicio;
        
        // Os operadores '*' leem o valor contido em 'fim' e sobrescrevem a regiao de memoria apontada por 'inicio'.
        *inicio = *fim;
        
        // O operador '*' grava o valor mantido em memoria temporaria na regiao apontada por 'fim'.
        *fim = temp;
        
        // Aritmetica de ponteiros: 'inicio' avanca para o proximo bloco, 'fim' recua para o bloco anterior.
        inicio++;
        fim--;
    }

    printf("Vetor invertido: ");
    for (ptr = v; ptr < v + n; ptr++) {
        // O operador '*' acessa a nova sequencia de valores diretamente das posicoes fisicas invertidas.
        printf("%d ", *ptr);
    }
    printf("\n");

    return 0;
}
