
#include "chessplane.hh"

#include <cmath>

// for testing
//#include <iostream>

ChessPlane::ChessPlane(const Material mat1, const Material mat2, const Vect v[4]) : 
		ThingPlane(mat1, v), material2(mat2) {
	//std::cout << "\t\tconstructing chess plane now\n";
	vect[0] = v[0];
	vect[1] = v[1] - v[0];
	vect[2] = v[2] - v[0];
	/*std::cout << "\t\tconstructing chess plane done( not)\n";
	std::cout << "\t\tvect[1] = " << vect[1].getX() << " " << vect[1].getY() << " " << vect[1].getZ() << "\n";
	std::cout << "\t\tvect[2] = " << vect[2].getX() << " " << vect[2].getY() << " " << vect[2].getZ() << "\n";
	std::cout << "\t\tv[3] = " << v[3].getX() << " " << v[3].getY() << " " << v[3].getZ() << "\n";
	std::cout << "\t\tv[0] = " << v[0].getX() << " " << v[0].getY() << " " << v[0].getZ() << "\n";*/
	transform = Matrix(vect[1], vect[2], v[3] - v[0]).getInverse();
	/*std::cout << "\t\tconstructing chess plane done( not 2)\n";
	transform.invert();
	std::cout << "\t\tconstructing chess plane done\n";*/
}
Material ChessPlane::getMaterial(const Ray& ray) const { 
	Ray r;
	r.origin = ray.origin;
	r.direction = ray.direction;
	return getMaterial(r.origin + plane.crossing(r) * r.direction.getUnitVect()); 
}
Material ChessPlane::getMaterial(const Vect& p) const { 
	Vect transfd = transform * (p - vect[0]);
	lu x_check = fmod(transfd.getX(), 2.0);
	lu y_check = fmod(transfd.getY(), 2.0);
	if (x_check < 0) x_check += 2.0;
	if (y_check < 0) y_check += 2.0;
	if ((x_check < 1.0) == (y_check < 1.0))
		return material;
	return material2; 
}
Colour ChessPlane::getColour(Ray& ray) { return getMaterial(ray).getColour(); }
Colour ChessPlane::getColour(Vect& p) { return getMaterial(p).getColour(); }

