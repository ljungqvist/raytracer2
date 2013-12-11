
#include "spotlight.hh"

SpotLight::SpotLight(const Vect& pos, const Colour col) : position(pos), colour(col) {}
LightRay SpotLight::illumination(Vect& pos) const {
	LightRay lray;
	lray.ray.origin = pos;
	lray.ray.direction = position - pos;
	lu ray_len = lray.ray.direction.length();
	lray.colour = (colour / (ray_len * ray_len));
	return lray;
}
Vect SpotLight::getPosition() { return position; }
void SpotLight::addToWorld() {}
