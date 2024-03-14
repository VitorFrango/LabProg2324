/*
Escreva um programa para converter um número em numeração romana para a notação decimal. Ex. MCMLXXIX = 1979.
Implemente um adequado tratamento de erros, que informe o utilizador, de forma clara, sobre o erro que cometeu na escrita do numeral romano (ex. usou uma letra não permitida como "P")
*/

#include <stdio.h>
#include <string.h>

// Função para converter numeral romano individual para seu valor decimal.
int valorRomanoParaDecimal(char r) {
    switch (r) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return -1;  // Retorna -1 se o caracter não for um numeral romano válido.
    }
}


// Função para verificar a validade do numeral romano e convertê-lo para decimal.
int romanoParaDecimal(const char* romano) {
    int total = 0;
    int len = strlen(romano);

    for (int i = 0; i < len; i++) {
        // Obter valor do numeral romano atual e do próximo.
        int valorAtual = valorRomanoParaDecimal(romano[i]);
        int valorProximo = (i + 1 < len) ? valorRomanoParaDecimal(romano[i + 1]) : 0;

        if (valorAtual < 0) {
            printf("Erro: Caractere inválido '%c' encontrado.\n", romano[i]);
            return -1;
        }

        // Comparar o numeral atual com o próximo para decidir se soma ou subtrai.
        if (valorAtual < valorProximo) {
            total += (valorProximo - valorAtual);
            i++;  // Pular o próximo numeral, pois já foi processado.
        } else {
            total += valorAtual;
        }
    }

    return total;
}

int main() {
     char romano[1000];
     printf("Digite o número romano: ");
     scanf("%s", romano);

     // Função que verifica se caracter é maisuculo
     for (size_t i = 0; i < strlen(romano); i++) {
         if (romano[i] >= 'a' && romano[i] <= 'z') {
             printf("Erro: Caractere inválido '%c' encontrado.\n", romano[i]);
             return -1;
         }
     }

     int resultado = romanoParaDecimal(romano);

     if (resultado != -1) {
         printf("O número decimal é %d\n", resultado);
     }

     return 0;
}
