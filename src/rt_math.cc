
#include "rt_math.hh"

#include <cmath>

lu rtMath::distance(Vect point, Ray line) {
	Vect origin_point = point - line.origin;
	Vect op_p = origin_point * line.direction.getUnitVect() * line.direction.getUnitVect();
	return (origin_point - op_p).length();
}

double rtMath::getAngle(size_t i, size_t resolution, double maxAngle) {
	
	return maxAngle * (resolution / 2 - i) / resolution;
}
