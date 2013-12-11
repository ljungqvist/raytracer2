
#include "picturedata.hh"

#include <iostream>
#include <fstream>
#include <cmath>

PictureData::~PictureData() { }

PictureData::PictureData() : res_x(300), 
		res_y(400), 
		data(300, std::vector<Colour>(400, Colour::black())) { }

PictureData::PictureData(const size_t x, const size_t y) : 
		res_x(x), 
		res_y(y), 
		data(x, std::vector<Colour>(y, Colour::black())) { }

std::vector<Colour>& PictureData::operator[] (const size_t ind) { return data[ind]; }


// Annis ändringar
size_t PictureData::getRes_x() {return res_x;}

size_t PictureData::getRes_y() {return res_y;}
// hit ända

void PictureData::dataToPPM(std::string file_name) {
	Colour::setPicColourLimits(0, 255);
	std::ofstream pic_file;
	pic_file.open (file_name);
	pic_file 
			<< "P3" << std::endl
			<< "# file '" << file_name << "'." << std::endl
			<< "# created with raytracer 2011!!!" << std::endl
			<< res_x << " " << res_y << std::endl
			<< "255" << std::endl;
	for (size_t j = 0; j < res_y; ++j) {
		for (size_t i = 0; i < res_x; ++i)
			pic_file << data[i][j].getPicColours();

		pic_file << std::endl;
	}
	pic_file.close();
}
