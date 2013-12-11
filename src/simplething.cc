
#include "simplething.hh"

SimpleThing::SimpleThing(const Material mat) : material(mat) {}

Material SimpleThing::getMaterial(const Ray& /*ray*/) const {
	return material;
}

Material SimpleThing::getMaterial(const Vect& /*position*/) const {
	return material;
}

Colour SimpleThing::getColour(Ray& /*ray*/) {
	return material.getColour();
}

Colour SimpleThing::getColour(Vect& /*position*/) {
	return material.getColour();
}
