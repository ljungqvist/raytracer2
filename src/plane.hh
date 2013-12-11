#ifndef AALTO_AS_CPP_RAYTRACER11_PLANE_H_
#define AALTO_AS_CPP_RAYTRACER11_PLANE_H_

#include "structs.hh"

// Vilken av konstruktorerna skall användas huvudsakligen? Den med n1, n2, n3 och d?

class Plane {
	public:
		Plane();
		Plane(Vect& n_, const lu d_);
		Plane(const lu n1, const lu n2, const lu n3, const lu d_);
		Plane(	const Vect& v1, 
				const Vect& v2, 
				const Vect& a3, 
				const Vect& direction = Vect::null(), 
				const bool opposite = true);
		Plane(Vect n_, const Vect& point);
		Plane(const Plane& p);
		Plane& operator = (const Plane& p);
		bool operator == (const Plane& p);
		lu distance(const Vect& v) const;
		lu crossing(Ray& r) const;
		Vect normal() const;
		lu d_const() const;
	private:
		Vect n;	// n1x + n2x + n3x + d = 0 
		lu d;	// n.length() = 1
};

#endif	// AALTO_AS_CPP_RAYTRACER11_PLANE_H_
