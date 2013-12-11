
#include "colour.hh"

#include <sstream>

Colour Colour::black_ = Colour(0.0, 0.0, 0.0);
Colour Colour::white_ = Colour(1.0, 1.0, 1.0);
size_t Colour::pic_colour_min = 0;
size_t Colour::pic_colour_max = 255;

// constructors
Colour::Colour(const colInd r_, const colInd g_, const colInd b_) : r(r_), g(g_), b(b_) {}
Colour::Colour(const Colour& colour) : r(colour.getRed()), g(colour.getGreen()), b(colour.getBlue()) {}

Colour& Colour::operator = (const Colour& colour) {
	r = colour.getRed();
	g = colour.getGreen();
	b = colour.getBlue();
	return *this;
}

Colour Colour::operator + (const Colour& colour) const {
	return Colour(r + colour.getRed(), g + colour.getGreen(), b + colour.getBlue());
}

Colour Colour::operator - (const Colour& colour) const {
	return Colour(
			std::max((colInd)0.0, r - colour.getRed()),
			std::max((colInd)0.0, g - colour.getGreen()),
			std::max((colInd)0.0, b - colour.getBlue()));
}


Colour Colour::operator * (const Colour& colour) const {
	return Colour( r * colour.getRed(), g * colour.getGreen(), b * colour.getBlue());
}

Colour& Colour::operator += (const Colour& colour) { return *this = *this + colour; }
Colour& Colour::operator -= (const Colour& colour) { return *this = *this - colour; }
Colour& Colour::operator *= (const Colour& colour) { return *this = *this * colour; }

bool Colour::operator == (const Colour& colour) const {
	return (r == colour.getRed() && g == colour.getGreen() && b == colour.getBlue());
}

bool Colour::operator != (const Colour& colour) const {
	return !(*this == colour);
}
		
Colour::colInd Colour::getRed() const { return r; }
Colour::colInd Colour::getGreen() const { return g; }
Colour::colInd Colour::getBlue() const { return b; }

Colour& Colour::black() { return black_; }
Colour& Colour::white() { return white_; }


void Colour::setPicColourLimits(const size_t min, const size_t max) { pic_colour_min = min; pic_colour_max = max; }
void Colour::getPicColours(size_t& r_, size_t& g_, size_t& b_) const { 
	if (r >= 1.0) r_ = pic_colour_max;
	else if (r <= 0.0) r_ = pic_colour_min;
	else r_ = pic_colour_min + (size_t)(r * (double)(pic_colour_max - pic_colour_min));
	
	if (g >= 1.0) g_ = pic_colour_max;
	else if (g <= 0.0) g_ = pic_colour_min;
	else g_ = pic_colour_min + (size_t)(g * (double)(pic_colour_max - pic_colour_min));
	
	if (b >= 1.0) b_ = pic_colour_max;
	else if (b <= 0.0) b_ = pic_colour_min;
	else b_ = pic_colour_min + (size_t)(b * (double)(pic_colour_max - pic_colour_min));
}
std::string Colour::getPicColours() const {
	size_t r_, g_, b_;
	getPicColours(r_, g_, b_);
	std::stringstream out;
	out << r_ << " " << g_ << " " << b_ << "\t";
	return out.str();
}




