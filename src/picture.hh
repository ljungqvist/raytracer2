#ifndef AALTO_AS_CPP_RAYTRACER11_PICTURE_H_
#define AALTO_AS_CPP_RAYTRACER11_PICTURE_H_

#include "picturedata.hh"
#include "structs.hh"

class Picture
{
	public:
		Picture();
		Picture(Camera& camera);
		Picture(size_t x, size_t y, Camera& camera);
		PictureData capture();
		PictureData getPicture();
	private:
		Camera camera;
		PictureData picture;
};

//double getAngle(size_t i, size_t resolution, double maxAngle);

#endif	// AALTO_AS_CPP_RAYTRACER11_PICTURE_H_
