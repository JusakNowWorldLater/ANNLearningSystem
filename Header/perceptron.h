#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include "layer.h"

class Perceptron
{
public:
	Perceptron( std::vector<int> configuration ) ;
	std::vector<double> calculate( std::vector<double> input ) ;
	Layer & getLayer( int index ) ;
	void study( std::vector<double> input , std::vector<double> trueAnswer ) ;
	int getSize() ;
private:
	std::vector<Layer> m_layers ;
};


#endif//PERCEPTRON_H