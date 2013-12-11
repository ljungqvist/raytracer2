
#include "material.hh"

Material::matInd Material::mZero = (Material::matInd)0;

Material::Material() : 	
		reflection((matInd) 0),
		refraction((matInd) 0),
		scattering((matInd) 1),
		translusans((tanslInd) 0),
		refractive_index((reflInd) 1.0),
		colour( 0.5, 0.5, 0.5) { }
		
Material::Material(const Colour c) :  	
		reflection((matInd) 0),
		refraction((matInd) 0),
		scattering((tanslInd) 0),
		translusans((tanslInd) 0),
		refractive_index((reflInd) 1.0),
		colour(c) { }

Material::Material(	const matInd refl,
					const matInd refr,
					const matInd scat,
					const tanslInd transl,
					const reflInd reflind,
					const Colour col) : 
		reflection(refl),
		refraction(refr),
		scattering(scat),
		translusans(transl),
		refractive_index(reflind),
		colour(col) { }
										
Colour Material::getColour() const { return colour; }
Material::matInd Material::getReflection() const { return reflection; }	
Material::matInd Material::getRefraction() const { return refraction; }
Material::matInd Material::getScattering() const { return scattering; }
Material::tanslInd Material::getTranslusans() const { return translusans; }
Material::reflInd Material::getRefractive_index() const { return refractive_index; }

