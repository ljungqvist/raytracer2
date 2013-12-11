#ifndef AALTO_AS_CPP_RAYTRACER11_TETRAHEDRON_H_
#define AALTO_AS_CPP_RAYTRACER11_TETRAHEDRON_H_

#include "plane.hh"
#include "simplething.hh"

class Tetrahedron : public SimpleThing {
	public:
		Tetrahedron(const Material mat, const Vect& v0, const Vect& v1, const Vect& v2, const Vect& v3);
		lu checkRay(Ray& ray, const lu max);
		lu checkInnerRay(Ray& ray) const;
		Vect getNormal(const Vect& position) const;
		bool wraps(const Vect& position) const;
		bool onSurface(const Vect& position) const;
	private:
		Vect vect [4];
		Plane plane [4];
};

#endif	// AALTO_AS_CPP_RAYTRACER11_TETRAHEDRON_H_
