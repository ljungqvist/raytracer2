#ifndef AALTO_AS_CPP_RAYTRACER11_LAMPSPHERE_H_
#define AALTO_AS_CPP_RAYTRACER11_LAMPSPHERE_H_

#include "structs.hh"
#include "thing.hh"

class LampSphere : public Thing {
	public:
		LampSphere(Colour col, const Vect& c, const lu r);
		lu checkRay(Ray& ray, const lu max);
		lu checkInnerRay(Ray& ray) const;
		Material getMaterial(const Ray& ray) const;
		Material getMaterial(const Vect& position) const;
		Colour getColour(Ray& ray);
		Colour getColour(Vect& position);
		Vect getNormal(const Vect& position) const;
		bool wraps(const Vect& position) const;
		bool onSurface(const Vect& position) const;
	private:
		Material mat;
		Vect cent;
		lu r;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_LAMPSPHERE_H_
