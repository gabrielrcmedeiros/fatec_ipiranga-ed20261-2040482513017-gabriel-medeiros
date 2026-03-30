#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Registradores da pilha HP12c */
float X = 0, Y = 0, Z = 0, T = 0;

/*
 * Função: exibir_pilha
 * Objetivo: Imprimir o estado atual dos quatro registradores no console.
 */
void exibir_pilha(const char* acao) {
    printf("Acao: %-5s -> [ T: %6.2f | Z: %6.2f | Y: %6.2f | X: %6.2f ]\n", acao, T, Z, Y, X);
}

/*
 * Função: empilhar
 * Objetivo: Deslocar os valores na pilha e inserir um novo valor no registrador X.
 */
void empilhar(float valor) {
    T = Z;
    Z = Y;
    Y = X;
    X = valor;
}

/*
 * Função: calcular
 * Objetivo: Executar a operacao matematica entre Y e X, salvar o resultado em X
 * e rebaixar os registradores superiores (Z e T).
 */
void calcular(char operador) {
    float resultado = 0;
    
    switch (operador) {
        case '+': resultado = Y + X; break;
        case '-': resultado = Y - X; break;
        case '*': resultado = Y * X; break;
        case '/': 
            if (X != 0) {
                resultado = Y / X; 
            } else {
                printf("Erro: Divisao por zero.\n");
                return;
            }
            break;
        default:
            printf("Erro: Operador invalido.\n");
            return;
    }
    
    X = resultado;
    Y = Z;
    Z = T;
    T = 0; /* Zera o topo da pilha apos o rebaixamento */
}

/*
 * Função: processar_rpn
 * Objetivo: Receber uma string em formato RPN, validar os tokens e manipular a pilha.
 */
void processar_rpn(char* expressao) {
    printf("Iniciando processamento da expressao RPN: %s\n\n", expressao);
    
    /* Utiliza espaco como delimitador para separar os elementos (tokens) */
    char* token = strtok(expressao, " ");
    
    while (token != NULL) {
        /* Verifica se o token eh um numero (considerando possiveis numeros negativos) */
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            float valor = atof(token);
            empilhar(valor);
            exibir_pilha(token);
        } 
        /* Verifica se o token eh um dos quatro operadores matematicos basicos */
        else if (strlen(token) == 1 && strchr("+-*/", token[0]) != NULL) {
            calcular(token[0]);
            exibir_pilha(token);
        } 
        else {
            printf("Erro: Token nao reconhecido (%s).\n", token);
            return;
        }
        
        token = strtok(NULL, " ");
    }
    
    printf("\nO resultado da expressao algebrica e: %.0f\n", X);
}

int main() {
    /* Expressao RPN fornecida como exemplo na especificacao da atividade */
    char expressao[] = "5 1 2 + 4 * + 3 -";
    
    processar_rpn(expressao);
    
    return 0;
}