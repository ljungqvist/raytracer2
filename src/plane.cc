
#include "plane.hh"

Plane::Plane() {}
Plane::Plane(Vect& n_, const lu d_) : 
		n(n_.getUnitVect()), 
		d(d_*n.getX()/n_.getX()) { }
Plane::Plane(const lu n1, const lu n2, const lu n3, const lu d_) : 
		n(Vect(n1, n2, n3).getUnitVect()), 
		d(d_*n.getX()/n1) { }
Plane::Plane(const Vect& v1, const Vect& v2, const Vect& v3, const Vect& direction, const bool opposite) :
		n(((v2 - v1) % (v3 - v1)).getUnitVect()), d(-(n * v1)) {
	if ((n * direction + d >= 0) == opposite) { n = -n; d = -d; }
}
Plane::Plane(Vect n_, const Vect& point) :
		n(n_.getUnitVect()), d(-(n * point)) { }
Plane::Plane(const Plane& p) : n(p.normal()), d(p.d_const()) {}
Plane& Plane::operator = (const Plane& p) { n = p.normal(); d = p.d_const(); return *this; }
bool Plane::operator == (const Plane& p) { return n == p.normal() and d == p.d_const(); }
lu Plane::distance(const Vect& v) const { return n * v + d; }
lu Plane::crossing(Ray& r) const {
	lu denominator = r.direction.getUnitVect() * n;
	if (denominator == 0) return -1;
	return -(d + r.origin * n) / denominator; 
}
Vect Plane::normal() const { return n; }
lu Plane::d_const() const { return d; }




