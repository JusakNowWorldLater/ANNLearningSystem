#include "gskfunctions.h"
#include <cmath>

double gsk::function::sigmoid( double x )
{
	return 1.0f / ( 1 + exp( -x ) ) ;
}