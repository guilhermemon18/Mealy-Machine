#pragma once // coisa do visual studio

//** Inicialmente � criado uma estrutura para a  Maquina de Mealy, que ira compor todas as etapas desde o inicio, a entrada de dados,
//a leitura, a verifica��o de estados, combina��o e verifica��o de estados.
//criando uma estrutura para maquina de mealy
typedef struct transicao//primeiro uma estrutura para guardar as transi�oes da maquina de mealy
{
	char caracter_lido;//caracter lido da palavra
	char estado_atual[20];// o proprio estado que a transi�ao pertence apenas para legibilidade
	char proximo_estado[20];// o estado que ir� depois que ler o caracter lido
	char saida[20];// os caracteres de saida dessa transi�ao
}transicao;

// ** A estrutura denominada estados, ter� um nome para cada estado identificado como q0,q1,q2 podendo ser 0 ou 1 onde sera verificado se
//� verdadeiro ou falso, tendo como limite de transi��es de estados 5.***
typedef struct estados// cada estado possui um nome(q0,q1,q2,ABOBRINHA,etc..), ele pode ser inicial(1 ou 0) pode ser final(1 ou 0) e
//possui transi�oes
{
	int ndetrans;//quantidade de transi��es do estado
	char nome[20];//seu nome
	int inicial;// zero para falso e 1 para verdadeiro
	int final;//zero para falso e 1 para verdadeiro
	transicao trans[20];// transi�oes do estado,limite dado como 20.
}estados;

typedef struct MaquinaDeMealy//e finalmente a estrutura para a maquina de mealy, que possui alfabeto de entrada,alfabeto de sa�da,estados,
//um estado inicial e um ou mais estados finais
{//*** A estrutura de maquina de mealy, sera controlada por vetores de estados, o alfabeto dara entrada, podendo ser aceito ou n�o, 
	//a string sera verificada tendo o limite de verificacao de estados em 20, e apos sera feita a saida de dados.**
	char palavra_saida[30];
	int condicaodapalavra;//aceita ou nao
	int quantidade_de_estados;// a quantidade de estados da maquina,(controle do vetor de estados)
	char alfabeto_entrada[20];// string contendo os caracteres do alfabeto de entrada
	char alfabeto_saida[20];// string contendo os caracteres do alfabeto de saida
	estados stats[20];// os estados da maquina (20 como combinado com o professor)
	char estado_inicial[20];// o nome do estado inicial
	char estados_finais[20][20];// os nomes dos estados finais
	int quantidadefinais;
}MaquinaDeMealy;

//fun�oes usadas 
//** As fun��es serviram para que o todo o processo corra de forma correta, garantindo que a maquina comece zerada sem lixo de memoria e 
//fa�a a leitura correta de caracteres/alfabeto, configurando a maquina e lendo o que e inicial e final,assim armazenando no arquivo e removendo
//o caracter ao final para uma nova leitura.**
void zeramaquina(MaquinaDeMealy* Maquina);//fun�ao que vai garantir que tudo come�e sem lixo na memoria
void LerArquivo(char nome_arquivo[],MaquinaDeMealy *Maquina);// fun�ao que vai ler o arquivo  e armazenar as informa�oes na maquina(struct).recebe
//string(nome do arquivo) e uma maquina para ler.
void Executar(char nome_palavra[],MaquinaDeMealy *Maquina);//executa a m�quina
void processaestado(char estado[], MaquinaDeMealy* Maquina, char nome_palavra[], char copia_nome_palavra[], char caracter_lido, char proximasaida[]);
// executa as configura�oes quando a maquina salta para um estado, � usada dentro de Executar
void remove1caracter(char str[]);//remove o primeiro caractere de uma string, usada na executar tambem, na processaestado.
int isfinal(char estadoatual[], MaquinaDeMealy* Maquina);
