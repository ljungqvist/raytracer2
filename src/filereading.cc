
#include "filereading.hh"

#include "chessplane.hh"
#include "csg.hh"
#include "cylinder.hh"
#include "lamp.hh"
#include "light.hh"
#include "sphere.hh"
#include "spotlight.hh"
#include "tetrahedron.hh"
#include "thingplane.hh"
#include "torus.hh"
#include "world.hh"

Thing* FindThing(std::istream& file, std::string word);
void FindLight(std::istream& file, std::string& word);
Material FindMaterial(std::istream& file);
Thing* FindSphere(std::istream& file);
Thing* FindCSG(std::istream& file);
Thing* FindTetrahedron(std::istream& file);
void FindCamera(std::istream& file, Camera& camera);
void FindLamp(std::istream& file);
void FindSpotlight(std::istream& file);

Material FindMaterial(std::istream& file) {
	std::string word, comment;
	Material::matInd reflection=0.0,
					 refraction=0.0,
					 scattering=1.0,
					 sum;
	Material::tanslInd translusans=1.0;
	Material::reflInd refractive_index=1.0;
	Colour::colInd r = 0.5, g = 0.5, b = 0.5;
	
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) {
		if (word.compare("reflection") == 0) {
			if (!(file >> reflection)) throw FileReading::exception(7, "reflection"); 
		} else if (word.compare("refraction") == 0) {
			if (!(file >> refraction)) throw FileReading::exception(7, "refraction");
		} else if (word.compare("scattering") == 0) {
			if (!(file >> scattering)) throw FileReading::exception(7, "scattering");
		} else if (word.compare("translusans") == 0) {
			if (!(file >> translusans)) throw FileReading::exception(7, "translusans");
		} else if (word.compare("refractive_index") == 0) {
			if (!(file >> refractive_index)) throw FileReading::exception(7, "refractive_index");
		} else if (word.compare("colour") == 0) {
			if (!(file >> r >> g >> b)) throw FileReading::exception(8);		
		} else if (word == FileReading::COMMENT){
				 getline(file, comment); // för att hoppa till en ny linje
		} else throw FileReading::exception(9, word);
		file >> word;
	}
	Colour colour(r,g,b);
	
	// Setting the material values refl, refr and scattering to sum up to 1:
	sum = reflection + refraction + scattering;
	reflection /= sum;
	refraction /= sum;
	scattering /= sum;
	sum = reflection + refraction + scattering;
	
	if (translusans > 1.0) translusans = 1.0;
	if (translusans < 0.0) translusans = 0.0;
	if (refractive_index < 1.0) refractive_index = 1.0;
	
	Material material(reflection, refraction, scattering, translusans, refractive_index, colour);
	return material;
}

Thing* FindSphere(std::istream& file) {
	std::string word, comment;
	lu x = 1, y = 1, z = 1, radius = 1;
	Material material; // constructor gives default values
	
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) {
		if (word.compare("material") == 0) {
			try { material = FindMaterial(file); }
			catch (FileReading::exception& e) { throw; }
		} else if (word.compare("position") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(4);		
		} else if (word.compare("radius") == 0) {
			if (!(file >> radius)) throw FileReading::exception(5);		
		} else if (word == FileReading::COMMENT){
				 getline(file, comment); // för att hoppa till en ny linje (fungerar!)
		} else throw FileReading::exception(6, word);
		file >> word;
	}
	Thing* sphere = new Sphere(material, Vect(x,y,z), radius);
	return sphere;
}

Thing* FindTetrahedron(std::istream& file) {
	std::string word, comment;
	lu x = 1, y = 1, z = 1;
	Material material; // constructor gives default values
	Vect vect1, vect2, vect3, vect4;
	
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) {
		if (word.compare("material") == 0) {
			try { material = FindMaterial(file); }
			catch (FileReading::exception& e) { throw; }
		} else if (word.compare("vect1") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(16, "vect1");
			vect1 = Vect(x,y,z);		
		} else if (word.compare("vect2") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(16, "vect2");
			vect2 = Vect(x,y,z);		
		} else if (word.compare("vect3") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(16, "vect3");
			vect3 = Vect(x,y,z);		
		} else if (word.compare("vect4") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(16, "vect4");
			vect4 = Vect(x,y,z);		
		} else if (word == FileReading::COMMENT){
				 getline(file, comment); // för att hoppa till en ny linje
		} else throw FileReading::exception(17, word);
		file >> word;
	}
	
	Thing* tetra = new Tetrahedron(material, vect1, vect2, vect3, vect4);
	return tetra;
}

