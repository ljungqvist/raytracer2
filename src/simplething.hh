#ifndef AALTO_AS_CPP_RAYTRACER11_SIMPLETHING_H_
#define AALTO_AS_CPP_RAYTRACER11_SIMPLETHING_H_

#include "thing.hh"

class SimpleThing : public Thing {
	public:
		SimpleThing(const Material mat);
		Material getMaterial(const Ray& ray) const;
		Material getMaterial(const Vect& position) const;
		Colour getColour(Ray& ray);
		Colour getColour(Vect& position);
	private:
		Material material;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_SIMPLETHING_H_
