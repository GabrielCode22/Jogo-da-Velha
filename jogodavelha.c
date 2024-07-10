#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#else
#endif

time_t start_time, end_time; //Aqui são variáveis que guardam o começo e o fim do timer
double elapsed_time; //Aqui  o tempo DURANTE o jogo
char mtz[3][3]; // Váriável Global para guardar os locais

void inicializar_matriz() {
    int i, j;
    // Inicializa a matriz com espaços em branco
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mtz[i][j] = ' ';
        }
    }
}

void mostrar_tempo() {
    end_time = time(NULL);
    elapsed_time = difftime(end_time, start_time);
    printf("\nTempo total de jogo: %.2f segundos\n", elapsed_time);
}

void espacar() {
    int i;
    for (i = 0; i < 4; i++) {
        putchar('\t');
    }
}
void matriz() {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("|- %c -|", mtz[i][j]);
        }
        printf("\n");
    }
}

int verificar_vencedor(char jogador) {
    int i;
    
    // Olha as linhas e colunas
    for (i = 0; i < 3; i++) {
        if (mtz[i][0] == jogador && mtz[i][1] == jogador && mtz[i][2] == jogador)
            return 1;
        if (mtz[0][i] == jogador && mtz[1][i] == jogador && mtz[2][i] == jogador)
            return 1;
    }
    
    // Olha as diagonais
    if (mtz[0][0] == jogador && mtz[1][1] == jogador && mtz[2][2] == jogador)
        return 2;
    if (mtz[0][2] == jogador && mtz[1][1] == jogador && mtz[2][0] == jogador)
        return 2;
    
    return 0;
}

void multijogador() {
    int jogadas = 0;
    int linha, coluna;
    char jogador = 'X'; // Começa com o jogador X

    inicializar_matriz();

    // Inicializa o cronômetro
    start_time = time(NULL);

    do {
        system("cls");
        matriz();

        printf("\nTempo de jogo: %.2f segundos\n", difftime(time(NULL), start_time));
        
        printf("\nJogador %c, digite a linha e coluna para sua jogada (formato: linha coluna): ", jogador);
        scanf("%d %d", &linha, &coluna);

        // Verifica se a posição é válida e está vazia
        if (linha >= 1 && linha <= 3 && coluna >= 1 && coluna <= 3 && mtz[linha-1][coluna-1] == ' ') {
            mtz[linha-1][coluna-1] = jogador;
            jogadas++;

            if (verificar_vencedor(jogador) == 1) {
                system("cls");
                matriz();
                printf("\n\nParabéns! Jogador %c venceu!\n Por vencer normalente, sua pontuação nessa partida foi de 5 pontos", jogador);
                 mostrar_tempo();
                 return;
            } else if (verificar_vencedor(jogador) == 2) {
                system("cls");
                matriz();
                printf("\n\nParabéns! Jogador %c venceu!\n Por vencer com o uso das diagonais, sua pontuação nessa partida foi de 10 pontos", jogador);
                mostrar_tempo();
                return;
                }

            // Troca o jogador
            jogador = (jogador == 'X') ? 'O' : 'X';
        } else {
            printf("\nJogada inválida! Tente novamente.\n");
        }

    } while (jogadas < 9); // O jogo acaba depois de 9 jogadas

    if (jogadas == 9) {
        matriz();
        printf("\n\nJogo empatado!\n");
    }

    mostrar_tempo();
}

void jogar_contra_computador() {
    int jogadas = 0;
    int linha, coluna;
    char jogador = 'X';
    
    inicializar_matriz();
    
    // Inicializa o cronômetro
    start_time = time(NULL);

    do {
        system("cls");
        matriz();
        
        // Mostra o cronômetro após cada jogada
        printf("\nTempo de jogo: %.2f segundos\n", difftime(time(NULL), start_time));
        
        if (jogador == 'X') {
            // Jogador humano
            printf("\nJogador %c, digite a linha e coluna para sua jogada (formato: linha coluna): ", jogador);
            scanf("%d %d", &linha, &coluna);
            
            // Verifica se a posição é válida e está vazia
            if (linha >= 1 && linha <= 3 && coluna >= 1 && coluna <= 3 && mtz[linha-1][coluna-1] == ' ') {
                mtz[linha-1][coluna-1] = jogador;
                jogadas++;
                
                // Verifica se o jogador atual venceu
                if (verificar_vencedor(jogador) == 1) {
                    system("cls");
                    matriz();
                    printf("\n\nParabéns! Jogador %c venceu!\n Por vencer normalente, sua pontuação nessa partida foi de 5 pontos", jogador);
                    mostrar_tempo();
                    return;
                } else if (verificar_vencedor(jogador) == 2) {
                    system("cls");
                    matriz();
                    printf("\n\nParabéns! Jogador %c venceu!\n Por vencer com o uso das diagonais, sua pontuação nessa partida foi de 10 pontos", jogador);
                    mostrar_tempo();
                    return;
                }
                // Troca o jogador
                jogador = 'O';
            } else {
                printf("\nJogada inválida! Tente novamente.\n");
            }
        } else {
            // Computador
            do {
                linha = rand() % 3;
                coluna = rand() % 3;
            } while (mtz[linha][coluna] != ' '); // Continua tentando até encontrar uma posição vazia
            
            mtz[linha][coluna] = jogador;
            jogadas++;
            
            // Verifica se o jogador atual venceu
            if (verificar_vencedor(jogador)) {
                
                matriz();
                printf("\n\nO computador venceu!\n");
                mostrar_tempo();
                return;
            }
            
            // Troca o jogador
            jogador = 'X';
        }
        
    } while (jogadas < 9); // O jogo acaba depois de 9 jogadas
    
    if (jogadas == 9) {
        matriz();
        printf("\n\nJogo empatado!\n");
    }
    
    mostrar_tempo();
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    char op;

    espacar();
    printf("Bem vindo ao Jogo da Velha!\n\n");
    espacar();
    printf("  Selecionar modo de jogo:\n\n\n\n");
    espacar();
    printf("1 - Multijogador\n\n");
    espacar();
    printf("2 - Jogar contra o computador\n\n");
    espacar();
    printf("3 - Ver Créditos\n\n");
    espacar();
    scanf(" %c", &op);
    
    switch (op) {
        case '1':
            multijogador();
            break;
        case '2':
            jogar_contra_computador();
            break;
        case '3':
            espacar();
            printf(" Luiz Fernando | Joshuan Estevão | Gabriel Chagas\n");
            break;
        default:
            printf("Opção inválida.\n");
    }

    return 0;
}
