#include "layer.h"
#include "cfg.h" 
#include "gskfunctions.h"

int Layer::layerCount = -1 ;

Layer::Layer( int nodeCount , int nextNodeCount ) : m_index( ++layerCount )
{
	for( int i = 0 ; i < nodeCount ; i++ )
		m_nodes.push_back( Node( nextNodeCount ) ) ;
}

Layer::Layer( std::vector<Node> nodes ) : m_index( ++layerCount )
{
	m_nodes = nodes ;
}

void Layer::takeLastLayer( Layer & layer )
{
	for( int i = 0 ; i < m_nodes.size() ; i++ )
	{
		double input = 0 ;

		for( int j = 0 ; j < layer.m_nodes.size() ; j++ )
		{
			input += layer.m_nodes[ j ].getInput() * layer.m_nodes[ j ].getWeightOf( i ) ; 
		}
		m_nodes[ i ].inputData( gsk::function::sigmoid( input ) ) ;
	}
}

void Layer::takeInput( std::vector<double> input )
{
	if( m_index == 0 && input.size() == m_nodes.size() )
	{
		for( int i = 0 ; i < input.size() ; i++ )
			m_nodes[ i ].inputData( input[ i ] ) ;
	}
}

int Layer::getSize()
{
	return m_nodes.size() ;
}

Node & Layer::getNode( int index ) 
{
	return m_nodes[ index ] ;
}