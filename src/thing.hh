#ifndef AALTO_AS_CPP_RAYTRACER11_THING_H_
#define AALTO_AS_CPP_RAYTRACER11_THING_H_

#include "material.hh"
#include "structs.hh"

class Thing {
	public:
		//Thing();
		virtual ~Thing() {}
		/* checkRay returns distance to thing. Returns a negative number if   *
		 * ray does nor cross thing. */
		virtual lu checkRay(Ray& ray, const lu max) =0;
		lu checkRay(Ray& ray) { return this->checkRay(ray, -1); }
		/* checkInnerRayreturns the distance to the point where the ray would * 
		 * exit thing. Returns a negative number if ray does not intersect    *
		 * whing thing. */
		virtual lu checkInnerRay(Ray& ray) const =0;
		virtual Material getMaterial(const Ray& ray) const =0;
		virtual Material getMaterial(const Vect& position) const =0;
		virtual Colour getColour(Ray& ray) =0;
		virtual Colour getColour(Vect& position) =0;
		virtual Vect getNormal(const Vect& position) const =0;
		/* wraps returns true if position is within ting. */
		virtual bool wraps(const Vect& position) const =0;
		virtual bool onSurface(const Vect& position) const =0;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_THING_H_
