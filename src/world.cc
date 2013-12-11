
#include "world.hh"

#include <cmath>
#include <thread>

std::list<Thing*> World::things;
std::list<Light*> World::lights;
World* World::inst = NULL;
static const int num_max = 20;

World* World::Instance() {
	if (!inst) inst = new World;
	return inst;
}
		
void World::addThing(Thing* thing) {
	things.push_back(thing);
}

void World::removeThing(Thing* thing){
	things.remove(thing);
	delete thing;
}

void World::addLight(Light* light) {
	lights.push_back(light);
	light->addToWorld();
}

Colour getShadowRay(Material::matInd index, Thing* thing, Vect& pos, Vect& n, int num) { 
	if (num >= 20) return Colour::black();
	if (index != Material::mZero)
		return index * World::Instance()->worldColour(thing, pos, n);
	else return Colour::black();
}

Colour getReflectionRay(Material::matInd index, Thing* thing, Vect& pos, Vect& n, Vect& direction, int num) {
	if (num >= 20) return Colour::black();
	if (index != Material::mZero) {
		Ray r;
		r.origin = pos;
		r.direction = direction.getReflection(n);
		return index * World::Instance()->sendRay(r, thing, num+1);
	}
	else return Colour::black();
}

Colour sendRefractionRay(Thing* thing, Ray& ray, int num) {
	if (num >= 20) return Colour::black();
	lu distance = thing->checkInnerRay(ray);
	Material mat = thing->getMaterial(ray.origin);
	Ray out_ray;
	out_ray.origin = ray.origin + ray.direction * distance / ray.direction.length();
	Vect n = thing->getNormal(out_ray.origin);
	out_ray.direction = ray.direction.getRefraction(mat.getRefractive_index(), 1, n);
	Colour ret_c;
	if (out_ray.direction.length() == 0) {
		out_ray.direction = ray.direction.getReflection(n);
		ret_c = sendRefractionRay(thing, out_ray, num+1);
	}
	else ret_c =  World::Instance()->sendRay(out_ray, thing, num+1);
	return ret_c * ((mat.getColour() * mat.getTranslusans()) ^ distance);
}

Colour getRefractionRay(Material::matInd index, Thing* thing, Vect& pos, Vect& n, Vect& direction, int num) {
	if (num >= num_max) return Colour::black();
	if (index != Material::mZero) {
		Ray r;
		r.origin = pos;
		r.direction = direction.getRefraction(1, thing->getMaterial(pos).getRefractive_index(), n);
		if (r.direction.length() == 0)
			return getReflectionRay(index, thing, pos, n, direction, num+1);
		return index * sendRefractionRay(thing, r, num+1);
	}
	return Colour::black();
}

Colour World::sendRay(Ray& ray, Thing* /*thing*/, int num) const {
	if (num >= num_max) return Colour::black();
	Thing* min_thing = NULL;
	lu min_lu = -1;
	for (std::list<Thing*>::iterator it = things.begin(); it != things.end(); ++it) {
		lu tmp_lu = (*it)->checkRay(ray, min_lu);
		if (tmp_lu > DELTA_LU and (min_lu < DELTA_LU or min_lu > tmp_lu)) {
			min_lu = tmp_lu;
			min_thing = *it;
		}
	}
	if (min_lu > DELTA_LU) {
		Vect pos = ray.origin + ray.direction.getUnitVect() * min_lu;
		Material mat = min_thing->getMaterial(pos);
		Vect n = min_thing->getNormal(pos);
		if (n == Vect(0,0,0))
			return min_thing->getColour(pos);
		return	getShadowRay(mat.getScattering(), min_thing, pos, n, num) +
				getReflectionRay(mat.getReflection(), min_thing, pos, n, ray.direction, num+1) +
				getRefractionRay(mat.getRefraction(), min_thing, pos, n, ray.direction, num+1);
	}
	else
		return Colour::black();
}
Colour World::sendRay(Ray& ray, Thing* thing) const {
	return this->sendRay(ray, thing, 0);
}

Colour World::worldColour(Thing* thing, Vect& pos, Vect& normal) const {
	Colour ret = Colour::black();
	for (std::list<Light*>::iterator it = lights.begin(); it != lights.end(); ++it) {
		bool in_shade = false;
		Ray ray;
		ray.direction = (*it)->getPosition() - pos;
		ray.origin = pos + ray.direction.getUnitVect() * DELTA_LU;
		lu coeff = ray.direction * normal;
		LightRay lray = (*it)->illumination(pos);
			ret += (0.1 * lray.colour) * thing->getColour(pos);
		if (coeff > 0) {
			lu l_dist = ray.direction.length() - 10 * DELTA_LU;
			Colour shadow = Colour(1,1,1);
			for (std::list<Thing*>::iterator itt = things.begin(); itt != things.end(); ++itt){
				lu t_dist = (*itt)->checkRay(ray);
				if (t_dist > 0 and t_dist < l_dist) {
					Ray inner_ray;
					inner_ray.origin = ray.origin + t_dist * ray.direction.getUnitVect();
					inner_ray.direction = ray.direction;
					Material mat = (*itt)->getMaterial(inner_ray.origin);
					Material::matInd rafraction = mat.getRefraction();
					if (rafraction == 0) {
						in_shade = true;
						break;
					}
					else {
						lu cut = (*itt)->checkInnerRay(inner_ray);
						shadow *=  (mat.getColour() * mat.getTranslusans()) ^ cut * rafraction;
					}
				}
			}
			if (!in_shade)
				ret += (0.9 * coeff / lray.ray.direction.length()) * lray.colour * thing->getColour(pos) * shadow;
		}
	}
	return ret;
}

Thing* World::getThing(Vect& position) const {
	std::list<Thing*>::iterator it;
	for (it = things.begin(); it != things.end(); ++it)
		if ((*it)->wraps(position)) break;
	if (it != things.end()) return NULL;
	return *it;
}

void World::Release() {	
	for (std::list<Thing*>::iterator it = things.begin(); it != things.end();) {
		delete *it++;
	}
	for (std::list<Light*>::iterator it = lights.begin(); it != lights.end();)
		delete *it++;
	things.clear();
	lights.clear();
	delete inst;
	inst = NULL;
}


