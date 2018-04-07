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
	void study( std::vector<double> input , std::vector<double> trueAnswers ) ;
	int getSize() ;
	void showWeights() ;
private:
	std::vector<double> calculateErrorsForLayer( Layer & layer , std::vector<double> & lastLayerErrors ) ;
	void changeLayerWeightsByErrors( Layer & currentLayer , Layer & nextLayer , std::vector<double> & lastLayerErrors ) ;
	std::vector<Layer> m_layers ;
	double m_learnKoef ;
};


#endif//PERCEPTRON_H