#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <windows.h>

#ifdef _WIN32
#include <conio.h> 
#define sleep(x) Sleep(1000 * (x)) 
#else
#include <termios.h>
#include <fcntl.h>
#endif

time_t start_time, end_time;
double elapsed_time;
char mtz[3][3]; // Matriz do jogo da velha

void inicializar_matriz();

void cronometro() {
    char command;
    time_t start, end;
    double elapsed = 0.0;
    int running = 0;
    
    while (1) {
        if (running) {
            end = time(NULL);
            elapsed = difftime(end, start);
        }

        printf("\rTempo: %.2f segundos", elapsed);
        fflush(stdout); 

        #ifdef _WIN32
        if (_kbhit()) {
            command = _getch();
        #else
        if (kbhit()) {
            command = getchar();
        #endif
            if (command == 's') {
                if (running) {
                    running = 0;
                } else {
                    start = time(NULL);
                    running = 1;
                }
            } else if (command == 'r') {
                elapsed = 0.0;
                running = 0;
            } else if (command == 'q') {
                break;
            }
        }

        sleep(1); 
    }

    printf("\n");
}

void espacar() {
    int i;
    for (i = 0; i < 4; i++) {
        putchar('\t');
    }
}

void inicializar_matriz() {
    int i, j;
    // Inicializa a matriz com espaços em branco
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            mtz[i][j] = ' ';
        }
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
    
    // Verifica linhas e colunas
    for (i = 0; i < 3; i++) {
        if (mtz[i][0] == jogador && mtz[i][1] == jogador && mtz[i][2] == jogador)
            return 1;
        if (mtz[0][i] == jogador && mtz[1][i] == jogador && mtz[2][i] == jogador)
            return 1;
    }
    
    // Verifica diagonais
    if (mtz[0][0] == jogador && mtz[1][1] == jogador && mtz[2][2] == jogador)
        return 1;
    if (mtz[0][2] == jogador && mtz[1][1] == jogador && mtz[2][0] == jogador)
        return 1;
    
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
        system("cls"); // Limpa a tela (funciona no Windows, pode variar em outros sistemas)
        matriz();

        printf("\nJogador %c, digite a linha e coluna para sua jogada (formato: linha coluna): ", jogador);
        scanf("%d %d", &linha, &coluna);

        // Verifica se a posição é válida e está vazia
        if (linha >= 1 && linha <= 3 && coluna >= 1 && coluna <= 3 && mtz[linha-1][coluna-1] == ' ') {
            mtz[linha-1][coluna-1] = jogador;
            jogadas++;

            // Verifica se o jogador atual venceu
            if (verificar_vencedor(jogador)) {
                system("cls");
                matriz();
                printf("\n\nParabéns! Jogador %c venceu!\n", jogador);
                break;
            }

            // Troca o jogador
            jogador = (jogador == 'X') ? 'O' : 'X';
        } else {
            printf("\nJogada inválida! Tente novamente.\n");
        }

    } while (jogadas < 9); // O jogo acaba depois de 9 jogadas

    // Finaliza o cronômetro
    end_time = time(NULL);
    elapsed_time = difftime(end_time, start_time);

    if (jogadas == 9) {
        system("cls");
        matriz();
        printf("\n\nJogo empatado!\n");
    }

    // Mostra o tempo decorrido
    printf("\nTempo total de jogo: %.2f segundos\n", elapsed_time);
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
                if (verificar_vencedor(jogador)) {
                    system("cls");
                    matriz();
                    printf("\n\nParabéns! Jogador %c venceu!\n", jogador);
                    break;
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
                system("cls");
                matriz();
                printf("\n\nO computador venceu!\n");
                break;
            }
            
            // Troca o jogador
            jogador = 'X';
        }
        
    } while (jogadas < 9); // O jogo acaba depois de 9 jogadas
    
    // Finaliza o cronômetro
    end_time = time(NULL);
    elapsed_time = difftime(end_time, start_time);
    
    // Exibe o tempo total de jogo
    printf("\nTempo total de jogo: %.2f segundos\n", elapsed_time);
    
    if (jogadas == 9) {
        system("cls");
        matriz();
        printf("\n\nJogo empatado!\n");
    }
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
            system("cls");
            multijogador();
            break;
        case '2':
            system("cls");
            jogar_contra_computador();
            break;
        case '3':
            system("cls");
            espacar();
            printf(" Luiz Fernando | Joshuan Estevão | Gabriel Chagas\n");
            break;
        default:
            printf("Opção inválida.\n");
    }

    return 0;
}
