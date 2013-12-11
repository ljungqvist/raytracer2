#ifndef AALTO_AS_CPP_RAYTRACER11_THINGPLANE_H_
#define AALTO_AS_CPP_RAYTRACER11_THINGPLANE_H_

#include "thing.hh"

#include "plane.hh"

class ThingPlane : public Thing {
	public:
		ThingPlane(const Material mat, const Plane pl);
		ThingPlane(const Material mat, const Vect v[4]);
		lu checkRay(Ray& ray, const lu max);
		lu checkInnerRay(Ray& ray) const;
		Material getMaterial(const Ray& ray) const;
		Material getMaterial(const Vect& position) const;
		Colour getColour(Ray& ray);
		Colour getColour(Vect& position);
		Vect getNormal(const Vect& position) const;
		bool wraps(const Vect& position) const;
		bool onSurface(const Vect& position) const;
	protected:
		Material material;
		Plane plane;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_THINGPLANE_H_
