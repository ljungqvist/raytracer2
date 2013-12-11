#ifndef AALTO_AS_CPP_RAYTRACER11_COLOUR_H_
#define AALTO_AS_CPP_RAYTRACER11_COLOUR_H_

#include <algorithm>
#include <string>

class Colour {
	
	public:
		typedef float colInd;	// [0.0, Inf) public so it can be used in filereading.cc
		Colour() {}
		Colour(const colInd r, const colInd g, const colInd b);
		Colour(Colour const& colour);
		Colour& operator = (const Colour& colour);
		Colour operator + (const Colour& colour) const;
		Colour operator - (const Colour& colour) const;
		Colour operator * (const Colour& colour) const;
		template <class T>
		Colour operator * (const T a) const {
			if (a <= 0.0) return black_;
			else return Colour((colInd)a * r, (colInd)a * g, (colInd)a * b);
		}
		template <class T>
		friend Colour operator * (const T a, const Colour& colour) { return colour * a; }
		template <class T>
		Colour operator / (const T a) const {
			if (a == 0) return white_;
			else return *this * (1/a); 
		}
		template <class T>
		Colour operator ^ (const T a) const {
			return Colour(pow(r, a), pow(g, a), pow(b, a)); 
		}
		Colour& operator += (const Colour& colour);
		Colour& operator -= (const Colour& colour);
		Colour& operator *= (const Colour& colour);
		template <class T>
		Colour& operator *= (const T a)  { return *this = a * *this; }
		template <class T>
		Colour& operator /= (const T a)  { return *this = *this / a; }
		bool operator == (const Colour& colour) const;
		bool operator != (const Colour& colour) const;
		colInd getRed() const;
		colInd getGreen() const;
		colInd getBlue() const;
		static Colour& black();
		static Colour& white();
		static void setPicColourLimits(const size_t min, const size_t max);
		// puts the converted colour values in the arguments.
		void getPicColours(size_t& r_, size_t& g_, size_t& b_) const; 
		std::string getPicColours() const; // retunrs "255 0 324\t"
		
	private:
		
		colInd r;
		colInd g;
		colInd b;
		
		static Colour black_;
		static Colour white_;
		static size_t pic_colour_min; // the min and max values 
		static size_t pic_colour_max; // for the values ruturned by getPicColours

};

/*
template <class T>
Colour operator * (const T a, const Colour& colour) {	// Not member function
	return Colour(
			std::max(Colour::minInd, std::min(Colour::maxInd, a * colour.getRed())),
			std::max(Colour::minInd, std::min(Colour::maxInd, a * colour.getGreen())),
			std::max(Colour::minInd, std::min(Colour::maxInd, a * colour.getBlue())));
}
template <class T>
Colour operator * (const Colour& colour, const T a) {return a * colour; } // Not member function
template <class T>
Colour operator / (const Colour& colour, const T a) {return (1/a) * colour; } // Not member function
template <class T>
Colour& Colour::operator *= (const T a) { return *this = a * *this; }
*/
#endif	// AALTO_AS_CPP_RAYTRACER11_COLOUR_H_
