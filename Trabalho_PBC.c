/* Nomes dos integrantes do grupo: Mateus Souza Coelho e Piettro Augusto Pereira Benincá.*/

#include"biblioteca.h"
void jogo1(int numjogadores);
void jogo2(int numjogadores);

int main()
{
	int escolha=0,numjogadores;
	srand(time(NULL));	
		
		printf("Sejam bem vindos a casa de recreacao Sem Censura!!!\n\n\n");
		printf("Por favor digite o numero de jogadores que irao participar do jogo,"); 
		printf(" no maximo 10 jogadores:\n");
		
		do//protege variavel
		{
			scanf("%i",&numjogadores);
			
				if(numjogadores<1 || numjogadores>10)
				{
					printf("Sao permitidos, no maximo 10 jogadores, digite novamente.\n");
				}
		
		}while( numjogadores<1 || numjogadores>10 );
		
		printf("\n");	
		
		printf("Agora, digite o numero 1 ou 2 para selecionar o jogo desejado,\n");
		printf("ao digitar 1, voce seleciona o jogo dos 30 aleatorios,\n");
		printf("ao digitar 2, voce seleciona o bingo de cartela unica.\n");
	
		do//protege variavel
		{
			printf("\nEscolha seu jogo:\n");
			scanf("%i",&escolha);
				
				if(escolha!=1 && escolha!=2)
				{
					printf("Por favor, digite apenas o numero 1 ou o numero 2.\n");
				}
		
		}while( escolha!=1 && escolha!=2 );
		
		printf("\n");			
		switch(escolha)
		{
			case 1:system("cls||clear");	
				printf("Voce selecionou o jogo 1!\n\n");
					jogo1(numjogadores);
					break;
			
			case 2:system("cls||clear");
				printf("Voce selecionou o jogo 2!\n\n");		
					jogo2(numjogadores);
					break;
		}
	

return(0);
}
//-------------------------------------------------------------------------------------
void jogo1(int numjogadores)
{
	FILE *resultado;
	resultado=fopen("jogo1.txt","w");
	int c,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,premio=0,maior_soma=0,num_somas_iguais=1,vencedor1,vencedor2,
		desvios_iguais=0,premio_dividido,vencedores_empate_soma[10],perdedores_empate_desvio[10];//continucao da declaracao ''int''
	float menor_desvio=999999.0;	
	
	c=numjogadores;//fizemos essa troca para tornar os contadores mais coesos entre si 
	//c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11 sao os contadores das repeticoes
	
		typedef struct{
				
					int aposta,numgerados[30];
					float desvio,media,soma;
		
				}tpvalores;
				typedef struct{
			
					char nome[60];
					tpvalores valores;
		
				}tpjogador;
			tpjogador jogador[c];	


		fprintf(resultado,"Relatorio final do jogo1:\n\n\n");
		for(c1=0; c1<c; c1++)//este "for" serve para adiquirir as informacoes do usuario
		{
			printf("Bem vindo, voce sera o jogador %i\n",c1+1);
			printf("Digite seu nome:\n");
			getchar();
			scanf("%[^\n]s",jogador[c1].nome);
			fprintf(resultado,"Jogador %i\n",c1+1);//colocamos c1+1 para a nomeacao dos jogadores comecar a partir de 1 
			fprintf(resultado,"Nome: %s \n",jogador[c1].nome);
		
			printf("Digite o numero de doces que voce deseja apostar:\n");
			
			do{	// protecao de variavel
			scanf("%i",&jogador[c1].valores.aposta);	
				if( jogador[c1].valores.aposta<5 || jogador[c1].valores.aposta>20 )
				{
					printf("O numero de doces deve estar entre 5 e 20.\n");	
				}
			}while( jogador[c1].valores.aposta<5 || jogador[c1].valores.aposta>20 );
				
			fprintf(resultado,"Valor apostado:%i\n",jogador[c1].valores.aposta);
			
			fprintf(resultado,"Seus numeros que foram gerados:\n");
			
            gera(jogador[c1].valores.numgerados,1,1000);//gera os numeros aleatorios			
            for(c2=0; c2<30; c2++)//este "for" serve para imprimir os numeros sorteados de cada jogador
			{				
				fprintf(resultado,"%i ",jogador[c1].valores.numgerados[c2]);
			}
			
			fprintf(resultado,"\n");
			
			jogador[c1].valores.soma=calcula(jogador[c1].valores.numgerados, 30);
			
			jogador[c1].valores.media=jogador[c1].valores.soma/30;
			fprintf(resultado,"Sua soma total: %.0f\n",jogador[c1].valores.soma);
			
			
			jogador[c1].valores.desvio=desvio( jogador[c1].valores.numgerados, 30, jogador[c1].valores.media);	
			fprintf(resultado,"Seu desvio padrao:%f\n",jogador[c1].valores.desvio);
			
			premio+=jogador[c1].valores.aposta;
			
			printf("________________________________________________\n");
			fprintf(resultado,"________________________________________________\n");
		c2=0;//inicializacao
		}
		
		for(c3=0; c3<c; c3++)//este "for" serve para verificar a maior soma
		{
			if(jogador[c3].valores.soma>maior_soma)
			{
				maior_soma=jogador[c3].valores.soma;
				vencedor1=c3;//vencedor1 serve para acusar a posicao do vencedor
				c4=vencedor1+1;//como a condicao do "if" e dada por "maior que" sabemos que caso haja algum jogador empatado, este com certeza estara apos o primeiro jogador com a maior soma
			}
		}

		while(c4<c)//este "while" serve para verificar se uma a maior soma gerada aparece mais de uma vez para diferente jogadores
		{
			if(maior_soma==jogador[c4].valores.soma)
			{
				num_somas_iguais++;
			}
        c4++;		
        }
		
		if(num_somas_iguais==1)//caso haja apenas um vencedor
		{
			fprintf(resultado,"-----------------------------------------------------------\n");
			fprintf(resultado,"Parabens %s",jogador[vencedor1].nome); 
			fprintf(resultado,", ou jogador %i, voce foi o vencedor!!!!\n",vencedor1+1); 
			fprintf(resultado,"Seu premio foi de:%i doces!!!\n",premio);
			fprintf(resultado,"-----------------------------------------------------------\n");
		}
		else//desempate
		{
			
			c5=vencedor1;
			while(c5<c)//este "while" serve para verificar quais dos jogadores empatados possui menor desvio
			{
					if(jogador[c5].valores.desvio<menor_desvio && jogador[c5].valores.soma==jogador[vencedor1].valores.soma)
					{
						menor_desvio=jogador[c5].valores.desvio;
						vencedor2=c5;//vencedor2 serve para acusar a posicao do vencedor
					}
            c5++;			
            }
			c6=vencedor2;//c6 pega a posicao do vencedor da segunda condicao do jogo	
			
			while(c6<c)//este "while" serve para verificar se uma o menor desvio gerado aparece mais de uma vez para diferente jogadores(empatados pela maior soma)
			{
				if(menor_desvio==jogador[c6].valores.desvio)
				{
					desvios_iguais++;
				}
					
					if(desvios_iguais>0)
					{
						vencedores_empate_soma[c7]=c6;	
					}
					
					
			
			c6++;c7++;									
			}
			while(c8<c)//este "while" serve para alocar os jogadores que perderam na condicao de desempate em um vetor
			{
				if(jogador[c8].valores.desvio>menor_desvio && jogador[c8].valores.soma==maior_soma)
				{
					perdedores_empate_desvio[c9]=c8;
				c9++;
				}
			
			c8++;
			}
			
			if(desvios_iguais==1)//caso haja apenas um vencedor na condicao de empate
			{
				fprintf(resultado,"Houve um empate no jogo,\n");
				fprintf(resultado,"utilzando o quesito de desempate, %s ou, jogador %i, foi o vencedor!!!!\n",jogador[vencedor2].nome,vencedor2+1);
				fprintf(resultado,"Com o menor desvio padrao %f, seu premio foi de:%i doces!!!\n",jogador[vencedor2].valores.desvio,premio);		
				fprintf(resultado,"\nEm relacao a soma dos numeros gerados, os jogadores que perderam no quesito de desempate e seus respectivos desvios foram:\n");
				while(c10<num_somas_iguais-1)//este "while" serve para imprimir o nome dos perdedores na condicao de empate
				{
					fprintf(resultado,"%s, desvio:%f\n",jogador[perdedores_empate_desvio[c10]].nome, jogador[perdedores_empate_desvio[c10]].valores.desvio);	
				c10++;
				}
				
			}
			else
			{
				premio_dividido = premio/desvios_iguais;//divide o premio entre os vencedores
					
					fprintf(resultado,"Como houveram empates nos menores desvios,\n");
					fprintf(resultado,"O premio sera divido entre os %i vencedores e cada um recebera:%i doces\n",desvios_iguais,premio_dividido);
					fprintf(resultado,"\nOs vencedores foram os jogadores:\n");
						for(c11=0; c11<desvios_iguais; c11++)//este "for" serve para imprimir o nome dos vencedores caso haja empate em todas as condicoes
						{
							fprintf(resultado,"%s, ",jogador[vencedores_empate_soma[c11]].nome);
						}
			}
		}
	printf("\nO jogo foi finalizado, por favor verifique os resultados em um documento chamado jogo1 no arquivo do programa.\n");
fclose(resultado);		
}
//-------------------------------------------------------------------------------------
void jogo2(int numjogadores)
{
	FILE *resultado;
	resultado=fopen("jogo2.txt","w");
	int c,c1,c2,c3,c4,c5,c6,c7,c8,c9,cartela[30],num_distintos=0,menor,premio=0,empates=0,vencedor1,jogs_empatados[10],premio_dividido;
	
	//c1,c2,c3,c4,c5,c6,c7,c8,c9 sao os contadores das repeticoes	                                                                                   
	c=numjogadores;//fizemos essa troca para tornar os contadores mais coesos entre si 
	menor=100000;
		
	fprintf(resultado,"Relatorio final do jogo2:\n\n\n");	
		typedef struct{
				
					int aposta,num_necessarios;
				
		
				}tpvalores;
				typedef struct{
			
					char nome[60];
					tpvalores valores;
		
				}tpjogador;
			tpjogador jogador[c];
			
		for(c1=0; c1<c; c1++)//este "for" serve para adiquirir as informacoes do usuario
		{
			printf("Bem vindo, voce sera o jogador %i\n",c1+1);
			printf("Digite seu nome:\n");
			getchar();
			scanf("%[^\n]s",jogador[c1].nome);
			fprintf(resultado,"Jogador %i\n",c1+1);
			fprintf(resultado,"Nome: %s \n",jogador[c1].nome);		
			
			printf("Digite o numero de doces que voce deseja apostar:\n");
			
			do{//protege variavel	
			scanf("%i",&jogador[c1].valores.aposta);
				if( jogador[c1].valores.aposta<5 || jogador[c1].valores.aposta>20 )
				{
					printf("O numero de doces deve estar entre 5 e 20.\n");
				}
			}while( jogador[c1].valores.aposta<5 || jogador[c1].valores.aposta>20 );
		
			fprintf(resultado,"Valor apostado:%i\n",jogador[c1].valores.aposta);
			
			premio+=jogador[c1].valores.aposta;
			
			fprintf(resultado,"____________________________________________________________\n");
		}
		
		fprintf(resultado,"A cartela gerada:\n");
		gera_zera(cartela,1,1000);//gera e zera a cartela unica do bingo
		for(c2=0; c2<30; c2++)//este "for" serve para imprimir a cartela
		{	
			fprintf(resultado,"%i ",cartela[c2]);
		}
		fprintf(resultado,"\n");
		
		for(c3=0; c3<30; c3++)//este "for" serve para contar os numeros diferentes de zero na cartela
		{
			if(cartela[c3]!=0)
			{
				num_distintos++;//numeros distintos entre si diferentes de zero na cartela
			}
		}
		
		for(c4=0; c4<c; c4++)//este "for" serve para gerar e contar os numeros necessarios de cada jogador para acertas os numeros da cartela
		{
			jogador[c4].valores.num_necessarios=sorteia(cartela,1,1000,num_distintos);				
		}
		
		for(c5=0; c5<c; c5++)//este "for" serve para verificar o jogador com o menor numero de geracoes aleatorias necessarias para os numeros da cartela
		{
			if(jogador[c5].valores.num_necessarios<menor)
			{
				menor=jogador[c5].valores.num_necessarios;
				vencedor1=c5;//acusa a posicao do vencedor
			}		
		}
		
		for(c6=0; c6<c; c6++)//este "for" serve para verificar caso haja empates entre os jogadores
		{
			if(jogador[c6].valores.num_necessarios==menor)
			{
				empates++;
			}
		}
		
		c7=vencedor1;/*como a condicao do "if" que verifica a menor quantidade de aleatior necessarios e dada por "menor que" sabemos que caso haja algum jogador empatado, 
	este com certeza estara apos o primeiro jogador com o menor numero de geracoes aleatorioas*/
		
		c8=0;
		while(c7<c)//este "while" serve para armazenar a posicao dos jogadores empatados
		{
			if(jogador[c7].valores.num_necessarios==menor)
			{
				jogs_empatados[c8]=c7;
			c8++;
			}
		
		c7++;
		}
	
		if(empates==1)//verifica caso haja apenas um vencedor
		{
			fprintf(resultado,"-----------------------------------------------------------\n");
			fprintf(resultado,"Parabens %s",jogador[vencedor1].nome); 
			fprintf(resultado,", ou jogador %i, voce foi o vencedor!!!!\n",vencedor1+1); 
			fprintf(resultado,"Com a menor quantidade de numeros gerados:%i,\n",jogador[vencedor1].valores.num_necessarios);
			fprintf(resultado,"Seu premio foi de:%i doces!!!\n",premio);
			fprintf(resultado,"-----------------------------------------------------------\n");	
			
		}
		else//caso haja empate
		{
			premio_dividido = premio/empates;//divide o premio entre os vencedores
			
			fprintf(resultado,"-----------------------------------------------------------\n");
			fprintf(resultado,"Como houveram empates na quantidade de numeros necessarios,\n");
			fprintf(resultado,"O premio sera divido entre os %i vencedores e cada um recebera:%i doces\n",empates,premio_dividido);
			fprintf(resultado,"Os vencedores e seus respectivos numeros necessarios foram:\n");
			for(c9=0; c9<empates; c9++)//este "for" serve para imprimir o nome dos jogadores empatados
			{
				fprintf(resultado,"%s, numeros necessarios:%i\n",jogador[jogs_empatados[c9]].nome,jogador[jogs_empatados[c9]].valores.num_necessarios);
			}
			fprintf(resultado,"-----------------------------------------------------------\n");
		}	
		
	printf("\nO jogo foi finalizado, por favor verifique os resultados em um documento chamado jogo2 no arquivo do programa.\n");
fclose(resultado);				
}
