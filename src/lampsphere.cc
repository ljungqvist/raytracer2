
#include "lampsphere.hh"

#include <cmath>

#include "rt_math.hh"

LampSphere::LampSphere(Colour col, const Vect& c_, const lu r_)
		: mat(0,0,1,0,0,col), cent(c_), r(r_) { }

lu LampSphere::checkRay(Ray& ray, const lu /*max*/) {
	if (rtMath::distance(cent, ray) <= r)
		return (cent - ray.origin).length();
	return -1;
}

lu LampSphere::checkInnerRay(Ray& /*ray*/) const {
	return -1;
}

Material LampSphere::getMaterial(const Ray& /*ray*/) const { return mat; }
Material LampSphere::getMaterial(const Vect& /*position*/) const { return mat; }

Colour LampSphere::getColour(Ray& ray) {
	lu dist = rtMath::distance(cent, ray);
	if (dist < r)
		return mat.getColour() * pow((r - dist) / r, 5);
	return Colour::black();
}
Colour LampSphere::getColour(Vect& position) {
	lu dist = (cent - position).length();
	if (dist < r)
		return mat.getColour() * pow((r - dist) / r, 5);
	return Colour::black();
}

Vect LampSphere::getNormal(const Vect& /*position*/) const {
	return Vect::null();
}
bool LampSphere::wraps(const Vect& /*position*/) const {
	return false; 
}
bool LampSphere::onSurface(const Vect& /*position*/) const {
	return false;
}

