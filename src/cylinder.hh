#ifndef AALTO_AS_CPP_RAYTRACER11_CYLINDER_H_
#define AALTO_AS_CPP_RAYTRACER11_CYLINDER_H_

#include "plane.hh"
#include "simplething.hh"

class Cylinder : public SimpleThing {
	public:
		Cylinder(const Material mat, const Ray& axis_, const lu r_);
		lu checkRay(Ray& ray, const lu max);
		lu checkInnerRay(Ray& ray) const;
		Vect getNormal(const Vect& position) const;
		bool wraps(const Vect& position) const;
		bool onSurface(const Vect& position) const;
	private:
		Ray axis;
		lu r;
		Plane plane1;
		Plane plane2;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_CYLINDER_H_
