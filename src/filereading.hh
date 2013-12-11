#ifndef AALTO_AS_CPP_RAYTRACER11_FILEREADING_H_
#define AALTO_AS_CPP_RAYTRACER11_FILEREADING_H_

#include "picture.hh"

class Material;
class Colour;

namespace FileReading {
	// ändrad så att den returnerar en Picture
	Picture read(std::istream& file);
	
	const std::string BEGIN = "{";
	const std::string END = "}";
	const std::string COMMENT = "//";
	
	class exception {
		public:
			exception(int);
			exception(int, std::string);
			~exception() {}
			int getNumber();
			std::string getMessage();
		private:
			exception();
			exception& operator = (exception&);
			
			int number;
			std::string param;
	};
}

std::ostream& operator << (std::ostream& os, FileReading::exception& ob);

#endif
