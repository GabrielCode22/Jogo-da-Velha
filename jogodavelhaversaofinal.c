#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"

time_t start_time, end_time;
double elapsed_time;
char mtz[3][3];
int cellSize = 100;
int screenWidth = 600;
int screenHeight = 600;
bool partidaTerminada = false;
int pontuacaoJogadorX = 0;
int pontuacaoJogadorO = 0;

char nomeJogadorX[30] = "Jogador X";
char nomeJogadorO[30] = "Jogador O";

typedef enum GameScreen { MENU = 0, GAME, GAME_PC } GameScreen;

void inicializar_matriz() {
    memset(mtz, ' ', sizeof(mtz));
}

void mostrar_tempo() {
    end_time = time(NULL);
    elapsed_time = difftime(end_time, start_time);
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
    for (int i = 0; i < 3; i++) {
        if (mtz[i][0] == jogador && mtz[i][1] == jogador && mtz[i][2] == jogador)
            return 1;
        if (mtz[0][i] == jogador && mtz[1][i] == jogador && mtz[2][i] == jogador)
            return 1;
    }
    if (mtz[0][0] == jogador && mtz[1][1] == jogador && mtz[2][2] == jogador)
        return 1;
    if (mtz[0][2] == jogador && mtz[1][1] == jogador && mtz[2][0] == jogador)
        return 1;
    return 0;
}

void jogada_computador() {
    int linha, coluna;
    do {
        linha = GetRandomValue(0, 2);
        coluna = GetRandomValue(0, 2);
    } while (mtz[linha][coluna] != ' ');

    mtz[linha][coluna] = 'O';
}

void exibir_mensagem_vencedor(const char* mensagem) {
    while (!IsKeyPressed(KEY_ENTER) && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(mensagem, screenWidth / 2 - MeasureText(mensagem, 40) / 2, screenHeight / 2, 40, BLACK);
        DrawText("Pressione ENTER para voltar ao menu", screenWidth / 2 - MeasureText("Pressione ENTER para voltar ao menu", 20) / 2, screenHeight / 2 + 50, 20, BLACK);
        EndDrawing();
    }
}

void multijogador() {
    int jogadas = 0;
    char jogador = 'X';
    inicializar_matriz();
    start_time = time(NULL);

    while (jogadas < 9 && !partidaTerminada) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            int linha = (mouseY - (screenHeight / 2 - cellSize * 1.5)) / cellSize;
            int coluna = (mouseX - (screenWidth / 2 - cellSize * 1.5)) / cellSize;

            if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && mtz[linha][coluna] == ' ') {
                mtz[linha][coluna] = jogador;
                jogadas++;

                int resultado = verificar_vencedor(jogador);
                if (resultado > 0) {
                    if (jogador == 'X') {
                        pontuacaoJogadorX += 5;
                    } else {
                        pontuacaoJogadorO += 5;
                    }
                    partidaTerminada = true;
                }

                jogador = (jogador == 'X') ? 'O' : 'X';
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        matriz();

        for (int i = 0; i < 4; i++) {
            DrawLine((screenWidth / 2 - cellSize * 1.5) + i * cellSize, screenHeight / 2 - cellSize * 1.5, 
                     (screenWidth / 2 - cellSize * 1.5) + i * cellSize, screenHeight / 2 + cellSize * 1.5, BLACK);
            DrawLine(screenWidth / 2 - cellSize * 1.5, (screenHeight / 2 - cellSize * 1.5) + i * cellSize, 
                     screenWidth / 2 + cellSize * 1.5, (screenHeight / 2 - cellSize * 1.5) + i * cellSize, BLACK);
        }

        DrawText(TextFormat("Tempo de jogo: %.2f segundos", difftime(time(NULL), start_time)), 10, 10, 20, BLACK);
        EndDrawing();
    }

    if (partidaTerminada) {
        if (jogador == 'X') {
            exibir_mensagem_vencedor(TextFormat("%s venceu!", nomeJogadorO));
        } else {
            exibir_mensagem_vencedor(TextFormat("%s venceu!", nomeJogadorX));
        }
    } else {
        exibir_mensagem_vencedor("Empate!");
    }
}

