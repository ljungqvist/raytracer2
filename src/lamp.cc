
#include "lamp.hh"

#include "lampsphere.hh"
#include "world.hh"

Lamp::Lamp(const Vect& pos, const Colour col, lu s) 
		: position(pos), colour(col), size(s) {}
LightRay Lamp::illumination(Vect& pos) const {
	LightRay lray;
	lray.ray.origin = pos;
	lray.ray.direction = position - pos;
	lu ray_len = lray.ray.direction.length();
	lray.colour = (colour / (ray_len * ray_len));
	return lray;
}
Vect Lamp::getPosition() { return position; }

void Lamp::addToWorld() {
	Thing* lamp = new LampSphere(colour, position, size);
	World::Instance()->addThing(lamp);
}

