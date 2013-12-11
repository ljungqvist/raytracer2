OBJS = chessplane.o colour.o csg.o cylinder.o filereading.o lamp.o lampsphere.o main.o material.o matrix.o picture.o picturedata.o plane.o rt_math.o simplething.o sphere.o spotlight.o tetrahedron.o thingplane.o torus.o vect.o world.o
CC = g++
# DEBUG = -std=c++0x
DEBUG = -std=c++0x -pedantic -Wall -Wextra -g -D_GLIBCXX_DEBUG
CFLAGS = $(DEBUG) -c 
LFLAGS = $(DEBUG)

raytracer : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o raytracer

chessplane.hh : thingplane.hh matrix.hh

chessplane.o : chessplane.cc chessplane.hh
	$(CC) $(CFLAGS) chessplane.cc

colour.o : colour.cc colour.hh
	$(CC) $(CFLAGS) colour.cc

csg.hh : simplething.hh

csg.o : csg.cc csg.hh
	$(CC) $(CFLAGS) csg.cc
	
cylinder.hh : plane.hh simplething.hh

cylinder.o : cylinder.cc cylinder.hh rt_math.hh
	$(CC) $(CFLAGS) cylinder.cc

filereading.hh : picture.hh

filereading.o : filereading.cc filereading.hh csg.hh cylinder.hh lamp.hh sphere.hh spotlight.hh tetrahedron.hh thingplane.hh torus.hh world.hh
	$(CC) $(CFLAGS) filereading.cc

lamp.hh : light.hh

lamp.o : lamp.cc lamp.hh lampsphere.hh world.hh 
	$(CC) $(CFLAGS) lamp.cc

lampsphere.hh : thing.hh

lampsphere.o : lampsphere.cc lampsphere.hh rt_math.hh
	$(CC) $(CFLAGS) lampsphere.cc

light.hh : struct.hh

material.hh : colour.hh

material.o : material.cc material.hh
	$(CC) $(CFLAGS) material.cc

matrix.hh : vect.hh

matrix.o : matrix.cc matrix.hh
	$(CC) $(CFLAGS) matrix.cc

main.o : main.cc filereading.hh world.hh
	$(CC) $(CFLAGS) main.cc

picture.hh : picturedata.hh struct.hh

picture.o : picture.cc picture.hh rt_math.hh world.hh
	$(CC) $(CFLAGS) picture.cc

picturedata.hh : colour.hh

picturedata.o : picturedata.cc picturedata.hh
	$(CC) $(CFLAGS) picturedata.cc

plane.hh : struct.hh

plane.o : plane.cc plane.hh
	$(CC) $(CFLAGS) plane.cc

rt_math.o : rt_math.cc rt_math.hh
	$(CC) $(CFLAGS) rt_math.cc

simplething.hh : thing.hh

simplething.o : simplething.cc simplething.hh
	$(CC) $(CFLAGS) simplething.cc

sphere.hh : simplething.hh

sphere.o : sphere.cc sphere.hh rt_math.hh
	$(CC) $(CFLAGS) sphere.cc

spotlight.hh : light.hh

spotlight.o : spotlight.cc spotlight.hh
	$(CC) $(CFLAGS) spotlight.cc

struct.hh : colour.hh vect.hh

tetrahedron.hh : plane.hh simplething.hh

tetrahedron.o : tetrahedron.cc tetrahedron.hh
	$(CC) $(CFLAGS) tetrahedron.cc

thing.hh : struct.hh material.hh

thingplane.hh : thing.hh plane.hh

thingplane.o : thingplane.cc thingplane.hh
	$(CC) $(CFLAGS) thingplane.cc

torus.hh : simplething.hh sphere.hh matrix.hh

torus.o : torus.cc torus.hh rt_math.hh
	$(CC) $(CFLAGS) torus.cc

vect.hh : material.hh

vect.o : vect.cc vect.hh
	$(CC) $(CFLAGS) vect.cc

world.hh : light.hh thing.hh

world.o : world.cc world.hh
	$(CC) $(CFLAGS) world.cc

clean:
	\rm *.o *~ raytracer


