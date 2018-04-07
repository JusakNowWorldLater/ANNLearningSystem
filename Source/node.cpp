#include <cstdlib>
#include <cmath>
#include "cfg.h"
#include "node.h"
#include "gskfunctions.h"

Node::Node( int nodesNumberInNextLayer , double shift ) 
{
	m_shift = shift ;
	for( int i = 0 ; i < nodesNumberInNextLayer ; i++ )
		m_weights.push_back( -0.5f + static_cast<double>(  rand() % static_cast<int>(pow( 10 , gsk::depthOfCalculating ) ) ) / pow( 10 , gsk::depthOfCalculating ) ) ;
}

Node::Node( std::vector<double> weights , double shift ) 
{
	m_shift = shift ;
	m_weights = weights ;
}

double Node::calculateValue( ) 
{
	return gsk::function::sigmoid( m_input ) ;
} 

double Node::getInput( ) 
{
	return m_input ;
} 

double Node::getWeightOf( int index ) 
{
	return m_weights[ index ] ;
}

void Node::changeWeightOf( int index , double deltaWeight ) 
{
	m_weights[index] += deltaWeight ;
}

int Node::getSize()
{
	return m_weights.size() ;
}

/*void Node::inputData( std::vector<Node> & lastLayer )
{
	m_input = m_shift ;
	for( auto node : lastLayer )
	{
		m_input += node.getWeightOf( m_index ) * node.calculateValue() ;
	}
}*/

void Node::inputData( double input )
{
	m_input = input ;
}