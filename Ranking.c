#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 100
#define NAME_LENGTH 50

typedef struct {
    char name[NAME_LENGTH];
    int score;
} Player;

void addPlayer(Player players[], int *numPlayers, const char *name, int score) {
    if (*numPlayers < MAX_PLAYERS) {
        strncpy(players[*numPlayers].name, name, NAME_LENGTH - 1);
        players[*numPlayers].name[NAME_LENGTH - 1] = '\0';  // Ensure null-termination
        players[*numPlayers].score = score;
        (*numPlayers)++;
    } else {
        printf("Limite máximo de jogadores atingido!\n");
    }
}

int comparePlayers(const void *a, const void *b) {
    Player *playerA = (Player *)a;
    Player *playerB = (Player *)b;
    return playerB->score - playerA->score;  // Ordem decrescente
}

void printRanking(const Player players[], int numPlayers) {
    printf("Ranking dos Jogadores:\n");
    int i;
    for (i = 0; i < numPlayers; i++) {
        printf("%d. %s - %d pontos\n", i + 1, players[i].name, players[i].score);
    }
}

int main() {
    Player players[MAX_PLAYERS];
    int numPlayers = 0;
    int opcao;

    do {
        printf("1. Adicionar Jogador\n");
        printf("2. Exibir Ranking\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            char name[NAME_LENGTH];
            int score;
            printf("Nome do jogador: ");
            scanf("%s", name);
            printf("Pontuacao do jogador: ");
            scanf("%d", &score);
            addPlayer(players, &numPlayers, name, score);
        } else if (opcao == 2) {
            qsort(players, numPlayers, sizeof(Player), comparePlayers);
            printRanking(players, numPlayers);
        }
    } while (opcao != 3);

    return 0;
}
