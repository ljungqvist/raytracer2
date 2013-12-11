#ifndef AALTO_AS_CPP_RAYTRACER11_MATRIX_H_
#define AALTO_AS_CPP_RAYTRACER11_MATRIX_H_

#include "vect.hh"

#include <iostream>

class Matrix {
	public:
		Matrix();
		Matrix(const lu& a);
		Matrix(const Matrix& m);
		Matrix(const Vect& v1, const Vect& v2, const Vect& v3);
		Matrix(const Vect*& v);
		Matrix(	const lu& a11, const lu& a12, const lu& a13,
				const lu& a21, const lu& a22, const lu& a23,
				const lu& a31, const lu& a32, const lu& a33);
		Matrix(const lu**& a);
		~Matrix();
		Matrix& operator = (const Matrix& m);
		bool operator == (const Matrix& m) const;
		bool operator != (const Matrix& m) const;
		lu*& operator [] (const size_t ind);
		lu*& operator [] (const size_t ind) const;
		Vect getVect(size_t ind);
		Matrix operator + (const Matrix& m) const;
		friend Matrix operator - (const Matrix& m);
		Matrix operator - (const Matrix& m) const;
		Matrix operator * (const Matrix& m) const;
		Vect operator * (const Vect& m) const;
		Matrix& operator += (const Matrix& m);
		Matrix& operator -= (const Matrix& m);
		lu det() const;
		Matrix getInverse() const;
		Matrix& invert();
		void rotToZ(const Vect& v);
		friend std::ostream& operator << (std::ostream& os, const Matrix& ob);
	private:
		void Init();
		lu** matrix;
};


#endif	// AALTO_AS_CPP_RAYTRACER11_MATRIX_H_
