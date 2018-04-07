#ifndef NODE_H
#define NODE_H

#include <vector> 

class Node 
{
public:
	Node( int nodesNumberInNextLayer , double shift = 0 ) ; 
	Node( std::vector<double> weights , double shift = 0 ) ;
	double calculateValue() ;
	double getInput() ;
	double getWeightOf( int index ) ;
	int getSize() ;
	void inputData( double input ) ;
	void changeWeightOf( int index , double deltaWeight ) ;
private:
	double m_input ;
	double m_shift ;
	std::vector<double> m_weights ;
};

#endif//NODE_H