void jogar_contra_computador() {
    int jogadas = 0;
    char jogador = 'X';
    inicializar_matriz();
    start_time = time(NULL);

    while (jogadas < 9 && !partidaTerminada) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            int linha = (mouseY - (screenHeight / 2 - cellSize * 1.5)) / cellSize;
            int coluna = (mouseX - (screenWidth / 2 - cellSize * 1.5)) / cellSize;

            if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && mtz[linha][coluna] == ' ') {
                mtz[linha][coluna] = jogador;
                jogadas++;

                int resultado = verificar_vencedor(jogador);
                if (resultado > 0) {
                    pontuacaoJogadorX += (resultado == 1) ? 5 : 10;
                    partidaTerminada = true;
                }

                if (!partidaTerminada && jogadas < 9) {
                    jogada_computador();
                    jogadas++;

                    resultado = verificar_vencedor('O');
                    if (resultado > 0) {
                        pontuacaoJogadorO += (resultado == 1) ? 5 : 10;
                        partidaTerminada = true;
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        matriz();

        for (int i = 0; i < 4; i++) {
            DrawLine((screenWidth / 2 - cellSize * 1.5) + i * cellSize, screenHeight / 2 - cellSize * 1.5, 
                     (screenWidth / 2 - cellSize * 1.5) + i * cellSize, screenHeight / 2 + cellSize * 1.5, BLACK);
            DrawLine(screenWidth / 2 - cellSize * 1.5, (screenHeight / 2 - cellSize * 1.5) + i * cellSize, 
                     screenWidth / 2 + cellSize * 1.5, (screenHeight / 2 - cellSize * 1.5) + i * cellSize, BLACK);
        }

        DrawText(TextFormat("Tempo de jogo: %.2f segundos", difftime(time(NULL), start_time)), 10, 10, 20, BLACK);
        EndDrawing();
    }

    if (partidaTerminada) {
        if (pontuacaoJogadorX > pontuacaoJogadorO) {
            exibir_mensagem_vencedor(TextFormat("%s venceu!", nomeJogadorX));
        } else {
            exibir_mensagem_vencedor(TextFormat("%s venceu!", nomeJogadorO));
        }
    } else {
        exibir_mensagem_vencedor("Empate!");
    }
}

void pedir_nomes(int modo) {
    if (modo == GAME) {
        // Pedir nome do jogador X
        DrawText("Nome do Jogador X:", screenWidth / 2 - 100, screenHeight / 2 - 20, 20, BLACK);
        DrawText(nomeJogadorX, screenWidth / 2 - MeasureText(nomeJogadorX, 20) / 2, screenHeight / 2 + 20, 20, BLACK);
        
        if (IsKeyPressed(KEY_ENTER)) {
            // Esperar entrada do jogador X
            nomeJogadorO[0] = '\0'; // Limpa o nome do jogador O
            return;
        }
    } else if (modo == GAME_PC) {
        // Pedir nome do jogador X
        DrawText("Nome do Jogador X:", screenWidth / 2 - 100, screenHeight / 2 - 20, 20, BLACK);
        DrawText(nomeJogadorX, screenWidth / 2 - MeasureText(nomeJogadorX, 20) / 2, screenHeight / 2 + 20, 20, BLACK);
        
        if (IsKeyPressed(KEY_ENTER)) {
            return;
        }
    }
}

int main() {
    InitWindow(screenWidth, screenHeight, "Jogo da Velha com Raylib");

    GameScreen currentScreen = MENU;

    while (!WindowShouldClose()) {
        if (currentScreen == MENU) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("Jogo da Velha", screenWidth / 2 - MeasureText("Jogo da Velha", 40) / 2, screenHeight / 2 - 50, 40, BLACK);
            DrawText("1. Começar Jogo", screenWidth / 2 - MeasureText("1. Começar Jogo", 20) / 2, screenHeight / 2 + 20, 20, BLACK);
            DrawText("2. Jogar contra o Computador", screenWidth / 2 - MeasureText("2. Jogar contra o Computador", 20) / 2, screenHeight / 2 + 50, 20, BLACK);
            DrawText("3. Sair", screenWidth / 2 - MeasureText("3. Sair", 20) / 2, screenHeight / 2 + 80, 20, BLACK);
            DrawText("Luiz Fernando, Joshuan Estevão, Gabriel Chagas", screenWidth / 2 - MeasureText("Luiz Fernando, Joshuan Estevão, Gabriel Chagas", 20) / 2, screenHeight - 50, 20, BLACK);

            if (IsKeyPressed(KEY_ONE)) {
                pedir_nomes(GAME);
                currentScreen = GAME;
            } else if (IsKeyPressed(KEY_TWO)) {
                pedir_nomes(GAME_PC);
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
