#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.000001

double** criaMatriz ( int l, int c );
void lerMatriz ( double** m, int l, int c );
void exibeMatriz ( double** m, int l, int c );
int substituicaoRetroativa ( double** m, int n, double x[] );
void Gauss ( double** m, int n );

int main()
{
	
	int i, n, tipo;
	double **m, *x;
	
	printf ( "Quantidade de variaveis: " );
	scanf ( "%d", &n );
	
	m = criaMatriz ( n , n + 1 );
	x = malloc ( sizeof ( double ) * n );
	
	if ( m == NULL || x == NULL )	// Faltou memoria, meno
	{
		printf ( "Deu Pau!\n Falta de Memoria\n" );
		return 1;
	}
	
	lerMatriz ( m , n , n + 1 );

	printf ( "\tMatriz Quadrada:\n" );
	exibeMatriz ( m , n , n + 1 );

	Gauss ( m , n );

	printf ( "\tMatriz Triangular Superior:\n" );
	exibeMatriz ( m , n , n + 1 );

	tipo = substituicaoRetroativa ( m , n , x );
	
	if ( tipo == 2 )
	{
		printf ( "\tSistema Linear Incompativel. \n" );
	}
	else
	{
		printf ( "\tSistema Linear %sdeterminado. \n\n", tipo ? "in" : "" );
		for ( i = 0; i < n ; i++ )
		{
			printf( "\tx[%d] = %10.3lf\n", i + 1 , x [ i ] );
		}
	}
	
	return 0;

}	// Fim da main

double** criaMatriz ( int l, int c )
{
	
/* 	
	Se houver memoria disponivel, cria uma matriz de double
	com l linha e c colunas e devolve um ponteiro para a matriz;
	Caso contrario, devolve um ponteiro nulo.
*/

	int i, j;
	double** m;
	
	m = malloc ( sizeof ( double *) * l );
	
	if ( m == NULL )		// Falta de memoria.
	{
		return NULL;
	}
		
	for ( i = 0 ; i < l ; i++ )
	{
		
		m [ i ] = malloc ( sizeof ( double ) * c );
		
		if ( m [ i ] == NULL )		// Falta de memoria.
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
	
	printf ( "\n" );

}	// Fim lerMatriz.

void exibeMatriz ( double** m, int l, int c )
{
	
	/*
		Exibe o conteudo de m, uma matriz de double,
		com l linha e c colunas alocada dinamicamente.
	*/
	
	int i, j;

	printf ( "\n" );

	for ( i = 0 ; i < l ; i++ )
	{
		for ( j = 0 ; j < c ; j++ )
		{
			printf ( "%10.3lf ", m [ i ][ j ] );
		}
		
		printf ( "\n" );
		
	}

	printf ( "\n" );
	
}	// Fim exibeMatriz

int substituicaoRetroativa ( double** m, int n, double x[] )
{
	
	/*
		Recebe m, a matriz aumentada de um Sistema Linear Triangular Superior
		com n variaveis; 
		Se o Sistema Linear for determinado, coloca em x a solucao
		do SL e devolve 0;
		Se o Sistema Linear for indeterminado, coloca em x uma solucao
		do SL e devolve 1;
		Se o Sistema Linear for imcompativel, devolve 2.
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
			if ( fabs ( m [ i ] [ n ] - soma ) < EPSILON )		// x[i] eh variavel livre.
			{
				x [ i ] = 0;
				tipo = 1;
			}
			else return 2;		// Sistema Linear Incompativel
		}
		else x [ i ] = ( m [ i ][ n ] - soma ) / m [ i ][ i ];
		
	}

	return tipo;

}	// Fim substituicaoRetroativa 

void Gauss ( double** m, int n )
{

	/*
		Recebe m, a matriz aumentada de um Sistema Linear
		com n variaveis e n equacoes, e transforma m na matriz
		aumentada de um Sistema Linear Triagular Superior equivalente.
	*/

	int i, j, k;
	double multiplicador;
	double* auxiliar;

	for ( i = 0 ; i < n - 1 ; i++ )
	{
		if ( m [ i ] [ i ] == 0 )	// Pivo nulo
		{
			j = i + 1;
			while ( j < n && m [ j ] [ i ] == 0 )
			{
				j++;
			}
			if ( j < n )	// Troca das linhas i e j
			{
				printf ( "\tGauss: Trocando linhas!\n" );
				auxiliar = m [ i ];
				m [ i ] = m [ j ];
				m [ j ] = auxiliar;
			} 
		}

		if ( m [ i ] [ i ] != 0 )
		{
			for ( j = i + 1 ; j < n ; j++ )
			{
				multiplicador = - m [ j ] [ i ] / m [ i ] [ i ];
				m [ j ] [ i ] = 0;
				for ( k = i + 1 ; k <= n ; k++ )
				{
					m [ j ] [ k ] += multiplicador * m [ i ] [ k ];
				}
			}
		}
	}
}	// Fim Gauss
