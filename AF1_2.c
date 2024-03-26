#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALAVRAS 1000
#define MAX_COMPRIMENTO_PALAVRA 100

void lerTextoDoArquivo(const char nomeArquivo[], char **texto) {
    FILE *arquivo = fopen(nomeArquivo, "r");  // Use the function parameter
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        *texto = NULL;
        return;
    }

    *texto = (char *)malloc(1);
    if (*texto == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        exit(1);
    }
    **texto = '\0';

    char linha[MAX_COMPRIMENTO_PALAVRA];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *temp = (char *)realloc(*texto, strlen(*texto) + strlen(linha) + 1);
        if (temp == NULL) {
            printf("Erro ao realocar memória.\n");
            free(*texto);
            fclose(arquivo);
            exit(1);
        }
        *texto = temp;
        strcat(*texto, linha);
    }
    fclose(arquivo);
}

void limpaTexto(char *s, char **sLimpa) {
    int i, j = 0;
    *sLimpa = (char *)malloc(strlen(s) + 1); 
    if (*sLimpa == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    for (i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i]) || s[i] == ' ') {
            (*sLimpa)[j++] = tolower(s[i]);
        }
    }
    (*sLimpa)[j] = '\0';
}

int testaPalindromo(char *s) {
    int i;
    int Nreal = strlen(s);
    for (i = 0; i < Nreal / 2; i++) {
        if (s[i] != s[Nreal - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

void gerar_combinacoes(char **palavras, char **originais, int inicio, int fim, char *combinacao) {
    size_t combinacaoLen = strlen(combinacao);
    size_t spaceLeft = MAX_COMPRIMENTO_PALAVRA - combinacaoLen - 1;

    if (inicio == fim) {
        if (strlen(combinacao) >= 3 && testaPalindromo(combinacao)) {
            printf("Combinação encontrada: %s / Combinação original: ", combinacao);
            for (int i = 0; i < fim; i++) {
                if (strstr(combinacao, palavras[i]) != NULL) {
                    printf("%s ", originais[i]);
                }
            }
            printf("\n");
        }
        return;
    }

    if (strlen(palavras[inicio]) <= spaceLeft) {
        strncat(combinacao, palavras[inicio], spaceLeft);
        gerar_combinacoes(palavras, originais, inicio + 1, fim, combinacao);
        combinacao[combinacaoLen] = '\0';
    }

    gerar_combinacoes(palavras, originais, inicio + 1, fim, combinacao);
}

int main() {
    char *texto = NULL;
    char *textoLimpo = NULL;
    char *palavras[MAX_PALAVRAS];
    char *originais[MAX_PALAVRAS];
    int tamanho = 0;

    lerTextoDoArquivo("palindromos.txt", &texto);
    if (texto == NULL) {
        return 1;
    }

    limpaTexto(texto, &textoLimpo);
    free(texto);

    const char *token = strtok(textoLimpo, " ");
    while (token != NULL && tamanho < MAX_PALAVRAS) {
        palavras[tamanho] = (char *)malloc(strlen(token) + 1);
        originais[tamanho] = (char *)malloc(strlen(token) + 1);
        if (palavras[tamanho] == NULL || originais[tamanho] == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }
        strcpy(palavras[tamanho], token);
        strcpy(originais[tamanho], token);
        tamanho++;
        token = strtok(NULL, " ");
    }

    char combinacao[MAX_COMPRIMENTO_PALAVRA] = "";
    gerar_combinacoes(palavras, originais, 0, tamanho, combinacao);

    for (int i = 0; i < tamanho; i++) {
        free(palavras[i]);
        free(originais[i]);
    }
    free(textoLimpo);

    return 0;
}
