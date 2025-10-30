// Nível Novato //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[50];
    char cor_exercito[20];
    int num_tropas;
};

int main() {
    struct Territorio mapa[5];
    int i;

    printf("--- Desafio WAR: Nivel Novato ---\n\n");

    for (i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);

           printf("  Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("  Cor do exercito: ");
        fgets(mapa[i].cor_exercito, sizeof(mapa[i].cor_exercito), stdin);
        mapa[i].cor_exercito[strcspn(mapa[i].cor_exercito, "\n")] = '\0';

        printf("  Numero de tropas: ");
        scanf("%d", &mapa[i].num_tropas);
        while (getchar() != '\n');
    }

    printf("\n--- Estado Atual do Mapa ---\n");
    printf("----------------------------------------------------------------\n");
    printf("| No. | Nome do Territorio | Cor do Exercito | Numero de Tropas |\n");
    printf("----------------------------------------------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("| %-3d | %-18s | %-15s | %-16d |\n", i + 1, mapa[i].nome, mapa[i].cor_exercito, mapa[i].num_tropas);
    }
    printf("----------------------------------------------------------------\n");

    return 0;
}

