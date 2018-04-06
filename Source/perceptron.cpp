#include "perceptron.h"

Perceptron::Perceptron( std::vector<int> configuration )
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

/*void Perceptron::study( std::vector<double> input , std::vector<double> trueAnswer )
{
	std::vector<double> networkAnswers = calculate( input ) ;

	for( int i = 0 ; i < networkAnswers.size() ; i++ )
	{
		std::vector< std::vector<double> > errors ;
		errors.resize( m_layers.size() ) ;

		for( int i = m_layers.size() - 1 ; i >= 0 ; i++ )
		{
			for()
			if( i == m_layers.size() - 1 )
				errors[i]
		}
	}
}*/