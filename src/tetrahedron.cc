
#include "tetrahedron.hh"

#include <cmath>

// for testing!!
//#include <iostream>

Tetrahedron::Tetrahedron(const Material mat, const Vect& v0, const Vect& v1, const Vect& v2, const Vect& v3)
		: SimpleThing(mat)/*, vect({v0, v1, v2, v3})*/ {
	vect[0] = v0; vect[1] = v1; vect[2] = v2; vect[3] = v3; 
	for (size_t i = 0; i < 4; ++i)
		plane[i] = Plane(vect[(i+0)%4], vect[(i+1)%4], vect[(i+2)%4], vect[(i+3)%4], true);
}

lu Tetrahedron::checkRay(Ray& ray, const lu max) {
	lu retval = -1;
	for (size_t i = 0; i < 4; ++i) {
		lu dist = plane[i].crossing(ray);
		if (dist > 0 and (max < 0 or dist < max)) {
			Vect point = ray.origin + ray.direction.getUnitVect() * dist;
			bool in_triangle = true;
			for (size_t j = 0; j < 4; ++j) {
				if ((i != j) and (plane[j].distance(point) >  DELTA_LU)) {
					in_triangle = false; break;
				}
			}
			if (in_triangle) {
				if (retval > 0.0) {
					if (retval > dist)
						retval = dist;
					break;
				} else retval = dist;
			}
		}
	}
	return retval;
}

lu Tetrahedron::checkInnerRay(Ray& ray) const {
	lu retval = -1;
	for (size_t i = 0; i < 4; ++i) {
		lu dist = plane[i].crossing(ray);
		if (dist > 0) {
			Vect point = ray.origin + ray.direction.getUnitVect() * dist;
			bool in_triangle = true;
			for (size_t j = 0; j < 4; ++j)
				if ((i != j) and (plane[j].distance(point) > DELTA_LU)) {
					in_triangle = false; break;
				}
			if (in_triangle) {
				if (retval > 0.0) {
					if (retval < dist)
						retval = dist;
					break;
				} else retval = dist;
			}
		}
	}
	return retval;
}

Vect Tetrahedron::getNormal(const Vect& position) const {
	for (size_t i = 0; i < 4; ++i)
		if (std::fabs(plane[i].distance(position)) <= DELTA_LU)
			return plane[i].normal();
	return Vect::null();
}
bool Tetrahedron::wraps(const Vect& position) const {
	for (size_t i = 0; i < 4; ++i)
		if (plane[i].distance(position) > -2.0 * DELTA_LU)
			return false;
	return true; 
}
bool Tetrahedron::onSurface(const Vect& position) const {
	for (size_t i = 0; i < 4; ++i)
		if (std::fabs(plane[i].distance(position)) <= DELTA_LU)
			return true;
	return false;
}




