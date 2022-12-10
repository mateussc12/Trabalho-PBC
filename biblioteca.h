/* Nomes dos integrantes do grupo: Mateus Souza Coelho e Piettro Augusto Pereira Benincá.*/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

void gera(int *vet, int inicio, int fim)//esta funcao serve para gerar os valores aleatorios no jogo 1
{
	int c;
		
		for(c=0; c<30; c++)
		{
			vet[c] = inicio + rand()%fim;
		}		
}
//_______________________________________________________________________________________________
float calcula(int *vet, float fim)//esta funcao serve para calcular a soma dos numeros gerados dos jogadores no jogo 1
{
	int c;
	float soma=0;
	
		for(c=0; c<30; c++)
		{
			soma+=vet[c];	
		}	

return(soma);		
}
//_______________________________________________________________________________________________
float desvio(int *vet, float fim, float media)//esta funcao serve para calcular o desvio padrao dos jogadores no jogo 1
{
	float desvio,soma=0;
	int c;	
	
		for(c=0; c<30; c++)
		{
			soma+=pow((vet[c]-media),2); 
		}
		
		desvio=sqrt(soma/(29.0));// 29=n-1 da formula do desvio padrao e o "." para tornar o 29 como "float"
				
return(desvio);
}
//______________________________________________________________________________________________
void gera_zera(int *vet, int inicio, int fim)//esta funcao serve para gerar e zerar os numeros repetidos da cartela no jogo 2
{
	int c=0,c1=0,c2=0,valor_repetido;	
		
		for(c=0; c<30; c++)
		{
			vet[c] = inicio + rand()%fim;
		}				
		
			for(c1=0; c1<30; c1++)
			{	
				valor_repetido=vet[c1];
					
					for(c2=0; c2<30; c2++)
					{
						if(c2!=c1 && vet[c2]==valor_repetido)
						{	
							vet[c2]=0;		
						}	
					}
					c2=0;
			}
			
}
//______________________________________________________________________________________________
int sorteia(int *vet, int inicio, int fim, int num_distintos)//esta funcao serve fornece os numeros aleatorios necessarios para que cada jogador do jogo 2 acerte os valores da cartela unica
{
	int c=0,num_certos=0,num_errados=0,num_gerados,num_aleatorio;
		
		while(num_certos!=num_distintos)
		{
			num_aleatorio=inicio + rand()%fim;	
			
				while(c<30)
				{
					if(num_aleatorio==vet[c])
					{
						num_certos++;	
					}
					else if(num_aleatorio!=vet[c] && vet[c]!=0)
					{
						num_errados++;
					}
					
				c++;	
				}
				c=0;	
		}
		
		num_gerados=num_certos+num_errados;
				
return(num_gerados);
}


















