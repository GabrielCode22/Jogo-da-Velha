#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"

time_t start_time, end_time; // Variáveis que guardam o começo e o fim do timer
double elapsed_time; // Tempo DURANTE o jogo
char mtz[3][3]; // Variável Global para guardar os locais
int cellSize = 100;
int screenWidth = 600;
int screenHeight = 600;
bool partidaTerminada = false;
int pontuacaoJogadorX = 0;
int pontuacaoJogadorO = 0;

typedef enum GameScreen { MENU = 0, GAME, GAME_PC } GameScreen;

void inicializar_matriz() {
    memset(mtz, ' ', sizeof(mtz)); // Inicializa a matriz com espaços em branco
}

void mostrar_tempo() {
    end_time = time(NULL);
    elapsed_time = difftime(end_time, start_time);
    // printf("\nTempo total de jogo: %.2f segundos\n", elapsed_time);
}

void matriz() {
    int posX = screenWidth / 2 - cellSize * 1.5;
    int posY = screenHeight / 2 - cellSize * 1.5;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            DrawText(TextFormat("%c", mtz[i][j]), posX + j * cellSize + cellSize / 2 - 10, posY + i * cellSize + cellSize / 2 - 10, 40, BLACK);
        }
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
        return 2;
    if (mtz[0][2] == jogador && mtz[1][1] == jogador && mtz[2][0] == jogador)
        return 2;

    return 0;
}

void jogada_computador() {
    // Computador faz uma jogada aleatória
    int linha, coluna;
    do {
        linha = GetRandomValue(0, 2);
        coluna = GetRandomValue(0, 2);
    } while (mtz[linha][coluna] != ' ');

    mtz[linha][coluna] = 'O';
}

void multijogador() {
    int jogadas = 0;
    int linha, coluna;
    char jogador = 'X'; // Começa com o jogador X
    inicializar_matriz();
    start_time = time(NULL);

    int posX = screenWidth / 2 - cellSize * 1.5;
    int posY = screenHeight / 2 - cellSize * 1.5;

    while (jogadas < 9 && !partidaTerminada) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // Ajusta para as coordenadas da matriz
            linha = (mouseY - posY) / cellSize;
            coluna = (mouseX - posX) / cellSize;

            if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && mtz[linha][coluna] == ' ') {
                mtz[linha][coluna] = jogador;
                jogadas++;

                int resultado = verificar_vencedor(jogador);
                if (resultado == 1) {
                    pontuacaoJogadorX += 5; // Incrementa a pontuação do jogador X
                    mostrar_tempo();
                    partidaTerminada = true;
                } else if (resultado == 2) {
                    pontuacaoJogadorX += 10; // Incrementa a pontuação do jogador X
                    mostrar_tempo();
                    partidaTerminada = true;
                }

                // Troca o jogador
                jogador = (jogador == 'X') ? 'O' : 'X';
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha a grade do jogo
        for (int i = 0; i < 4; i++) {
            DrawLine(posX + i * cellSize, posY, posX + i * cellSize, posY + cellSize * 3, BLACK);
            DrawLine(posX, posY + i * cellSize, posX + cellSize * 3, posY + i * cellSize, BLACK);
        }

        matriz();
        DrawText(TextFormat("Tempo de jogo: %.2f segundos", difftime(time(NULL), start_time)), 10, 10, 20, BLACK);

        EndDrawing();
    }

    if (!partidaTerminada) {
        // printf("\n\nJogo empatado!\n");
        mostrar_tempo();
    }
}

