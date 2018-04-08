#include "perceptron.h"
#include "cfg.h"
#include "gskfunctions.h"
#include <fstream>
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

Perceptron::Perceptron( std::string fileName ) : m_learnKoef( gsk::learnKoef )
{
	std::ifstream fIn( fileName ) ;

	std::string line ;

	std::getline( fIn , line ) ;

	int layerCount = std::stoi( line ) , tmpInt ; 
	std::vector<int> configuration ;
	double tmpDouble ;

	for( int i = 0 ; i < tmpInt ; i++ )
	{
		std::getline( fIn , line ) ;
		tmpInt = std::stoi( line ) ;
		configuration.push_back( tmpInt ) ;
	}

	for( int i = 0 ; i < configuration.size() ; i++ )
	{
		if( i != configuration.size() - 1 )
			m_layers.push_back(Layer( configuration[i] , configuration[ i + 1 ] ) ) ;
		else
			m_layers.push_back(Layer( configuration[i] , 0 ) ) ;

	}

	for( auto & layer : m_layers )
	{
		for( int i = 0 ; i < layer.getSize() ; i++ )
		{
			for( int j = 0 ; j < layer.getNode( i ).getSize() ; j++ )
			{
				std::getline( fIn , line ) ;
				tmpDouble = std::stof( line ) ;
				layer.getNode( i ).changeWeightOf( j , -1.0f * layer.getNode( i ).getWeightOf( j ) + tmpDouble ) ;
			}
		}
	}

	fIn.close() ;


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
	for( int repeat = 0 ; repeat < gsk::repeatingInStuding ; repeat++ )
	{
		std::vector<double> networkAnswers = calculate( input ) ;

		for( int i = 0 ; i < networkAnswers.size() ; i++ )
		{
			std::vector< std::vector<double> > errors ;
			errors.resize( m_layers.size() ) ;

			errors[ m_layers.size() - 1 ].push_back( trueAnswers[i] - networkAnswers[i] ) ;

			

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
			errors[ i ] += layer.getNode( i ).getWeightOf( j ) * lastLayerErrors[ j ] ;
		}
	}


	return errors ;
}

void Perceptron::save( std::string fileName )
{
	std::ofstream fOut( fileName );

	fOut << m_layers.size() << std::endl ;

	for( auto layer : m_layers )
		fOut << layer.getSize() << std::endl ;

	for( auto layer : m_layers )
	{
		for( int i = 0 ; i < layer.getSize() ; i++ )
		{
			for( int j = 0 ; j < layer.getNode( i ).getSize() ; j++ )
				fOut << layer.getNode( i ).getWeightOf( j ) << std::endl ;				
		}
	}

	fOut.close() ;

}