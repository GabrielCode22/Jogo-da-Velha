#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void matriz() {
		int i;
	for (i = 0; i < 10; i++) {
		putchar('\t');
		printf("  |		|");
		printf("\n");
	}
}

void multijogador(){
	matriz();
}

int main(){

setlocale(LC_ALL, "Portuguese");

int matriz[1][1] , jogador1 , jogador2;
char op;

putchar('\t'); putchar('\t'); putchar('\t'); putchar('\t');
printf("Bem vindo ao Jogo da Velha !\n\n");
putchar('\t'); putchar('\t'); putchar('\t'); putchar('\t');
printf("  Selecionar modo de jogo:\n\n\n\n");
putchar('\t'); putchar('\t'); putchar('\t'); putchar('\t');
printf("1 - Multijogador\n\n");
putchar('\t'); putchar('\t'); putchar('\t'); putchar('\t');
printf("2 - Jogar contra o computador\n\n");
putchar('\t'); putchar('\t'); putchar('\t'); putchar('\t');
printf("3 - Ver Créditos\n\n");
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
	printf(" Luiz Fernando\n Joshuan Estevão \n Gabriel Chagas");
	break;

default:
	printf("A");
}


return 0;
}
