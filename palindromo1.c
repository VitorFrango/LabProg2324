/*
Escreva um programa em C  para encontrar palíndromos num ficheiro de texto. Um palíndromo é uma sequência de caracteres 
que se lê da mesma forma, tanto da esquerda para a direita como da direita para a esquerda. Exemplos de palíndromos:
 sacas, rapar, rodador, anilina. Considere apenas palíndromos de comprimentos entre 3 e 10 caracteres
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256

void prepararString(const char* entrada, char* saida, int indices[]) {
    int i = 0, pos = 0;
    while (entrada[pos]) {
        if (isalpha((unsigned char)entrada[pos]) || isdigit((unsigned char)entrada[pos])) { 
            saida[i] = tolower((unsigned char)entrada[pos]);
            indices[i] = pos;
            i++;
        }
        pos++;
    }
    saida[i] = '\0';
}

bool palindromo(const char* palavra, int inicio, int fim) {
    while (fim > inicio) {
        if (palavra[inicio++] != palavra[fim--]) {
            return false;
        }
    }
    return true;
}

void encontrarPalindromos(const char* linha, const char* textoPreparado, int indices[]) {
    int len = strlen(textoPreparado);
    for (int i = 0; i < len; i++) {
        for (int j = len; j > i + 1; j--) {
            if (palindromo(textoPreparado, i, j - 1)) {
                int start = indices[i];
                int end = indices[j - 1];
                // Verifica se o palíndromo encontrado tem mais de um caractere
                if (end - start > 0) {
                    printf("Palíndromo encontrado: ");
                    for (int k = start; k <= end; k++) {
                        printf("%c", linha[k]);
                    }
                    printf("\n");
                    break; // Encontrou o palíndromo mais longo nesta faixa
                }
            }
        }
    }
}

int main() {
    FILE *arquivo = fopen("palindromo.txt", "r");
    char linha[MAX_LINE_LENGTH];
    char textoPreparado[MAX_LINE_LENGTH];
    int indices[MAX_LINE_LENGTH];

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    while (fgets(linha, MAX_LINE_LENGTH, arquivo)) {
        linha[strcspn(linha, "\n")] = 0; // Remove newline character

        prepararString(linha, textoPreparado, indices);
        encontrarPalindromos(linha, textoPreparado, indices);
    }

    fclose(arquivo);
    return 0;
}
