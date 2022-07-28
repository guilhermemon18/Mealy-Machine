#pragma warning(disable : 4996)// coisa do visual studio
#include <stdio.h>
#include  <stdlib.h>
#include <string.h>
#include "Funcoes.h"

//implementação das funções

void zeramaquina(MaquinaDeMealy* Maquina)//recebe a máquina e garante que ela incialize corretamente
{
	int i = 0;
	
	Maquina->quantidadefinais = 0;
	Maquina->palavra_saida[0] = '\0';//palavra de saida começa vazia para poder concatenar conforme é montada
	Maquina->quantidade_de_estados = 0;// começa com 0 estados
	Maquina->condicaodapalavra = 1;// começa como aceita, ela é recusada quando é processada, fora isso inicia dada como aceita

	for (i = 0; i < 20; i++)// os 20 estados começam com condiçao(final ou inicial) zerada e numero de transiçoes vazia
	{
		Maquina->stats[i].ndetrans = 0;
		Maquina->stats[i].final = 0;
		Maquina->stats[i].inicial = 0;
	}
}


	void LerArquivo(char nome_arquivo[],MaquinaDeMealy *Maquina)//função responsável por ler o arquivo com as especificaçoes da maquina
{
	char c = '0';// variável auxiliar char para achar fim do arquivo.
	char quantidadedeestados = 0;//variavel pra auxiliar na contagem de estados;
	FILE* p;//declarando ponteiro de arquivo

	p = fopen(nome_arquivo, "r"); 
	if (p == NULL)
	{
		printf("Erro na abertuda do arquivo.\n");
		exit(1);
	}
	fscanf(p, "%*[^{]");// le ate encontrar um abre chaves
	fscanf(p, "%*c");//descarta o abre chaves

	//lê o alfabeto de entrada
	for (int i = 0; c != '}';)
	{
		c = fgetc(p);
		if (c != ',' && c != '}' && c != ' ')
		{
			Maquina->alfabeto_entrada[i] = c;
			i++;
		}
	}
		fscanf(p, "%*[^{]");// le ate encontrar um abre chaves
		fscanf(p, "%*c");//descarta o abre chaves

		//lê o alfabeto de saida
		for (int i = 0,c = 0; c != '}';)
		{
			c = fgetc(p);
			if (c != ',' && c != '}' && c != ' ')
			{
				Maquina->alfabeto_saida[i] = c;
				i++;
			}
		}
		fscanf(p, "%*[^{]");// le ate encontrar um abre chaves e descarta
		fscanf(p, "%*c");//descarta o abre chaves

		//le os nomes dos estados na ordem
		char str[20];//string auxiliar para ler os estados

	
		for (int i = 0, c = '0'; c != '}'; i++)
		{
			fscanf(p, "%*[^q]");//le ate encontrar um estado começando com q, para evitar ler espaço em branco.
			fscanf(p, "%[^\n ,}]s", str);// vai ler somente os estados, quando encontrar o fecha chaves, ele termina o loop
			fscanf(p, "%c", &c);
			strcpy(Maquina->stats[i].nome,str);
			quantidadedeestados++;
		}
		Maquina->quantidade_de_estados = quantidadedeestados;//atribui a quantidade de estados lidos para a maquina

		fscanf(p, "%*[^=]");// le ate encontrar um sinal de igual
		fscanf(p, "%*c");//descarta o sinal de igual

		fscanf(p, "%*[^q]");//le ate encontrar um estado começando com q, para evitar ler espaço em branco.

		//le o estado inicial;
		fscanf(p, "%s", Maquina->estado_inicial);

		fscanf(p, "%*[^{]");// le ate encontrar um abre chaves 
		fscanf(p, "%*c");//descarta o abre chaves

		//le os estados finais
		for (int i = 0, c = '0'; c != '}'; i++)
		{
			fscanf(p, "%*[^q]");//le ate encontrar um estado começando com q, para evitar ler espaço em branco.
			fscanf(p, "%[^\n ,}]s", str);// vai ler somente os estados_finais, quanddo encontrar o fecha chaves ele termina o loop
			fscanf(p, "%*[ ]");//le  espaço em branco.
			fscanf(p, "%c", &c);
			strcpy(Maquina->estados_finais[i], str);
			Maquina->quantidadefinais++;
		}
		
		//vai ler o nome do estado, achar o estado com esse nome e colocar na transiçao desse estado
		int controle = 0; //variavel pra controlar os estados
		while(c!= EOF)
		{
			fscanf(p, "%*c");//le o parenteses e descarta
			fscanf(p, "%*[(]s");
			fscanf(p, "%*[^q]");//le ate encontrar um estado começando com q, para evitar ler espaço em branco.
			fscanf(p, "%[^,) ]s", str);// le a string com o nome do estado atual da transiçao
			fscanf(p, "%*[ ]");//le  espaço em branco.

			
			for(controle=0;controle<Maquina->quantidade_de_estados;controle++)//acha o estado correspondende ao estado atual da transiçao lida
				if (strcmp(Maquina->stats[controle].nome, str) == 0)
				{
					//vai ler ver se é igual se for colocar na string esatado atual e entao incrmentar o numero de transiçoes depois que colocou
					// e entao sair do for
					strcpy(Maquina->stats[controle].trans[Maquina->stats[controle].ndetrans].estado_atual, str);
					Maquina->stats[controle].ndetrans++;//incrementa para a proxima vez que ler estar com o  indice pronto
					break;
				}
				
			fscanf(p, "%*c");//le a virgula e descarta

			fscanf(p, "%*[ ]");//le os espaços em branco, para evitar ler espaço em branco.

			fscanf(p, "%c", &Maquina->stats[controle].trans[Maquina->stats[controle].ndetrans - 1].caracter_lido);// le o caracter de leitura
			
			
			fscanf(p, "%*[^q]");//le ate encontrar um estado começando com q, para evitar ler espaço em branco.
			
			fscanf(p, "%[^\n ,() =]s", str);// le a string ate encontrar uma virgula ou espaço em branco
			fscanf(p, "%*[ ]");//le  espaço em branco.
			strcpy(Maquina->stats[controle].trans[Maquina->stats[controle].ndetrans - 1].proximo_estado, str);//copia a estring lida para a maquina

			fscanf(p, "%*c");// le e descarta a virgula;
			fscanf(p, "%*[ ]s");//le espaço em braco, para evitar ler espaço em branco.
			fscanf(p, "%[^) ]s", str);// le a string ate encontrar um fecha parentesis ou espaço em branco
			fscanf(p, "%*[ ]");//le  espaço em branco.
			fscanf(p,"%*c");// le o fecha parentesis e descarta

			strcpy(Maquina->stats[controle].trans[Maquina->stats[controle].ndetrans - 1].saida, str);
			c = fgetc(p);// variavel pra controlar o fim de arquivo,quando igual a EOF termina o loop.
		}
	fclose(p);
}


