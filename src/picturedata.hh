#ifndef AALTO_AS_CPP_RAYTRACER11_PICTUREDATA_H_
#define AALTO_AS_CPP_RAYTRACER11_PICTUREDATA_H_

#include <vector>
#include <string>

#include "colour.hh"

class PictureData {
	public:
		~PictureData();
		PictureData();
		PictureData(size_t x, size_t y);
		std::vector<Colour>& operator[] (size_t ind);
		void dataToPPM(std::string file);
		size_t getRes_x();
		size_t getRes_y();
		
	private:
		size_t res_x;
		size_t res_y;
		std::vector<std::vector<Colour>> data;
};

#endif	// AALTO_AS_CPP_RAYTRACER11_PICTUREDATA_H_
