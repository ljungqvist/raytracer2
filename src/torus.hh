#ifndef AALTO_AS_CPP_RAYTRACER11_TORUS_H_
#define AALTO_AS_CPP_RAYTRACER11_TORUS_H_

#include "simplething.hh"
#include "sphere.hh"
#include "matrix.hh"

class Torus : public SimpleThing {
	public:
		Torus(const Material mat, const Ray& axis_, const lu R_, const lu r_);
		lu checkRay(Ray& ray, const lu max);
		lu checkInnerRay(Ray& ray) const;
		Vect getNormal(const Vect& position) const;
		bool wraps(const Vect& position) const;
		bool onSurface(const Vect& position) const;
	private:
		inline lu f(const lu t, const Ray& ray) const;
		inline lu df(const lu t, const Ray& ray) const;
		/*
		lu checkR(Ray& ray, bool outer) const;
		lu checkR(Ray& ray, bool outer);
		*/
		lu checkR(Ray& ray, lu min, lu max, bool outer) const;
		Vect normal(const Vect& position) const;
		lu sqDistFromMajor(const Vect& position) const;
		
		Ray axis; //  ray startin from the centre of the torus 
		lu R, r; // major radius restp. minor radius
		Sphere sphere;
		Matrix m;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_TORUS_H_
