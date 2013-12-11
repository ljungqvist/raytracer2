#ifndef AALTO_AS_CPP_RAYTRACER11_LIGHT_H_
#define AALTO_AS_CPP_RAYTRACER11_LIGHT_H_

#include "structs.hh"

class Light {
	public:
		Light() {}
		virtual ~Light() {}
		virtual LightRay illumination(Vect& position) const =0;
		virtual Vect getPosition() =0;
		virtual void addToWorld() =0;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_LIGHT_H_
