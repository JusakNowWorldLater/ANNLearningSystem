#include <iostream>
#include <cstdlib>
#include "perceptron.h"
#include "layer.h"
#include "node.h"

int main()
{
	std::vector<int> config;
	int layersNumber ;

	std::cout << "Enter num of layers" << std::endl ; 

	std::cin >> layersNumber ;
	
	config.resize( layersNumber ) ;

	for( int i = 0 ; i < config.size() ; i++ )
	{
		int tmp ;
		std::cout << "Enter num of nodes in " << i << " layer" << std::endl ;
		std::cin >> tmp ;
		config[ i ] = tmp ;
	}

	Perceptron perceptron( config ) ;

	std::vector<double> input ;
	input.resize( perceptron.getLayer( 0 ).getSize() ) ;
	std::vector<double> out ;
	out.push_back( 0 ) ;



	for( int i = 0 ; i < 100000 ; i++ )
	{
		input[0] = -50 + rand()%100 ;
		input[1] = -50 + rand()%100 ;
		if( input[0] + input[1] < 0 )
			out[0] = 0 ;
		else
			out[0] = 1 ;

		perceptron.study( input , out ) ;
		std::cout << perceptron.calculate( input )[0] << std::endl ;
	}

	int trueAnswers = 0 ;

	for( int i = 0 ; i < 10000 ; i++ )
	{
		input[0] = -50 + rand()%100 ;
		input[1] = -50 + rand()%100 ;
		if( input[0] + input[1] < 0 )
			if( perceptron.calculate( input )[0] < 0.5f )
				trueAnswers++ ;

		if( perceptron.calculate( input )[0] >= 0.5f && input[0] + input[1] >= 0 )
			trueAnswers++ ; 
			
	}

	std::cout << trueAnswers << std::endl ;

	perceptron.save( "Perceptrons/PoM.gskdb" ) ;

	return 0 ;
}