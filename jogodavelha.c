#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

char mtz[3][3];

void espacar() {
	int i;
    for ( i = 0; i < 4; i++) {
        putchar('\t');
    }
}

void matriz() {
		int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("| %c |", mtz[i][j]);
		}
		printf("\n");
	}
}

void multijogador(){
	matriz();
	int coiso;
	printf("Digite onde quer colocar o coiso:\n1 - 9\n");
	scanf("%d", &coiso);
	
	if (coiso == 1) {
		system("cls");
		mtz[0][3] = 'X';
		matriz();
	}
}

int main(){

setlocale(LC_ALL, "Portuguese");

int jogador1 , jogador2;
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
scanf("%c", &op);

switch(op)
{
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
	printf(" Luiz Fernando | Joshuan Estevão | Gabriel Chagas");
	break;

default:
	printf("A");
}


return 0;
}
