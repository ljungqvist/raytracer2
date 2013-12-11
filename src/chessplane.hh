#ifndef AALTO_AS_CPP_RAYTRACER11_CHESSPLANE_H_
#define AALTO_AS_CPP_RAYTRACER11_CHESSPLANE_H_

#include "thingplane.hh"

#include "matrix.hh"

class ChessPlane : public ThingPlane {
	public:
		ChessPlane(const Material mat1, const Material mat2, const Vect v[4]);
		Material getMaterial(const Ray& ray) const;
		Material getMaterial(const Vect& position) const;
		Colour getColour(Ray& ray);
		Colour getColour(Vect& position);
	private:
		Material material2;
		Vect vect[3];
		Matrix transform;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_CHESSPLANE_H_
