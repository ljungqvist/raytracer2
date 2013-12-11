
#include <fstream>
#include <iostream>
#include <string>

#include "filereading.hh"
#include "world.hh"

/*
g++ -std=c++0x -pedantic -Wextra -Wall -g -D_GLIBCXX_DEBUG -o filetester filereading_new.cc material.cc vect.cc colour.cc sphere.cc world.cc rt_math.cc simplething.cc csg.cc plane.cc lamp.cc lampsphere.cc picture.cc picturedata.cc test_hilkka.cc spotlight.cc tetrahedron.cc
*/

int main(int argc, char* argv[]) { 
	std::string scene_file, destination_file;
	if (argc >= 3) {
		scene_file = argv[1];
		destination_file = argv[2];
	} else if (argc == 2) {
		scene_file = argv[1];
		std::cout << "Please give the name of the picture: (ending with .ppm) " << std::endl;
		std::cin >> destination_file;
	} else {
		std::cout << "Please give the name of the scene file:" << std::endl;
		std::cin >> scene_file;
		std::cout << "Please give the name of the picture: (ending with .ppm) " << std::endl;
		std::cin >> destination_file;
	}
    std::ifstream file;
    file.open(scene_file);
    if (!file.good()) {
		std::cout << "\nScene file name not valid.\nPlease give a new scene file name.\n(\"quit\" to exit):" << std::endl;
		std::cin >> scene_file;
		if (scene_file == "quit") {
			World::Instance()->Release();
			return 0;
		}
    	file.open(scene_file);
    }
    Picture picture;
    try {
		picture = FileReading::read(file);
	} catch (FileReading::exception& e) {
		std::cerr << e << std::endl;
		file.close();
		World::Instance()->Release();
		return 0;
	}
	file.close();
	PictureData data = picture.capture();
	data.dataToPPM(destination_file);
	World::Instance()->Release();
	return 0;
}

