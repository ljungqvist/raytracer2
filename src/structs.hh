#ifndef AALTO_AS_CPP_RAYTRACER11_STRUCTS_H_
#define AALTO_AS_CPP_RAYTRACER11_STRUCTS_H_

#include "colour.hh"
#include "vect.hh"

typedef double lu;
const lu DELTA_LU=0.000015;

struct Camera {
	Vect position;
	Vect centre;
	Vect up;
	char projection;
	float angle_x;
	float angle_y;
};

struct Ray {
	Vect origin;
	Vect direction;
};

struct LightRay {
	LightRay() {}
	Ray ray;
	Colour colour;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_STRUCTS_H_

