#include <iostream>
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

	std::cout << "Enter " << perceptron.getLayer( 0 ).getSize() << " values ( 0 - 1 )" << std::endl ;
	std::vector<double> input ;
	for( int i = 0 ; i < perceptron.getLayer( 0 ).getSize() ; i++ )
	{
		double tmp ;
		std::cin >> tmp ;
		input.push_back( tmp ) ;
	}

	std::cout << "Result(s) : " ;

	for( auto result : perceptron.calculate( input ) )
		std::cout << result << " " ;
	
	std::cout << std::endl ;

	return 0 ;
}