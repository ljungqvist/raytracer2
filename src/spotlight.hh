#ifndef AALTO_AS_CPP_RAYTRACER11_SPOTLIGHT_H_
#define AALTO_AS_CPP_RAYTRACER11_SPOTLIGHT_H_

#include "light.hh"

class SpotLight : public Light {
	public:
		SpotLight(const Vect& pos, const Colour col);
		LightRay illumination(Vect& position) const;
		Vect getPosition();
		void addToWorld();
	private:
		Vect position;
		Colour colour;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_SPOTLIGHT_H_
