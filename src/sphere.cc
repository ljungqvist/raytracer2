
#include "sphere.hh"

#include <math.h>

//temp
//#include <iostream>

#include "rt_math.hh"
//#include "world.hh"

Sphere::Sphere(const Material m_, const Vect& c_, const lu r_)
		: SimpleThing(m_), cent(c_), r(r_) { }

lu Sphere::checkRay(Ray& ray, const lu /*max*/) {
	if (rtMath::distance(cent, ray) <= r) {
		Vect cent_point = (ray.origin) - cent;
		Vect dir = ray.direction.getUnitVect();
		lu b = 2 * (cent_point * dir);
		lu c = (cent_point * cent_point) - (r * r);
		lu discr = b * b - 4 * c;
		return (-b - sqrt(discr)) / 2;
	}
	return -1;
}

lu Sphere::checkInnerRay(Ray& ray) const {
	Vect cent_point = (ray.origin) - this->cent;
	Vect dir = ray.direction / ray.direction.length();
	lu b = 2 * (cent_point * dir);
	lu c = (cent_point * cent_point) - (r * r);
	lu discr = b * b - 4 * c;
	if (discr < 0) return -1;
	return (-b + sqrt(discr)) / 2;
}

Vect Sphere::getNormal(const Vect& position) const {
	return (position - cent).getUnitVect();
}
bool Sphere::wraps(const Vect& position) const {
	Vect diff = position - cent;
	lu r_minus = r -  DELTA_LU;
	return diff * diff < r_minus * r_minus; 
}
bool Sphere::onSurface(const Vect& position) const {
	Vect diff = position - cent;
	lu dist = diff.length() - r;
	return -DELTA_LU <= dist and dist <= DELTA_LU;
}
