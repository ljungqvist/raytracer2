#ifndef AALTO_AS_CPP_RAYTRACER11_CSG_H_
#define AALTO_AS_CPP_RAYTRACER11_CSG_H_

#include "simplething.hh"

class CSG : public SimpleThing
{
	public:
		CSG(Material mat);
		CSG(Material mat, SimpleThing* l, char b, SimpleThing* r);
		~CSG();
		void setLeft(SimpleThing* thing);
		void setRight(SimpleThing* thing);
		void setBinOp(char b);
		lu checkRay(Ray&, const lu);
		lu checkInnerRay(Ray&) const;
		Vect getNormal(const Vect&) const;
		bool wraps(const Vect&) const;
		bool onSurface(const Vect& position) const;

	private:
		CSG& operator = (CSG&);
		SimpleThing* left;
		SimpleThing* right;
		char binOp; // 'U': union (default), 'I': intersection, 'C': complement
};

#endif	// AALTO_AS_CPP_RAYTRACER11_CSG_H_
