#ifndef AALTO_AS_CPP_RAYTRACER11_MATERIAL_H_
#define AALTO_AS_CPP_RAYTRACER11_MATERIAL_H_

#include "colour.hh"

class Material {
	
	public:
		typedef float matInd; // skall vara i klassen men refereras till med Material::matInd.
		typedef float tanslInd;
		typedef float reflInd;
	
		Material();
		Material(const Colour);
		Material(	const matInd refl,
					const matInd refr,
					const matInd scat,
					const tanslInd transl,
					const reflInd reflind,
					const Colour col);
		Colour getColour() const;
		matInd getReflection() const;	
		matInd getRefraction() const;
		matInd getScattering() const;
		tanslInd getTranslusans() const;
		reflInd getRefractive_index() const;
		
		static matInd mZero;
		
	private:
		matInd reflection;	// these three 
		matInd refraction;	// must add 
		matInd scattering;	// up to exactly one!
		tanslInd translusans;
		reflInd refractive_index;	// >= 1
		Colour colour;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_MATERIAL_H_
