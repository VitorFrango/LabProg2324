/*
Escreva um programa para encontrar palíndromos num ficheiro de texto. Um palíndromo é uma sequência de caracteres que se lê da mesma forma, 
tanto da esquerda para a direita como da direita para a esquerda. Exemplos de palíndromos: sacas, rapar, rodador, anilina. Considere apenas 
palíndromos de comprimentos entre 3 e 10 caracteres.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Declarraçao da funçao que verifica se uma palavra é palindromo

int palindromo(char *palavra){
    size_t inicio = 0; 
    size_t fim = strlen(palavra) - 1;

    while(inicio < fim){
        if(palavra[inicio] != palavra[fim]){
        return 0;   // Se a palavra nao for palindromo

    }
    inicio++;
    fim--;
}
return 1; // Se a palavra for palindromo
}


// Funçao que limpa texto e e converte opara minusculas
void limpar_texto(char *palavra){
    char temp[MAX];
    int j = 0;

    for (int i = 0; palavra[i]; i++) {
        if(isalpha(palavra[i])){
            temp[j++]  = (char)tolower((unsigned char)palavra[i]);
        }
    }

    temp[j] = '\0';
    strcpy(palavra, temp);
}

int main(void){
    FILE *file;
    char palavra[MAX];

    file = fopen("palindromos.txt", "r");
    if(file == NULL){
        printf("Erro ao abrir o ficheiro");
        return -1; 
    }
    while(fscanf(file, "%s", palavra) != EOF){
        limpar_texto(palavra);
        if (strlen(palavra) >= 3 && strlen(palavra) <= 10 && palindromo(palavra)){
            printf("%s\n", palavra);
        }
    }

    fclose(file);
    return 0;
}
