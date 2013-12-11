#ifndef AALTO_AS_CPP_RAYTRACER11_RT_MATH_H_
#define AALTO_AS_CPP_RAYTRACER11_RT_MATH_H_

#include "structs.hh"

namespace rtMath {
	lu distance(Vect point, Ray line);
	
	double getAngle(size_t i, size_t resolution, double maxAngle) ;
}



#endif	//AALTO_AS_CPP_RAYTRACER11_RT_MATH_H_
