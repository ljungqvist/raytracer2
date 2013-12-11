
#include "torus.hh"

#include <cmath>

// for testing
#include <iostream>

#include "rt_math.hh"

Torus::Torus(const Material mat, const Ray& axis_, const lu R_, const lu r_) :
		SimpleThing(mat), 
		axis(axis_), 
		R(R_),
		r(r_),
		sphere(mat, axis_.origin, R_+r_),
		m() {
	axis.direction.normalize();
	m.rotToZ(axis.direction);
	std::cout << m;
}

inline lu Torus::f(const lu t, const Ray& ray) const {
	lu ax = ray.origin[0], ay = ray.origin[1], az = ray.origin[2];
	lu bx = ray.direction[0], by = ray.direction[1], bz = ray.direction[2];
	lu x = ax+bx*t, y = ay+by*t, z = az+bz*t;
	lu p = R - sqrt(x*x+y*y);
	return p*p + z*z - r*r;
}
inline lu Torus::df(const lu t, const Ray& ray) const {
	lu ax = ray.origin[0], ay = ray.origin[1]/*, az = ray.origin[2]*/;
	lu bx = ray.direction[0], by = ray.direction[1]/*, bz = ray.direction[2]*/;
	lu a = ax+bx*t, b = ay+by*t;
	lu sqr = sqrt(a*a+b*b);
	return (2*(ax*bx+ay*by+(bx*bx+by*by)*t)*(sqr-R))/sqr;
}
lu Torus::checkR(Ray& ray, lu min, lu max, bool outer) const {
	if (min < 0 && max < 0) {
		if (outer) return min;
		return max;
	}
	Ray rr;
	rr.origin = m*(ray.origin - axis.origin);
	rr.direction = m*ray.direction;
	rr.direction.normalize();
	if (min < 0) min = DELTA_LU;
	lu val = f(min, rr);
	if (outer && val < 0) return -1;
	lu t = min;
	while (t <= max && val >= 0) {
		t += DELTA_LU;
		val = f(t, rr);
	}
	if (outer) {
//		return t-DELTA_LU;
		if (t <= max) {
//			std::cout << "t=" << t << std::endl;
			return t-DELTA_LU;
		}
//		std::cout << "s=" << t << std::endl;
		return -1;
	}
	while (t <= max && val < 0) {
		t += DELTA_LU;
		val = f(t, rr);
	}
	if (t <= max) return t-DELTA_LU;//-DELTA_LU;
	return -1;
}
lu Torus::checkRay(Ray& ray, const lu /*max*/) {
	lu min = sphere.checkRay(ray, -1) - DELTA_LU;
	lu max = sphere.checkInnerRay(ray) + DELTA_LU;
	return checkR(ray, min, max, true);
}

lu Torus::checkInnerRay(Ray& ray) const {
	lu min = (static_cast<Sphere>(sphere)).checkRay(ray, -1);
	lu max = sphere.checkInnerRay(ray);
	return checkR(ray, min, max, false);
}

Vect Torus::normal(const Vect& position) const {
	Vect v = position - axis.origin;
	v = v - ((v - (axis.direction * v) * axis.direction).getUnitVect() * R);
	return v;
}
lu Torus::sqDistFromMajor(const Vect& position) const {
	Vect v = normal(position);
	return v * v;
}
Vect Torus::getNormal(const Vect& position) const {
	return normal(position).getUnitVect();
}
bool Torus::wraps(const Vect& position) const {
	lu r_ = r - DELTA_LU;
	return	sqDistFromMajor(position) <= r_*r_;
}
bool Torus::onSurface(const Vect& position) const {
	lu dist = sqDistFromMajor(position);
	lu r_m = r - DELTA_LU;
	lu r_p = r + DELTA_LU;
	return (dist < r_p*r_p) and (dist > r_m*r_m);
}