void jogar_contra_computador() {
    int jogadas = 0;
    int linha, coluna;
    char jogador = 'X'; // Começa com o jogador X
    inicializar_matriz();
    start_time = time(NULL);
    bool exibirMensagem = false;

    int posX = screenWidth / 2 - cellSize * 1.5;
    int posY = screenHeight / 2 - cellSize * 1.5;

    while (jogadas < 9 && !partidaTerminada) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // Ajusta para as coordenadas da matriz
            linha = (mouseY - posY) / cellSize;
            coluna = (mouseX - posX) / cellSize;

            if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && mtz[linha][coluna] == ' ') {
                mtz[linha][coluna] = jogador;
                jogadas++;

                int resultado = verificar_vencedor(jogador);
                if (resultado == 1) {
                    pontuacaoJogadorX += 5; // Incrementa a pontuação do jogador X
                    exibirMensagem = true;
                    partidaTerminada = true;
                } else if (resultado == 2) {
                    pontuacaoJogadorX += 10; // Incrementa a pontuação do jogador X
                    exibirMensagem = true;
                    partidaTerminada = true;
                }

                // Jogada do computador
                if (!partidaTerminada && jogadas < 9) {
                    jogada_computador();
                    jogadas++;

                    resultado = verificar_vencedor('O');
                    if (resultado == 1) {
                        pontuacaoJogadorO += 5; // Incrementa a pontuação do jogador O
                        exibirMensagem = true;
                        partidaTerminada = true;
                    } else if (resultado == 2) {
                        pontuacaoJogadorO += 10; // Incrementa a pontuação do jogador O
                        exibirMensagem = true;
                        partidaTerminada = true;
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha a grade do jogo
        for (int i = 0; i < 4; i++) {
            DrawLine(posX + i * cellSize, posY, posX + i * cellSize, posY + cellSize * 3, BLACK);
            DrawLine(posX, posY + i * cellSize, posX + cellSize * 3, posY + i * cellSize, BLACK);
        }

        matriz();
        DrawText(TextFormat("Tempo de jogo: %.2f segundos", difftime(time(NULL), start_time)), 10, 10, 20, BLACK);

        if (exibirMensagem) {
            DrawText(TextFormat("Pontuação: Jogador X - %d pontos, Jogador O - %d pontos", pontuacaoJogadorX, pontuacaoJogadorO), screenWidth / 2 - MeasureText("Pontuação: Jogador X - 00 pontos, Jogador O - 00 pontos", 20) / 2, screenHeight / 2, 20, BLACK);
        }

        EndDrawing();
    }

    if (!partidaTerminada) {
        // printf("\n\nJogo empatado!\n");
        mostrar_tempo();
    }
}

int main() {
    InitWindow(screenWidth, screenHeight, "Jogo da Velha com Raylib");
    
    
    SetTargetFPS(60);
    
    InitAudioDevice();
    
    Music teste = LoadMusicStream("Insira o Caminho da Musica");
    
    PlayMusicStream(teste);
    
    GameScreen currentScreen = MENU;

    while (!WindowShouldClose()) {
        UpdateMusicStream(teste);
        if (currentScreen == MENU) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            // Desenha o menu
            DrawText("Jogo da Velha", screenWidth / 2 - MeasureText("Jogo da Velha", 40) / 2, screenHeight / 2 - 50, 40, BLACK);
            DrawText("1. Começar Jogo", screenWidth / 2 - MeasureText("1. Começar Jogo", 20) / 2, screenHeight / 2 + 20, 20, BLACK);
            DrawText("2. Jogar contra o Computador", screenWidth / 2 - MeasureText("2. Jogar contra o Computador", 20) / 2, screenHeight / 2 + 50, 20, BLACK);
            DrawText("3. Sair", screenWidth / 2 - MeasureText("3. Sair", 20) / 2, screenHeight / 2 + 80, 20, BLACK);
            DrawText("Luiz Fernando, Joshuan Estevão, Gabriel Chagas", screenWidth / 2 - MeasureText("Luiz Fernando, Joshuan Estevão, Gabriel Chagas", 20) / 2, screenHeight - 50, 20, BLACK);

            if (IsKeyPressed(KEY_ONE)) {
                currentScreen = GAME;
            } else if (IsKeyPressed(KEY_TWO)) {
                currentScreen = GAME_PC;
            } else if (IsKeyPressed(KEY_THREE)) {
                break;
            }

            EndDrawing();
        } else if (currentScreen == GAME) {
            partidaTerminada = false;
            multijogador();
            currentScreen = MENU;
        } else if (currentScreen == GAME_PC) {
            partidaTerminada = false;
            jogar_contra_computador();
            currentScreen = MENU;
        }
    }

    CloseWindow();
    return 0;
}
