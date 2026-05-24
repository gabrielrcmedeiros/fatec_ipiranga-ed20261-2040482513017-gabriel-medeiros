// RA: 2040482513017 - Gabriel Reinaldo Chagas de Medeiros

#include <stdio.h>

/* Funcao que troca os valores apontados por a e b usando apenas aritmetica de ponteiros */
void trocar(int *a, int *b) {
    // O operador '*' acessa os valores nos enderecos 'a' e 'b'. O valor armazenado em '*a' recebe a soma de ambos.
    *a = *a + *b;
    
    // O operador '*' altera o valor no endereco 'b', atribuindo a subtracao da soma total (*a) pelo valor atual de '*b'.
    *b = *a - *b;
    
    // O operador '*' altera o valor no endereco 'a', atribuindo a subtracao da soma total (*a) pelo novo valor de '*b'.
    *a = *a - *b;
}

int main() {
    int x = 15;
    int y = 42;

    printf("--- ANTES DA TROCA ---\n");
    
    // O operador '&' extrai o endereco de memoria de 'x' para ser lido e impresso pelo especificador %p.
    printf("Variavel x: Valor = %d | Endereco = %p\n", x, (void*)&x);
    
    // O operador '&' extrai o endereco de memoria de 'y' para ser lido e impresso pelo especificador %p.
    printf("Variavel y: Valor = %d | Endereco = %p\n", y, (void*)&y);

    // O operador '&' captura os enderecos de 'x' e 'y', passando-os como parametros por referencia para a funcao 'trocar'.
    trocar(&x, &y);

    printf("\n--- DEPOIS DA TROCA ---\n");
    
    // O operador '&' extrai o endereco de 'x' novamente para demonstrar que a alocacao fisica nao foi alterada.
    printf("Variavel x: Valor = %d | Endereco = %p\n", x, (void*)&x);
    
    // O operador '&' extrai o endereco de 'y' novamente para demonstrar que a alocacao fisica nao foi alterada.
    printf("Variavel y: Valor = %d | Endereco = %p\n", y, (void*)&y);

    return 0;
}
