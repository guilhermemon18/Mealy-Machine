// implemente um simulador de Maquina de Mealy.

//1� passo ler o arquivo contendo as especifica�oes da maquina(entrada)
//2� executar a maquina(execu��o)
//3� apresentar os resultados na tela(sa�da)

#include <stdio.h>//includes
#include <string.h>
#include <locale.h>
#include "Funcoes.h"


int main()//fun�ao principal main
{
	setlocale(LC_ALL, "portuguese");
	MaquinaDeMealy Maquina; //declara-se uma maquina 
	char str[30];//declara uma string para armazenar a palavra

	// a maquina precisa come�ar zerada em transi�oes, e  os estados zerados na condi�ao  se sao ou nao iniciais ou finais.
	zeramaquina(&Maquina);//incia a maquina com as condi�oes para operar,para ler o arquivo.

	LerArquivo("especificacoes.txt",&Maquina);//fun�ao para leitura do arquivo de especificacoes
	
	printf("Digite uma palavra, digite \"fim\" para terminar\n");//pede para digitar as palavras que vao ser transformadas pela maquina
	gets(str);// le a palavra e armazena na string str

	while (strcmp(str, "fim"))//enquanto a palavra for diferente de fim processar� as transforma�oes
	{
		
		Maquina.condicaodapalavra = 1;//atribui a palavra pra come�ar como sendo val�da
		Maquina.palavra_saida[0] = '\0';//palavra de saida come�a vazia para ser concatenada conforme for sendo feita
		Executar(str,&Maquina);//executa a maquina de Mealy na palavra
		printf("Digite uma palavra, digite \"fim\" para terminar\n");//pede para digitar outra palavra que ser� testada na m�quina de Mealy
		gets(str);// le a palavra e armazena na string str
	}
	system("pause");
	return 0;//indica que n houve problemas e retona zero para main
}