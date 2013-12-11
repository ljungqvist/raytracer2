#ifndef AALTO_AS_CPP_RAYTRACER11_SPHERE_H_
#define AALTO_AS_CPP_RAYTRACER11_SPHERE_H_

#include "simplething.hh"

class Sphere : public SimpleThing {
	public:
		Sphere(const Material mat, const Vect& c, const lu r);
		lu checkRay(Ray& ray, const lu max);
		lu checkInnerRay(Ray& ray) const;
		Vect getNormal(const Vect& position) const;
		bool wraps(const Vect& position) const;
		bool onSurface(const Vect& position) const;
	private:
		Vect cent;
		lu r;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_SPHERE_H_
