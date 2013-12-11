#include "picture.hh"

#include <cmath>
#include <iostream>

#include "rt_math.hh"
#include "structs.hh"
#include "world.hh"

Picture::Picture() {}

Picture::Picture(Camera& camera) : camera(camera)
{
	picture = PictureData();
}

Picture::Picture(size_t x, size_t y, Camera& camera) : camera(camera) {
	picture = PictureData(x, y);
}

double getAngle(size_t i, size_t resolution, double maxAngle, char projection) {
	
	if (projection == 1)
		return (maxAngle / 2  - maxAngle/(resolution - 1) * i );
	
	return (maxAngle / 2);
	
}

PictureData Picture::capture() {

	//Calculating unit vectors forward, up and down from camera
	Vect cameraFrontUnit = (camera.centre - camera.position).getUnitVect();
	Vect vUp = camera.up - camera.centre;
	Vect cameraUpUnit = (vUp - (vUp*cameraFrontUnit)*cameraFrontUnit).getUnitVect();
	Vect cameraSideUnit = (cameraFrontUnit % cameraUpUnit).getUnitVect();
	//Vect positionVector = camera.position;
	
	size_t res_x = picture.getRes_x();
	size_t res_y = picture.getRes_y();
	
	std::cout << std::endl;
	
	//sending ray through every pixel in picturedata
	for (size_t i = 0; i < res_x; i++) {
		std::cout << ((float)i / (float)res_x)*100.f << "%" << std::endl;
		
		double cangle_x = getAngle(i, res_x, camera.angle_x, camera.projection);
		double lenghtSide = tan(cangle_x*3.14159 / 180.0);
		if (camera.projection != 1)
			lenghtSide = (lenghtSide / ((double)res_x / 2.0)) * ((double)res_x / 2.0 - (double)i); 
		Vect vector_Side = cameraSideUnit * lenghtSide;
		
		for (size_t j = 0; j < res_y; j++) {
			double cangle_y = getAngle(j, res_y, camera.angle_y, camera.projection);
			double lengthUp = tan(cangle_y*3.14159 / 180.0);
			if (camera.projection != 1) {
				lengthUp = (lengthUp / ((double)res_y / 2.0)) * ((double)res_y / 2.0 - (double)j); 
				
			}
			Vect vector_Up = cameraUpUnit * lengthUp;
			//Calculating resultant vector of the three components
			Vect result = cameraFrontUnit + vector_Up + vector_Side;
			Ray ray;
			ray.origin = camera.position;
			ray.direction = result;
			picture[i][j] = World::Instance()->sendRay(ray, NULL);
		}
	}
	return picture;

}

PictureData Picture::getPicture() {return picture;}



