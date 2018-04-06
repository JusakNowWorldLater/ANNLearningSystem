#ifndef LAYER_H
#define LAYER_H


#include <vector>
#include "node.h"


class Layer
{
public:
	Layer( int nodeCount , int nextNodeCount ) ;
	Layer( std::vector<Node> nodes ) ;
	int getSize() ;
	Node & getNode( int index ) ;
	void takeLastLayer( Layer & layer ) ;
	void takeInput( std::vector<double> input ) ;
private:
	static int layerCount ;
	const int m_index ;
	std::vector<Node> m_nodes ;
};


#endif//LAYER_H