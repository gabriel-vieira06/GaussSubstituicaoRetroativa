#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double** criaMatriz ( int l, int c );
void lerMatriz ( double** m, int l, int c );
void exibeMatriz ( double** m, int l, int c );
int substituicaoRetroativa ( double** m, int n, double x[] );

int main()
{
	
	int i, n, tipo;
	double **m, *x;
	
	printf ( "Quantidade de variaveis: " );
	scanf ( "%d", &n );
	
	m = criaMatriz ( n , n + 1 );
	x = malloc ( sizeof ( double ) * n );
	
	if ( m == NULL || x == NULL )	// Faltou memória, menó
	{
		printf ( "Deu Pau!\n Falta de Memoria\n" );
		return 1;
	}
	
	lerMatriz ( m , n , n + 1 );
	exibeMatriz ( m , n , n + 1 );
	tipo = substituicaoRetroativa ( m , n , x );
	
	if ( tipo == 2 )
	{
		printf ( "Sistema Linear Incompativel. \n" );
	}
	else
	{
		printf ( "Sistema Linear %sdeterminado. \n", tipo ? "in" : "" );
		for ( i = 0; i < n ; i++ )
		{
			printf( "x[%d] = %10.3lf\n", i + 1 , x [ i ] );
		}
	}
	
	return 0;

}	// Fim da main

double** criaMatriz ( int l, int c )
{
	
/* 	
	Se houver memória disponível, cria uma matriz de double
	com l linha e c colunas e devolve um ponteiro para a matriz;
	Caso contrário, devolve um ponteiro nulo.
*/

	int i, j;
	double** m;
	
	m = malloc ( sizeof ( double *) * l );
	
	if ( m == NULL )		// Falta de memória.
	{
		return NULL;
	}
		
	for ( i = 0 ; i < l ; i++ )
	{
		
		m [ i ] = malloc ( sizeof ( double ) * c );
		
		if ( m [ i ] == NULL )		// Falta de memória.
		{
		
			for ( j = 0 ; j < i ; j++ )
			{
				free ( m [ j ] );
			}
			
			free ( m );
			return NULL;
		
		}
	}
	
	return m;

}	// Fim criaMatriz.

void lerMatriz ( double** m, int l, int c )
{
	
	/*
		Le valores para m, uma matriz de double com l linhas
		e c colunas alocadas dinamicamente.
	*/
	
	int i, j;
	
	for ( i = 0 ; i < l ; i++)
	{
		for ( j = 0 ; j < c ; j++)
		{
			printf ( "M[%d][%d]: " , i + 1 , j + 1 );
			scanf ( "%lf" , &m [ i ][ j ] );
		}
	}
	
}	// Fim lerMatriz.

void exibeMatriz ( double** m, int l, int c )
{
	
	/*
		Exibe o conteudo de m, uma matriz de double,
		com l linha e c colunas alocada dinamicamente.
	*/
	
	int i, j;
	
	for ( i = 0 ; i < l ; i++ )
	{
		for ( j = 0 ; j < c ; j++ )
		{
			printf ( "%10.3lf ", m [ i ][ j ] );
		}
		
		printf ( "\n" );
		
	}
	
}	// Fim exibeMatriz

int substituicaoRetroativa ( double** m, int n, double x[] )
{
	
	/*
		Recebe m, a matriz aumentada de um Sistema Linear Triangular Superior
		com n variaveis; 
		Se o Sistema Linear for determinado, coloca em x a solução
		do SL e devolve 0;
		Se o Sistema Linear for indeterminado, coloca em x uma solução
		do SL e devolve 1;
		Se o Sistema Linear for imcompativel, devolve 2;
	*/
	
	int i, j, tipo = 0;
	double soma;
	
	for ( i = n - 1 ; i >= 0 ; i-- )
	{
		soma = 0;
		
		for ( j = i + 1 ; j < n ; j++ )
		{
			soma += m [ i ][ j ] * x [ j ];
		}
		
		if ( m [ i ][ i ] == 0 )
		{
			if ( soma == m [ i ][ n ] )		// x[i] é variável livre.
			{
				x [ i ] = 0;
				tipo = 1;
			}
			else return 2;		// Sistema Linear Incompatível
		}
		else x [ i ] = ( m [ i ][ n ] - soma ) / m [ i ][ i ];
		
	}

	return tipo;

}	// Fim substituicaoRetroativa 
