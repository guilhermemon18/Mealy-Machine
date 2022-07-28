// implemente um simulador de Maquina de Mealy.

//1º passo ler o arquivo contendo as especificaçoes da maquina(entrada)
//2º executar a maquina(execução)
//3º apresentar os resultados na tela(saída)

#include <stdio.h>//includes
#include <string.h>
#include <locale.h>
#include "Funcoes.h"


int main()//funçao principal main
{
	setlocale(LC_ALL, "portuguese");
	MaquinaDeMealy Maquina; //declara-se uma maquina 
	char str[30];//declara uma string para armazenar a palavra

	// a maquina precisa começar zerada em transiçoes, e  os estados zerados na condiçao  se sao ou nao iniciais ou finais.
	zeramaquina(&Maquina);//incia a maquina com as condiçoes para operar,para ler o arquivo.

	LerArquivo("especificacoes.txt",&Maquina);//funçao para leitura do arquivo de especificacoes
	
	printf("Digite uma palavra, digite \"fim\" para terminar\n");//pede para digitar as palavras que vao ser transformadas pela maquina
	gets(str);// le a palavra e armazena na string str

	while (strcmp(str, "fim"))//enquanto a palavra for diferente de fim processará as transformaçoes
	{
		
		Maquina.condicaodapalavra = 1;//atribui a palavra pra começar como sendo valída
		Maquina.palavra_saida[0] = '\0';//palavra de saida começa vazia para ser concatenada conforme for sendo feita
		Executar(str,&Maquina);//executa a maquina de Mealy na palavra
		printf("Digite uma palavra, digite \"fim\" para terminar\n");//pede para digitar outra palavra que será testada na máquina de Mealy
		gets(str);// le a palavra e armazena na string str
	}
	system("pause");
	return 0;//indica que n houve problemas e retona zero para main
}