Thing* FindCylinder(std::istream& file) {
	std::string word, comment;
	lu x1(0), y1(0), z1(0), x2(1), y2(1), z2(1), r(1);
	Material material; // constructor gives default values
	
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) {
		if (word.compare("material") == 0) {
			try { material = FindMaterial(file); }
			catch (FileReading::exception& e) { throw; }
		} else if (word.compare("end_1") == 0) {
			if (!(file >> x1 >> y1 >> z1)) throw FileReading::exception(26, "end_1");
		} else if (word.compare("end_2") == 0) {
			if (!(file >> x2 >> y2 >> z2)) throw FileReading::exception(26, "end_2");			
		} else if (word.compare("radius") == 0) {
			if (!(file >> r)) throw FileReading::exception(26, "radius");		
		} else if (word == FileReading::COMMENT){
				 getline(file, comment); // för att hoppa till en ny linje (fungerar!)
		} else throw FileReading::exception(27, word);
		file >> word;
	}
	Ray ray;
	ray.origin = Vect(x1, y1, z1);
	ray.direction = Vect(x2, y2, z2) - ray.origin;
	if (r < 0) r = -r;
	return (Thing*)(new Cylinder(material, ray, r));
}

Thing* FindTorus(std::istream& file) {
	std::string word, comment;
	lu x1(0), y1(0), z1(0), x2(0), y2(0), z2(1), r(2), R(1);
	Material material; // constructor gives default values
	
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) {
		if (word.compare("material") == 0) {
			try { material = FindMaterial(file); }
			catch (FileReading::exception& e) { throw; }
		} else if (word.compare("position") == 0) {
			if (!(file >> x1 >> y1 >> z1)) throw FileReading::exception(26, "position");
		} else if (word.compare("direction") == 0) {
			if (!(file >> x2 >> y2 >> z2)) throw FileReading::exception(26, "direction");			
		} else if (word.compare("minor") == 0) {
			if (!(file >> r)) throw FileReading::exception(26, "minor");			
		} else if (word.compare("major") == 0) {
			if (!(file >> R)) throw FileReading::exception(26, "major");	
		} else if (word == FileReading::COMMENT){
				 getline(file, comment); // för att hoppa till en ny linje (fungerar!)
		} else throw FileReading::exception(27, word);
		file >> word;
	}
	Ray ray;
	ray.origin = Vect(x1, y1, z1);
	ray.direction = Vect(x2, y2, z2);
	if (r < 0) r = -r;
	if (R < 0) R = -R;
	return (Thing*)(new Torus(material, ray, R, r));
}

Thing* FindCSG(std::istream& file) {
	std::string word, comment;
	SimpleThing* left, *right;
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	Material material; // constructor gives default values
	char type = 'U'; // default value
	file >> word;
	while (word != FileReading::END) { // goes through the whole CSG section
		if (word.compare("//") == 0){
			getline(file, comment); // för att hoppa till en ny linje
		} else if (word.compare("right") == 0) {
			file >> word; // this should be the "{" sign
			if (word != FileReading::BEGIN) throw FileReading::exception(1);
			file >> word;
			try { right = (SimpleThing*) FindThing(file, word); }
			catch (FileReading::exception& e) { throw; }
			file >> word; // this should be the "}" sign
			while (word == FileReading::COMMENT) {
				getline(file, comment);
				file >> word;
			}
			if (word != FileReading::END) throw FileReading::exception(10);
		} else if (word.compare("material") == 0) {
			try { material = FindMaterial(file); }
			catch (FileReading::exception& e) { throw; }	
		} else if (word.compare("type") == 0) {
			if (!(file >> type)) throw FileReading::exception(11, "type");
		} else if (word.compare("left") == 0) {
			file >> word; // this should be the "{" sign
			if (word != FileReading::BEGIN) throw FileReading::exception(1);
			file >> word;
			try { left = (SimpleThing*) FindThing(file, word); }
			catch (FileReading::exception& e) { throw; }
			file >> word; // this should be the "}" sign
			while (word == FileReading::COMMENT) {
				getline(file, comment);
				file >> word;
			}
			if (word != FileReading::END) throw FileReading::exception(10);
		} else throw FileReading::exception(12, word);
		file >> word;
	}
	Thing* csg = new CSG(material, left, type, right);
	return csg;
}

