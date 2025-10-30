// Nível Mestre //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5

struct Territorio {
    char nome[50];
    char cor_exercito[20];
    int num_tropas;
};

struct Missao {
    int tipo;
    char descricao[100];
};

void inicializar_territorios(struct Territorio *mapa) {
    strcpy(mapa[0].nome, "Asia");      strcpy(mapa[0].cor_exercito, "Azul");     mapa[0].num_tropas = 5;
    strcpy(mapa[1].nome, "Africa");    strcpy(mapa[1].cor_exercito, "Vermelho"); mapa[1].num_tropas = 4;
    strcpy(mapa[2].nome, "Europa");    strcpy(mapa[2].cor_exercito, "Verde");    mapa[2].num_tropas = 6;
    strcpy(mapa[3].nome, "America");   strcpy(mapa[3].cor_exercito, "Amarelo");  mapa[3].num_tropas = 3;
    strcpy(mapa[4].nome, "Oceania");   strcpy(mapa[4].cor_exercito, "Preto");    mapa[4].num_tropas = 2;
}

void exibir_mapa(const struct Territorio *mapa) {
    printf("\n--- Estado Atual do Mapa ---\n");
    printf("----------------------------------------------------------------\n");
    printf("| No. | Nome do Territorio | Cor do Exercito | Numero de Tropas |\n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("| %-3d | %-18s | %-15s | %-16d |\n", i + 1, mapa[i].nome, mapa[i].cor_exercito, mapa[i].num_tropas);
    }
    printf("----------------------------------------------------------------\n");
}

void inicializar_missao(struct Missao *missao) {
    missao->tipo = rand() % 2 + 1;
    if (missao->tipo == 1) {
        strcpy(missao->descricao, "Destrua o exercito Verde.");
    } else {
        strcpy(missao->descricao, "Conquiste 3 territorios.");
    }
}

void simular_ataque(struct Territorio *atacante, struct Territorio *defensor) {
    int dado_ataque = rand() % 6 + 1;
    int dado_defesa = rand() % 6 + 1;

    printf("\n--- Batalha ---\n");
    printf("Atacante (%s): %d\n", atacante->nome, dado_ataque);
    printf("Defensor (%s): %d\n", defensor->nome, dado_defesa);

    if (dado_ataque >= dado_defesa) {
        printf("Atacante vence! %s perde 1 tropa.\n", defensor->nome);
        defensor->num_tropas--;
        if (defensor->num_tropas == 0) {
            printf("%s foi conquistado por %s!\n", defensor->nome, atacante->nome);
            strcpy(defensor->cor_exercito, atacante->cor_exercito);
            defensor->num_tropas = 1;
        }
    } else {
        printf("Defensor vence! Nenhuma mudanca.\n");
    }
}

int verificar_missao(const struct Missao *missao, const struct Territorio *mapa) {
    if (missao->tipo == 1) {
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor_exercito, "Verde") == 0) {
                return 0;
            }
        }
        return 1;
    } else if (missao->tipo == 2) {
        const char *minha_cor = mapa[0].cor_exercito;
        int territorios_conquistados = 0;
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor_exercito, minha_cor) == 0) {
                territorios_conquistados++;
            }
        }
        return territorios_conquistados >= 3;
    }
    return 0;
}

int main() {
    srand(time(NULL));

    struct Territorio *mapa = calloc(NUM_TERRITORIOS, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro de alocacao de memoria.\n");
        return 1;
    }

    inicializar_territorios(mapa);

    struct Missao missao;
    inicializar_missao(&missao);

    int opcao;
    int atacante_idx, defensor_idx;

    printf("--- Desafio WAR: Nivel Mestre ---\n");
    printf("Sua missao e: %s\n", missao.descricao);

    do {
        exibir_mapa(mapa);
        printf("\n--- Menu Principal ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nEscolha os territorios para a batalha:\n");
                printf("Territorio atacante (1-%d): ", NUM_TERRITORIOS);
                scanf("%d", &atacante_idx);
                printf("Territorio defensor (1-%d): ", NUM_TERRITORIOS);
                scanf("%d", &defensor_idx);
                while (getchar() != '\n');

                if (atacante_idx < 1 || atacante_idx > NUM_TERRITORIOS || defensor_idx < 1 || defensor_idx > NUM_TERRITORIOS || atacante_idx == defensor_idx) {
                    printf("Escolha invalida. Tente novamente.\n");
                    continue;
                }
                
                simular_ataque(&mapa[atacante_idx - 1], &mapa[defensor_idx - 1]);
                printf("\nPressione Enter para continuar...\n");
                getchar();
                break;

            case 2:
                if (verificar_missao(&missao, mapa)) {
                    printf("\nParabens! Missao concluida! Voce venceu o jogo!\n");
                    opcao = 0; // Termina o loop
                } else {
                    printf("\nMissao ainda nao concluida. Continue lutando!\n");
                }
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpcao invalida. Por favor, escolha novamente.\n");
                break;
        }

    } while (opcao != 0);

    free(mapa);
    return 0;
}