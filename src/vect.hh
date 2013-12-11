#ifndef AALTO_AS_CPP_RAYTRACER11_VECT_H_
#define AALTO_AS_CPP_RAYTRACER11_VECT_H_

#include "material.hh" // should be forward declared

typedef double lu;

class Vect {
	public:
		Vect();
		Vect(const lu a1, const lu a2, const lu a3);
		Vect(const lu*& a);
		Vect(const Vect& v);
		Vect& operator = (const Vect& v);
		Vect operator + (const Vect& v) const;
		friend Vect operator - (const Vect& v);	// Not member function
		Vect operator - (const Vect& v) const;
		lu operator * (const Vect& v) const;	// vector multiplication
		Vect operator % (const Vect& v) const;	// Kryssprodukt av två vektorer
		Vect& operator += (const Vect& v);
		Vect& operator -= (const Vect& v);
		Vect operator * (const lu a) const;
		friend Vect operator * (const lu a, const Vect& v);	// Not member function
		Vect operator / (const lu a) const;
		Vect& operator /= (const lu a);
		Vect& operator *= (const lu a);
		bool operator == (const Vect& v) const;
		bool operator != (const Vect& v) const;
		lu& operator [] (const size_t ind);
		lu operator [] (const size_t ind) const;
		lu length();
		Vect getUnitVect();	// Vect in 
		Vect& normalize();
		Vect getReflection(Vect& normal);
		Vect getRefraction(Material::reflInd n1, Material::reflInd n2, Vect& normal);
		lu getX() const; // so that other functions
		lu getY() const; // can use the coordinates
		lu getZ() const; // as well.
		
		static Vect& null();
		
		// Annis ändringar
		// Kryssprodukt av två vektorer
		//friend Vect x(const Vect f, const Vect u);
	
	protected:
		lu len;
	
	private:
		lu x;
		lu y;
		lu z;
		static Vect null_;
};

// outside of the class because the 
//Vect& operator + (const Vect& v);
//Vect& operator - (const Vect& v);


#endif	// AALTO_AS_CPP_RAYTRACER11_VECT_H_