Thing* FindThing(std::istream& file, std::string word) {
	std::string comment;
	Thing* thing;
	if (word.compare("sphere") == 0) {
		try { thing = FindSphere(file); }
		catch (FileReading::exception& e) { throw; }
	} else if (word.compare("constructive_solid_geometry") == 0) {
		try { thing = FindCSG(file); }
		catch (FileReading::exception& e) { throw; }
	} else if (word.compare("tetrahedron") == 0) {
		try { thing = FindTetrahedron(file); }
		catch (FileReading::exception& e) { throw; }
	} else if (word.compare("cylinder") == 0) {
		try { thing = FindCylinder(file); }
		catch (FileReading::exception& e) { throw; }
	} else if (word.compare("torus") == 0) {
		try { thing = FindTorus(file); }
		catch (FileReading::exception& e) { throw; }
	} else if (word == FileReading::COMMENT){
		getline(file, comment); // för att hoppa till en ny linje
	} else throw FileReading::exception(3, word);
	return thing;
}

void FindSpotlight(std::istream& file) {
	std::string word, comment;
	lu x=1,y=1,z=1;
	Colour::colInd r=0.5,g=0.5,b=0.5;
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) { // goes through the whole spotlight section
		if (word.compare("position") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(23, "position");
		} else if (word.compare("colour") == 0) {
			if (!(file >> r >> g >> b)) throw FileReading::exception(23, "colour");
		} else if (word == FileReading::COMMENT){
			getline(file, comment); // för att hoppa till en ny linje
		} else throw FileReading::exception(24, word);
		file >> word;
	}
	Light* spotlight = new SpotLight(Vect(x,y,z), Colour(r,g,b));
	World::Instance()->addLight(spotlight);
}

void FindLamp(std::istream& file) {
	std::string word, comment;
	lu x=1,y=1,z=1, size=1;
	Colour::colInd r=0.5,g=0.5,b=0.5;
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) { // goes through the Lamp section
		if (word.compare("position") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(21, "position");
		} else if (word.compare("colour") == 0) {
			if (!(file >> r >> g >> b)) throw FileReading::exception(21, "colour");
		} else if (word.compare("size") == 0) {
			if (!(file >> size)) throw FileReading::exception(21, "size");
		} else if (word == FileReading::COMMENT){
			getline(file, comment); // för att hoppa till en ny linje
		} else throw FileReading::exception(22, word);
		file >> word;
	}
	Light* lamp = new Lamp(Vect(x,y,z), Colour(r,g,b), size);
	World::Instance()->addLight(lamp);
}

void FindLight(std::istream& file, std::string& word) {
	std::string comment;
	if (word.compare("spotlight") == 0) {
		try { FindSpotlight(file); }
		catch (FileReading::exception& e) { throw; }
	} else if (word.compare("lamp") == 0) {
		try { FindLamp(file); }
		catch (FileReading::exception& e) { throw; }
	} else if (word == FileReading::COMMENT){
		getline(file, comment); // för att hoppa till en ny linje
	} else throw FileReading::exception(18, word);
}

void FindCamera(std::istream& file, Camera& camera) {
	std::string word, comment;
	lu x,y,z;
	Vect position, centre, up;
	char projection;
	float angle_x, angle_y;
	
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) { // goes through the whole Light section
		if (word.compare("position") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(19, "position");
			position = Vect(x,y,z);
			camera.position = position;
		} else if (word.compare("centre") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(19, "centre");
			centre = Vect(x,y,z);
			camera.centre = centre;
		} else if (word.compare("up") == 0) {
			if (!(file >> x >> y >> z)) throw FileReading::exception(19, "up");
			up = Vect(x,y,z);
			camera.up = up;
		} else if (word.compare("projection") == 0) {
			if (!(file >> projection)) throw FileReading::exception(19, "projection");
			camera.projection = projection;
		} else if (word.compare("angle_x") == 0) {
			if (!(file >> angle_x)) throw FileReading::exception(19, "angle_x");
			camera.angle_x = angle_x;
		} else if (word.compare("angle_y") == 0) {
			if (!(file >> angle_y)) throw FileReading::exception(19, "angle_y");
			camera.angle_y = angle_y;
		} else if (word == FileReading::COMMENT){
			getline(file, comment); // för att hoppa till en ny linje
		} else throw FileReading::exception(20, word);
		file >> word;
	}
}

