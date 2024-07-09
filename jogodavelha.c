#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

char mtz[3][3]; // Matriz do jogo da velha

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
    printf("Bem vindo ao Jogo da Velha !\n\n");
    espacar();
    printf("  Selecionar modo de jogo:\n\n\n\n");
    espacar();
    printf("1 - Multijogador\n\n");
    espacar();
    printf("2 - Jogar contra o computador\n\n");
    espacar();
    printf("3 - Ver Créditos\n\n");
    espacar();
    scanf(" %c", &op); // Corrigido para " %c" para ignorar espaços em branco
    
    switch (op) {
        case '1':
            system("cls");
            multijogador();
            break;
        case '2':
            system("cls");
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
