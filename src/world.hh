#ifndef AALTO_AS_CPP_RAYTRACER11_WORLD_H_
#define AALTO_AS_CPP_RAYTRACER11_WORLD_H_

#include <list>

#include "light.hh"
#include "thing.hh"

/* The World class holds and handles all the information		
 * related to the scene.	The class is a singleton			
 */
class World {
	public:
		static World* Instance();
		void addThing(Thing* thing);
		void removeThing(Thing* thing);
		void addLight(Light* light);
		Colour sendRay(Ray& ray, Thing* thing, int num) const;
		Colour sendRay(Ray& ray, Thing* thing) const;
		Colour worldColour(Thing* thing, Vect& position, Vect& normal) const;
		Thing* getThing(Vect& position) const;
		void Release();
	private:
		static std::list<Thing*> things;
		static std::list<Light*> lights;
		static World* inst;
		World() {}
		World(const World&);
		World& operator=(const World&);
};

#endif	// AALTO_AS_CPP_RAYTRACER11_WORLD_H_