Thing* FindPlane(std::istream& file) {
	std::string word, comment;
	int i;
	lu x[4] = {0, 1, 0, 0}, y[4] = {0, 0, 1, 0}, z[4] = {0, 0, 0, 1};
	Material material; // constructor gives default values
	
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) {
		if (word == FileReading::COMMENT) {
			getline(file, comment); // för att hoppa till en ny linje (fungerar!)
		} else if (word.compare("material") == 0) {
			try { material = FindMaterial(file); }
			catch (FileReading::exception& e) { throw; }		
		} else if (word.compare("point") == 0) {
			if (!(file >> i) or i < 1 or i > 4) throw FileReading::exception(29, "point");
			if (!(file >> x[i-1] >> y[i-1] >> z[i-1])) throw FileReading::exception(29, "point");
		} else throw FileReading::exception(30, word);
		file >> word;
	}
	Vect v[4];
	for (i = 0; i < 4; ++i) v[i] = Vect(x[i], y[i], z[i]);
	return new ThingPlane(material, v);
}

Thing* FindChessPlane(std::istream& file) {
	std::string word, comment;
	int i;
	lu x[4] = {0, 1, 0, 0}, y[4] = {0, 0, 1, 0}, z[4] = {0, 0, 0, 1};
	Material material1; // constructor gives default values
	Material material2; // constructor gives default values
	
	file >> word; // this should be "{"
	if (word != FileReading::BEGIN) throw FileReading::exception(1);
	file >> word;
	while (word != FileReading::END) {
		if (word == FileReading::COMMENT) {
			getline(file, comment); // för att hoppa till en ny linje (fungerar!)
		} else if (word.compare("material") == 0) {
			if (!(file >> i) or i < 1 or i > 2) throw FileReading::exception(31, "point");
			if (i == 1) {
				try { material1 = FindMaterial(file); }
				catch (FileReading::exception& e) { throw; }	
			} else {	
				try { material2 = FindMaterial(file); }
				catch (FileReading::exception& e) { throw; }	
			}
		} else if (word.compare("point") == 0) {
			if (!(file >> i) or i < 1 or i > 4) throw FileReading::exception(31, "point");
			if (!(file >> x[i-1] >> y[i-1] >> z[i-1])) throw FileReading::exception(31, "point");
		} else throw FileReading::exception(32, word);
		file >> word;
	}
	Vect v[4];
	for (i = 0; i < 4; ++i) v[i] = Vect(x[i], y[i], z[i]);
	return new ChessPlane(material1, material2, v);
}

Thing* FindSpecialThing(std::istream& file, std::string word) {
	std::string comment;
	Thing* thing;
	if (word == FileReading::COMMENT) {
		getline(file, comment); // för att hoppa till en ny linje
	} else if (word.compare("plane") == 0) {
		try { thing = FindPlane(file); }
		catch (FileReading::exception& e) { throw; }
	} else if (word.compare("chess_plane") == 0) {
		try { thing = FindChessPlane(file); }
		catch (FileReading::exception& e) { throw; }
	} else throw FileReading::exception(28, word);
	return thing;
}

Picture FileReading::read(std::istream& file) {
	std::string comment, word, sign;
	/*file.open (filename, std::ios::out);*/
	Thing* thing;
	Plane plane;
	Camera camera;
	size_t x_max, y_max;
	bool end_found = false;
	
	while (!file.eof()) {
		file >> word;
		if (word == FileReading::COMMENT) {
			getline(file, comment);
		} else if (word.compare("thing") == 0) {
			file >> word; // this is the "{" sign or "//".
			while (word == FileReading::COMMENT) {
				getline(file, comment);
				file >> word; // this is the "{" sign
			}
			if (word != FileReading::BEGIN) throw FileReading::exception(1);
			file >> word;
			while (word != FileReading::END) { // för att gå igenom alla thingina som deklareras
				if (word == FileReading::COMMENT) {
					getline(file, comment); // för att hoppa till en ny linje
				} else {
					try { thing = FindThing(file, word); }
					catch (FileReading::exception& e) { throw; }
					World::Instance()->addThing(thing);
				} 
				file >> word;
			}
		} else if (word.compare("special_thing") == 0) { // things whict aren't SimpleThing
			file >> word; // this is the "{" sign or "//".
			while (word == FileReading::COMMENT) {
				getline(file, comment);
				file >> word; // this is the "{" sign
			}
			if (word != FileReading::BEGIN) throw FileReading::exception(1);
			file >> word;
			while (word != FileReading::END) { // för att gå igenom alla thingina som deklareras
				if (word == FileReading::COMMENT) {
					getline(file, comment); // för att hoppa till en ny linje
				} else {
					try { thing = FindSpecialThing(file, word); }
					catch (FileReading::exception& e) { throw; }
					World::Instance()->addThing(thing);
				} 
				file >> word;
			}
		} else if (word.compare("light") == 0) {
			file >> word; // this is the "{" sign or "//".
			while (word == FileReading::COMMENT) {
				getline(file, comment);
				file >> word; // this is the "{" sign
			}
			if (word != FileReading::BEGIN) throw FileReading::exception(1);
			file >> word;
			while (word != FileReading::END) {
				if (word == FileReading::COMMENT){
					getline(file, comment); // för att hoppa till en ny linje
				} else {
					try { FindLight(file, word); }
					catch (FileReading::exception& e) { throw; }
				}
				file >> word;
			}
		} else if (word.compare("camera") == 0) {
			try { FindCamera(file, camera); }
			catch (FileReading::exception& e) { throw; }
		} else if (word.compare("picture_size") == 0) {
			file >> word; // this should be the "{" sign
			if (word != FileReading::BEGIN) throw FileReading::exception(1);
			file >> word;
			while (word != FileReading::END) {
				if (word == FileReading::COMMENT) {
					getline(file, comment);
				} else if (word == "x_max") {
					if (!(file >> x_max)) throw FileReading::exception(14, "x_max");
				} else if (word == "y_max") {
					if (!(file >> y_max)) throw FileReading::exception(14, "y_max");
				} else throw FileReading::exception(15, word);
				file >> word; 
			}
		} else if (word == "end") {
			end_found = true;
			break;
		} else throw FileReading::exception(13, word);
	}
	
	if (!end_found) FileReading::exception(25);

	Picture picture(x_max, y_max, camera);
	return picture;
}


