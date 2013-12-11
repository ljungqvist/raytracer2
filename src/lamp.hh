#ifndef AALTO_AS_CPP_RAYTRACER11_LAMP_H_
#define AALTO_AS_CPP_RAYTRACER11_LAMP_H_

#include "light.hh"

class Lamp : public Light {
	public:
		Lamp(const Vect& pos, const Colour col, lu s);
		LightRay illumination(Vect& position) const;
		Vect getPosition();
		void addToWorld();
	private:
		Vect position;
		Colour colour;
		lu size;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_LAMP_H_
