#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void espacar() {
    for (int i = 0; i < 4; i++) {
        putchar('\t');
    }
}

void matriz() {
		int i;
	for (i = 0; i < 3; i++) {
		putchar('\t');
		printf("  |		|");
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
		printf("   X");
		matriz();
	}
}

int main(){

setlocale(LC_ALL, "Portuguese");

int matriz[1][1][1] , jogador1 , jogador2;
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
