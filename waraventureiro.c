// Nível Aventureiro //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio {
    char nome[50];
    char cor_exercito[20];
    int num_tropas;
};

void exibir_mapa(struct Territorio *mapa, int num_territorios) {
    printf("\n--- Estado Atual do Mapa ---\n");
    printf("----------------------------------------------------------------\n");
    printf("| No. | Nome do Territorio | Cor do Exercito | Numero de Tropas |\n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < num_territorios; i++) {
        printf("| %-3d | %-18s | %-15s | %-16d |\n",
               i + 1, mapa[i].nome, mapa[i].cor_exercito, mapa[i].num_tropas);
    }
    printf("----------------------------------------------------------------\n");
}

void simular_batalha(struct Territorio *atacante, struct Territorio *defensor) {
    int dado_ataque = rand() % 6 + 1;
    int dado_defesa = rand() % 6 + 1;

    printf("\n--- Batalha ---\n");
    printf("Atacante (%s - %s): %d\n", atacante->nome, atacante->cor_exercito, dado_ataque);
    printf("Defensor (%s - %s): %d\n", defensor->nome, defensor->cor_exercito, dado_defesa);

    if (dado_ataque >= dado_defesa) {
        printf("Atacante vence! %s perde 1 tropa.\n", defensor->nome);
        defensor->num_tropas--;

        if (defensor->num_tropas <= 0) {
            printf("%s foi conquistado por %s!\n", defensor->nome, atacante->nome);
            strcpy(defensor->cor_exercito, atacante->cor_exercito);
            defensor->num_tropas = 1; // Nova ocupação
            if (atacante->num_tropas > 1) atacante->num_tropas--; // Move uma tropa
        }
    } else {
        printf("Defensor vence! Nenhuma mudanca.\n");
    }
}

int main() {
    srand(time(NULL));

    int num_territorios = 5;
    struct Territorio *mapa = calloc(num_territorios, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return 1;
    }

    printf("--- Desafio WAR: Nivel Aventureiro ---\n\n");

    // limpar o buffer antes de fgets
    while (getchar() != '\n' && !feof(stdin));

    for (int i = 0; i < num_territorios; i++) {
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

    int atacante_idx, defensor_idx;
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        exibir_mapa(mapa, num_territorios);

        printf("\nEscolha os territorios para a batalha:\n");
        printf("Territorio atacante (1-%d): ", num_territorios);
        scanf("%d", &atacante_idx);
        printf("Territorio defensor (1-%d): ", num_territorios);
        scanf("%d", &defensor_idx);
        while (getchar() != '\n');

        if (atacante_idx < 1 || atacante_idx > num_territorios ||
            defensor_idx < 1 || defensor_idx > num_territorios ||
            atacante_idx == defensor_idx) {
            printf("Escolha invalida. Tente novamente.\n");
            continue;
        }

        simular_batalha(&mapa[atacante_idx - 1], &mapa[defensor_idx - 1]);

        printf("\nContinuar batalhando? (s/n): ");
        scanf(" %c", &continuar);

        // limpar tela (opcional)
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    free(mapa);
    printf("\nJogo encerrado. Ate a proxima aventura!\n");
    return 0;
}