
#include "thingplane.hh"

#include <cmath>

#include "rt_math.hh"

ThingPlane::ThingPlane(const Material mat, const Plane pl) : material(mat), plane(pl) {}
ThingPlane::ThingPlane(const Material mat, const Vect v[4]) : material(mat), plane(v[0], v[1], v[2], v[3], false) {}
lu ThingPlane::checkRay(Ray& ray, const lu /*max*/) { return plane.crossing(ray); }
lu ThingPlane::checkInnerRay(Ray& ray) const { return plane.crossing(ray); }
Material ThingPlane::getMaterial(const Ray& /*ray*/) const { return material; }
Material ThingPlane::getMaterial(const Vect& /*position*/) const { return material; }
Colour ThingPlane::getColour(Ray& /*ray*/) { return material.getColour(); }
Colour ThingPlane::getColour(Vect& /*position*/) { return material.getColour(); }
Vect ThingPlane::getNormal(const Vect& /*position*/) const { return plane.normal(); }
bool ThingPlane::wraps(const Vect& /*position*/) const { return false; }
bool ThingPlane::onSurface(const Vect& position) const {
	lu dist = plane.distance(position);
	return (dist >= -DELTA_LU) and (dist <= DELTA_LU);
}