void Executar(char nome_palavra[], MaquinaDeMealy* Maquina)
{
	int i = 0;
	char copia_nome_palavra[20];
	strcpy(copia_nome_palavra, nome_palavra);//agora tem uma copia da string original
	char estadoatual[20];// variavel para armazenar o estado, começa no inicial sempre quando liga a maquina e processa.
	char proximasaida[20];
	strcpy(estadoatual, Maquina->estado_inicial);//copiou o estado inicial para a variavel auxiliar.
	//while (nome_palavra[i] != '\0')
	int j = 0;

	printf("[%s] %s\n", estadoatual, copia_nome_palavra);//imprime o estado inicial e a palavra inteira

	while(j<strlen(nome_palavra))// precisa processar a quantidade de caracterres da palavra ou menos vezes(break) pra terminar a exucução
	{
		processaestado(estadoatual, Maquina,nome_palavra,copia_nome_palavra,nome_palavra[i],proximasaida);
		if (Maquina->condicaodapalavra == 0 )// n imprime nada se processar o estado e for rejeitado
			break;//dá break e sai do while
		printf("[%s] %-*s      saida: %s\n", estadoatual, strlen(nome_palavra),copia_nome_palavra, proximasaida);//imprime o estado e a saida 
		i++;
		j++;
	}

	if (isfinal(estadoatual,Maquina) == 0)//se nao chegou no estado final a palavra é rejeita.
		Maquina->condicaodapalavra = 0;

	if (Maquina->condicaodapalavra == 1 )
		printf("ACEITA\n");
	else
		printf("REJEITA\n");
	printf("palavra de saida: %s\n", Maquina->palavra_saida);
	printf("\n");//espaço entre os processamentos de palavras
}



void processaestado(char estadoatual[], MaquinaDeMealy* Maquina, char nome_palavra[], char copia_nome_palavra[], char caracterlido, char proximasaida[])
{
	if (Maquina->condicaodapalavra == 0)// obs: so pra poupar processamento a palavra que tá na condiçao falsa nao vai arrumar nada nos for.
		return;
	Maquina->condicaodapalavra = 0;//atribui zero pq ja testou, entao zera e se ela passsar no processo volta a ser 1.
	
	
		for (int i = 0; i < Maquina->quantidade_de_estados; i++)//acha o estado correspondente ao estado atual
			if (strcmp(Maquina->stats[i].nome, estadoatual) == 0)
			{
				for (int j = 0; j < Maquina->stats[i].ndetrans; j++)//acha a transiçao com o caracter correspondente ao lido
					if (Maquina->stats[i].trans[j].caracter_lido == caracterlido)//caracter lido dever ser igual ao da transição
					{
						strcpy(estadoatual, Maquina->stats[i].trans[j].proximo_estado);//copia o proximo estado para estadoretorno
						strcpy(proximasaida, Maquina->stats[i].trans[j].saida);//copia a proxima saida 
						if (strcmp(proximasaida, "@") != 0)
							strcat(Maquina->palavra_saida, proximasaida);//apenas caracteres diferentes de @ concatenarao na palavra
						remove1caracter(copia_nome_palavra);// remove um carctere da palavra original armazenada em copia_nome_palavra
						Maquina->condicaodapalavra = 1;//atribui 1 pois a palavra foi aceita
					}

				break;//depois que achou o estado no primeiro for pode acabar o loop;

			}

}


void remove1caracter(char str[])//recebe uma sstring e remove o primeiro caractere de uma string
{
	int i = 0;
	char aux[20] ;
	for (i = 1; str[i] != '\0';i++)
	{
		aux[i - 1] = str[i];
	}
	aux[i - 1] = '\0';
	for (i = 0; aux[i] != '\0'; i++)
		str[i] = aux[i];
	str[i] = '\0';
}

int isfinal(char estadoatual[], MaquinaDeMealy* Maquina)//verifica o estado na maquina se é final
{
	for (int i = 0; i < Maquina->quantidadefinais; i++)
		if (strcmp(estadoatual, Maquina->estados_finais[i]) == 0)
			return 1;// se corresponder é final

	return 0;//varreu e n achou retorna zero
}

