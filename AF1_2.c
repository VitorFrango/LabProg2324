#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PALAVRAS 1000
#define MAX_COMPRIMENTO_PALAVRA 100

void lerTextoDoArquivo(char nomeArquivo[], char **texto) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    *texto = malloc(1);  // Inicializando com tamanho 1 para '\0'
    **texto = '\0';      // Inicializando a string vazia

    char linha[MAX_COMPRIMENTO_PALAVRA];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        *texto = (char *)realloc(*texto, (strlen(*texto) + strlen(linha) + 1));
        if (*texto == NULL) {
            printf("Erro ao realocar memória.\n");
            exit(1);
        }
        strcat(*texto, linha);
    }

    fclose(arquivo);
}

void limpaTexto(char *s, char **sLimpa) {
    int i, j = 0;
    *sLimpa = (char *)malloc((strlen(s) + 1)); 
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
    printf("Texto limpo: %s\n", *sLimpa);
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

    char combinacaoAnterior[MAX_COMPRIMENTO_PALAVRA];
    strcpy(combinacaoAnterior, combinacao);

    strcat(combinacao, palavras[inicio]);
    gerar_combinacoes(palavras, originais, inicio + 1, fim, combinacao);

    strcpy(combinacao, combinacaoAnterior);
    gerar_combinacoes(palavras, originais, inicio + 1, fim, combinacao);
}

int main() {
    char *texto = NULL;
    char *textoLimpo = NULL;
    char *palavras[MAX_PALAVRAS];
    char *originais[MAX_PALAVRAS];
    int tamanho = 0;

    lerTextoDoArquivo("palindromo.txt", &texto);
    limpaTexto(texto, &textoLimpo);
    free(texto);  // Libera a memória alocada para o texto original

    const char *token = strtok(textoLimpo, " ");

    while (token != NULL && tamanho < MAX_PALAVRAS) {
        palavras[tamanho] = (char *)malloc((strlen(token) + 1) * sizeof(char));
        originais[tamanho] = (char *)malloc((strlen(token) + 1) * sizeof(char));
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

    // Liberando memória alocada
    for (int i = 0; i < tamanho; i++) {
        free(palavras[i]);
        free(originais[i]);
    }
    free(textoLimpo);

    return 0;
}