FileReading::exception::exception(int num) : number(num), param("") {}
FileReading::exception::exception(int num, std::string str) : number(num), param(str) {}
int FileReading::exception::getNumber() { return number; }
std::string FileReading::exception::getMessage() {
	std::string ret;
	switch (number) {
		case 1: ret = "Expected '{'"; break;
		case 2: ret = "Expected number before declaration '" + param + "'."; break;
		case 3: ret = "thing '" + param + "' not recognised."; break;
		case 4: ret = "Unreadable position parameters."; break;
		case 5: ret = "Unreadable radius parameter."; break;
		case 6: ret = "sphere parameter '" + param + "' not recognised."; break;
		case 7: ret = "Unreadable material parameter '" + param + "'."; break;
		case 8: ret = "Unreadable colour parameter '" + param + "'."; break;
		case 9: ret = "material parameter '" + param + "' not recognised."; break;
		case 10: ret = "Expected '}'"; break;
		case 11: ret = "Unreadable constructive_solid_geometry parameter '" + param + "'."; break;
		case 12: ret = "constructive_solid_geometry parameter '" + param + "' not recognised."; break;
		case 13: ret = "Unknown command '" + param + "'."; break;
		case 14: ret = "Unreadable picture_size parameter '" + param + "'."; break;
		case 15: ret = "picture_size parameter '" + param + "' not recognised."; break;
		case 16: ret = "Unreadable tetrahedron parameter '" + param + "'."; break;
		case 17: ret = "tetrahedron parameter '" + param + "' not recognised."; break;
		case 18: ret = "light parameter '" + param + "' not recognised."; break;
		case 19: ret = "Unreadable camera parameter '" + param + "'."; break;
		case 20: ret = "camera parameter '" + param + "' not recognised."; break;
		case 21: ret = "Unreadable lamp parameter '" + param + "'."; break;
		case 22: ret = "lamp parameter '" + param + "' not recognised."; break;
		case 23: ret = "Unreadable spotlight parameter '" + param + "'."; break;
		case 24: ret = "spotlight parameter '" + param + "' not recognised."; break;
		case 25: ret = "'end' not found."; break;
		case 26: ret = "Unreadable cylinder parameter '" + param + "'."; break;
		case 27: ret = "cylinder parameter '" + param + "' not recognised."; break;
		case 28: ret = "special_thing '" + param + "' not recognised."; break;
		case 29: ret = "Unreadable plane parameter '" + param + "'."; break;
		case 30: ret = "plane parameter '" + param + "' not recognised."; break;
		case 31: ret = "Unreadable chess_plane parameter '" + param + "'."; break;
		case 32: ret = "chess_plane parameter '" + param + "' not recognised."; break;
		default: ret = "Random error ('" + param + "')."; break;
	}
	return ret;
}

std::ostream& operator << (std::ostream& os, FileReading::exception& ob) {
	return os << "Scene file reading error #" << ob.getNumber() << ": " << ob.getMessage();
}





