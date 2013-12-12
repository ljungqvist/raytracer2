
#include "matrix.hh"
#include <cmath>
// #include <iostream> // debug

Matrix::Matrix() { Init(); }
Matrix::Matrix(const lu& a) {
	Init();
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix[i][j] = a;
}
Matrix::Matrix(const Matrix& m) {
	Init();
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix[i][j] = m[i][j];
}
Matrix::Matrix(const Vect& v1, const Vect& v2, const Vect& v3) {
	Init();
	for (size_t i = 0; i < 3; ++i) {
		matrix[i][0] = v1[i];
		matrix[i][1] = v2[i];
		matrix[i][2] = v3[i];
	}
}
Matrix::Matrix(const Vect*& v) {
	Init();
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix[i][j] = v[j][i];
}
Matrix::Matrix(	const lu& a11, const lu& a12, const lu& a13,
				const lu& a21, const lu& a22, const lu& a23,
				const lu& a31, const lu& a32, const lu& a33) {
	Init();
	matrix[0][0] = a11; matrix[0][1] = a12; matrix[0][2] = a13; 
	matrix[1][0] = a21; matrix[1][1] = a22; matrix[1][2] = a23; 
	matrix[2][0] = a31; matrix[2][1] = a32; matrix[2][2] = a33; 
}
Matrix::Matrix(const lu**& a) {
	Init();
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix[i][j] = a[i][j];
}
Matrix::~Matrix() {
	for (size_t i = 0; i < 3; ++i)
		delete[] (matrix[i]);
	delete[] matrix;
}
Matrix& Matrix::operator = (const Matrix& m) {
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			matrix[i][j] = m[i][j];
	return *this;
}
bool Matrix::operator == (const Matrix& m) const {
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			if (matrix[i][j] != m[i][j])
				return false;
	return true;
}
bool Matrix::operator != (const Matrix& m) const { return !(*this == m); }
lu*& Matrix::operator [] (size_t ind) { return matrix[ind]; }
lu*& Matrix::operator [] (size_t ind) const { return matrix[ind]; }
Vect Matrix::getVect(size_t ind) { 
	return Vect(matrix[1][ind], matrix[2][ind], matrix[3][ind]);
}
Matrix Matrix::operator + (const Matrix& m) const {
	Matrix ret;
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			ret[i][j] = (*this)[i][j] + m[i][j];
	return ret;
}
Matrix operator - (const Matrix& m) {
	Matrix ret;
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			ret[i][j] = -(m[i][j]);
	return ret;
}
Matrix Matrix::operator - (const Matrix& m) const { return *this + (-m); }
Matrix Matrix::operator * (const Matrix& m) const {
	Matrix ret(0);
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			for (size_t k = 0; k < 3; ++k)
				ret[i][j] += (*this)[i][k] * m[k][j];
	return ret;
}
Vect Matrix::operator * (const Vect& m) const {
	Vect ret;
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			ret[i] += matrix[i][j] * m[j];
	return ret;
}
Matrix& Matrix::operator += (const Matrix& m) { return *this = *this + m; }
Matrix& Matrix::operator -= (const Matrix& m) { return *this += -m; }
lu Matrix::det() const {
	lu ret = 0;
	for (size_t i = 0; i < 3; ++i)
		ret += matrix[0][i] * (matrix[1][(i+1)%3] * matrix[2][(i+2)%3] - matrix[1][(i+2)%3] * matrix[2][(i+1)%3]);
	return ret;
}
Matrix Matrix::getInverse() const {
	Matrix ret;
	lu det = this->det();
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
			ret[j][i] += (matrix[(i+1)%3][(j+1)%3] * matrix[(i+2)%3][(j+2)%3] - 
						  matrix[(i+1)%3][(j+2)%3] * matrix[(i+2)%3][(j+1)%3]) 
						  / det;
	return ret;
}
Matrix& Matrix::invert() { return *this = this->getInverse(); }
void Matrix::rotToZ(const Vect& v) {
	lu x = v[0], y = v[1], z = v[2];
	lu sqr = sqrt(x*x+y*y);
	lu z_ = 1-z;
	matrix[0][0] = z+y*y*z_; matrix[0][1] = -x*y*z_;  matrix[0][2] = -x*sqr; 
	matrix[1][0] = -x*y*z_;  matrix[1][1] = z+x*x*z_; matrix[1][2] = -y*sqr; 
	matrix[2][0] = x*sqr;    matrix[2][1] = y*sqr;    matrix[2][2] = z; 
}
std::ostream& operator << (std::ostream& os, const Matrix& ob) {
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j)
			os << ob[i][j] << "\t";
		os << "\n";
	}
	return os;
}

//private
void Matrix::Init() {
	matrix = new lu*[3];
	for (size_t i = 0; i < 3; ++i) 
		matrix[i] = new lu[3];
}









