#include "perceptron.h"
#include "cfg.h"
#include "gskfunctions.h"
#include <iostream>

Perceptron::Perceptron( std::vector<int> configuration ) : m_learnKoef( gsk::learnKoef )
{
	for( int i = 0 ; i < configuration.size() ; i++ )
	{
		if( i != configuration.size() - 1 )
			m_layers.push_back(Layer( configuration[i] , configuration[ i + 1 ] ) ) ;
		else
			m_layers.push_back(Layer( configuration[i] , 0 ) ) ;

	}
}

Layer & Perceptron::getLayer( int index ) 
{
	return m_layers[ index ] ;
}

int Perceptron::getSize()
{
	return m_layers.size() ;
}

std::vector<double> Perceptron::calculate( std::vector<double> input )
{
	std::vector<double> result ;

	for( int i = 0 ; i < m_layers.size() ; i++ )
	{
		if( i == 0 )
			m_layers[ i ].takeInput( input ) ;
		else
			m_layers[ i ].takeLastLayer( m_layers[ i - 1 ] ) ;
	}

	for( int i = 0 ; i < m_layers[ m_layers.size() - 1 ].getSize() ; i++ )
		result.push_back( m_layers[ m_layers.size() - 1 ].getNode( i ).getInput() ) ;

	return result ;

}

void Perceptron::study( std::vector<double> input , std::vector<double> trueAnswers ) 
{
	for( int repeating = 0 ; repeating < gsk::repeatingInStuding ; repeating++ )
	{
		std::vector<double> networkAnswers = calculate( input ) ;

		for( int i = 0 ; i < networkAnswers.size() ; i++ )
		{
			std::vector< std::vector<double> > errors ;
			errors.resize( m_layers.size() ) ;

			errors[ m_layers.size() - 1 ].push_back( trueAnswers[i] - networkAnswers[i] ) ; //ERROR



			for( int j = 0 ; j < m_layers.size() - 1 ; j++ )
			{
				changeLayerWeightsByErrors( m_layers[j] , m_layers[ j + 1 ] , errors[ j + 1 ] ) ;
			}

			for( int j = m_layers.size() - 2 ; j >= 0 ; j-- ) 
			{
				errors[ j ] = calculateErrorsForLayer( m_layers[ j ] , errors[ j + 1 ] ) ;
			}
		}
	}
}

void Perceptron::changeLayerWeightsByErrors( Layer & currentLayer , Layer & nextLayer , std::vector<double> & lastLayerErrors )
{
	for( int i = 0 ; i < currentLayer.getSize() ; i++ )
	{
		for( int j = 0 ; j < lastLayerErrors.size() ; j++ )
		{
			double derivedFunc = gsk::function::sigmoid( nextLayer.getNode( j ).getInput() ) * ( 1 - gsk::function::sigmoid( nextLayer.getNode( j ).getInput() ) ) ;
			currentLayer.getNode( i ).changeWeightOf( j , lastLayerErrors[ j ] * derivedFunc * currentLayer.getNode( i ).getInput() * m_learnKoef ) ;
		}
	}
}

std::vector<double> Perceptron::calculateErrorsForLayer( Layer & layer , std::vector<double> & lastLayerErrors )
{
	std::vector<double> errors ;

	errors.resize( layer.getSize() ) ;

	for( auto & value : errors )
		value = 0 ;
	
	for( int i = 0 ; i < layer.getSize() ; i++ )
	{
		for( int j = 0 ; j < lastLayerErrors.size() ; j++ )
		{
			//std::cout << layer.getNode( i ).getWeightOf( j ) * lastLayerErrors[ j ] << "  |   LVL " << layer.m_index << " : " << i << "->" << j << std::endl ;
			errors[ i ] += layer.getNode( i ).getWeightOf( j ) * lastLayerErrors[ j ] ;
		}
	}

	//std::cout << std::endl << std::endl << std::endl ;

	return errors ;
}

void Perceptron::showWeights()
{
	for( int i = 0 ; i < m_layers.size() ; i++ )
	{
		std::cout << "LVL " << i << ":" << std::endl ;
		for( int j = 0 ; j < m_layers[ i ].getSize() ; j++ )
		{
			for( int k = 0 ; k < m_layers[ i + 1 ].getSize() ; k++ )
			{
				std::cout << j << "->" << k << " = " << m_layers[i].getNode( j ).getWeightOf( k ) << " " ;
			}
			std::cout << " | " ;
		}

		std::cout << std::endl ;
	}
}