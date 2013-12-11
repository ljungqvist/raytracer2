
#include "vect.hh"

#include <cmath>

//for testing
// #include <iostream>

Vect Vect::null_ = Vect(0,0,0);

// constructors:
Vect::Vect() : len(-1), x(0), y(0), z(0) { }
Vect::Vect(const lu a1, const lu a2, const lu a3) : len(-1), x(a1), y(a2), z(a3) { }
Vect::Vect(const lu*& a) : len(-1), x(a[0]), y(a[1]), z(a[2]) {}
Vect::Vect(const Vect& v) : len(v.len), x(v.getX()), y(v.getY()), z(v.getZ()) { }

Vect& Vect::operator = (const Vect& v) {
	x = v.getX();
	y = v.getY();
	z = v.getZ();
	len = v.len;
	return *this;
}

Vect Vect::operator + (const Vect& v) const {
	return Vect(x + v.getX(), y + v.getY(), z + v.getZ());
}
Vect operator - (const Vect& v) { 
	return Vect(-(v.getX()), -(v.getY()), -(v.getZ())); 
}
Vect Vect::operator - (const Vect& v) const {
	return (-v) + *this;
}

lu Vect::operator * (const Vect& v) const {	// vector multiplication
	return x*v.getX() + y*v.getY() + z*v.getZ();
}

Vect Vect::operator % (const Vect& v) const {
	return Vect(y*v.getZ() - z*v.getY(), z*v.getX() - x*v.getZ(), x*v.getY() - y*v.getX());
}

Vect& Vect::operator += (const Vect& v){
	return *this = *this + v;
}
Vect& Vect::operator -= (const Vect& v){
	x -= v.getX();
	y -= v.getY();
	z -= v.getZ();
	len = -1;
	return *this;
}

Vect Vect::operator * (const lu a) const {
	return Vect(this->getX() * a, this->getY() * a, this->getZ() * a);
}
// nb not member function -> no Vect::
Vect operator * (const lu a, const Vect& v) { return v * a; }
Vect Vect::operator / (const lu a) const { return *this * (1/a); }

Vect& Vect::operator /= (const lu a) { return *this = *this / a; }
Vect& Vect::operator *= (const lu a) { return *this = *this * a; }

bool Vect::operator == (const Vect& v) const {
	return (x == v.getX() && y == v.getY() && z == v.getZ()); }
bool Vect::operator != (const Vect& v) const { return !(*this == v); }

lu& Vect::operator [] (const size_t ind) {
	if (ind == 0) return x;
	if (ind == 1) return y;
	return z;
}
lu Vect::operator [] (const size_t ind) const {
	if (ind == 0) return x;
	if (ind == 1) return y;
	return z;
}

lu Vect::length() {
	if (len == -1)
		len = sqrt(x*x + y*y + z*z);
	return len;
}

Vect Vect::getUnitVect() {
	if (length() == 0) return *this;
	Vect ret(*this / length());
	ret.len = 1;
	return ret;
}
Vect& Vect::normalize() {
	return *this = getUnitVect();
}

Vect Vect::getReflection(Vect& normal) {
	return *this - 2 * (*this * normal) * normal;
}
Vect Vect::getRefraction(Material::reflInd n1, Material::reflInd n2, Vect& normal) {
	lu a1, b1, c1, a2;
	Vect a1_v, b2_v;
	b1 = -normal * *this;
	if (b1 < 0) {
		b1 = -b1;
		normal = -normal;
	}
	c1 = this->length();
	a1_v = *this + b1 * normal;
	a1 = a1_v.length();
	a2 = a1/c1 * n1/n2;
	if (a2 > 1) { return Vect(0, 0, 0);}
	b2_v = sqrt(1-a2*a2) * (-normal);	return b2_v + a2/a1 * a1_v;
}

lu Vect::getX() const { return x; }
lu Vect::getY() const { return y; }
lu Vect::getZ() const { return z; }

Vect& Vect::null() { return null_; }

// Annin lisäämää
/*
Vect x(const Vect& f, const Vect& u) {
	return Vect(f.getY()*u.getZ() - f.getZ()*u.getY(), f.getZ()*u.getX() - f.getX()*u.getZ(), f.getX()*u.getY() - f.getY()*u.getX());
}
*/


