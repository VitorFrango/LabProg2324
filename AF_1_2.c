#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
#define MAX_WORDS 50

void prepararString(const char* entrada, char** saida, char* palavras[], int* numPalavras) {
    int pos = 0, palavraPos = 0, i = 0;
    char* palavraAtual = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    *saida = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));

    if (!palavraAtual || !*saida) {
        fprintf(stderr, "Falha na alocação de memória\n");
        free(palavraAtual);
        free(*saida);
        *saida = NULL;
        return;
    }

    while (entrada[pos]) {
        if (isalpha((unsigned char)entrada[pos])) {
            (*saida)[i] = tolower((unsigned char)entrada[pos]);
            palavraAtual[palavraPos++] = (*saida)[i];
            i++;
        } else if (palavraPos > 0) {
            palavraAtual[palavraPos] = '\0';
            if (palavraPos > 0) { // Alterado para capturar todas as palavras.
                palavras[*numPalavras] = strdup(palavraAtual);
                (*numPalavras)++;
            }
            palavraPos = 0;
        }
        pos++;
    }

    if (palavraPos > 0) {
        palavraAtual[palavraPos] = '\0';
        palavras[*numPalavras] = strdup(palavraAtual);
        (*numPalavras)++;
    }

    (*saida)[i] = '\0';
    free(palavraAtual);
}

bool palindromo(const char* palavra) {
    int inicio = 0;
    int fim = strlen(palavra) - 1;
    while (inicio < fim) {
        if (palavra[inicio++] != palavra[fim--]) {
            return false;
        }
    }
    return true;
}

void encontrarPalindromos(char* palavras[], int numPalavras) {
    for (int i = 0; i < numPalavras; i++) {
        for (int j = i; j < numPalavras; j++) {
            char* combinacao = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
            char* combinacaoOriginal = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
            if (!combinacao || !combinacaoOriginal) {
                fprintf(stderr, "Falha na alocação de memória\n");
                free(combinacao);
                free(combinacaoOriginal);
                return;
            }

            combinacao[0] = '\0';
            combinacaoOriginal[0] = '\0';

            for (int k = i; k <= j; k++) {
                strcat(combinacao, palavras[k]);
                if (k > i) {
                    strcat(combinacaoOriginal, " ");
                }
                strcat(combinacaoOriginal, palavras[k]);
            }
            if (palindromo(combinacao)) {
                printf("Combinação encontrada: %s / Combinação original: %s\n", combinacao, combinacaoOriginal);
            }

            free(combinacao);
            free(combinacaoOriginal);
        }
    }
}

int main() {
    FILE *arquivo = fopen("palindromo.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char* palavras[MAX_WORDS];
    int numPalavras = 0;

    char linha[MAX_LINE_LENGTH];
    while (fgets(linha, MAX_LINE_LENGTH, arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        char* textoPreparado;
        prepararString(linha, &textoPreparado, palavras, &numPalavras);
        free(textoPreparado); // Libera memória do texto preparado, não mais necessário.
    }

    if (numPalavras > 0) {
        encontrarPalindromos(palavras, numPalavras);
    }

    for (int i = 0; i < numPalavras; i++) {
        free(palavras[i]);
    }

    fclose(arquivo);
    return 0;
}