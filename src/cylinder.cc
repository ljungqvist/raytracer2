
#include "cylinder.hh"

#include <cmath>

// for testing
#include <iostream>

#include "rt_math.hh"

Cylinder::Cylinder(const Material mat, const Ray& axis_, const lu r_) :
		SimpleThing(mat), 
		axis(axis_), 
		r(r_), 
		plane1(-(axis_.direction), axis_.origin), 
		plane2(axis_.direction, axis_.origin + axis_.direction)  {
	axis.direction.normalize();
}

lu Cylinder::checkRay(Ray& ray, const lu /*max*/) {
	//return checkInnerRay(ray);
	// order of the planes in referense fo ray
	Plane* p1;
	Plane* p2;
	if (ray.direction * plane1.normal() < 0) { p1 = &plane1; p2 = &plane2; }
	else {p1 = &plane2; p2 = &plane1;}
		
	// behind secon plane
	if (p2->distance(ray.origin) > DELTA_LU) { return -1; }
	
	Ray ray_; //rays to work with (ray)
	ray_.direction = ray.direction.getUnitVect();
	ray_.origin = ray.origin;
	
	// ray starts inside pipe
	if (rtMath::distance(ray_.origin, axis) <= r) {
		lu dist = p1->crossing(ray);
		if (dist > 0 and rtMath::distance((ray_.origin + dist * ray_.direction), axis) <= r)
			return dist;
		return -1;
	}
	
	Vect axis_x_ray = axis.direction % ray_.direction;
	Vect plane_n = axis_x_ray.getUnitVect();
	lu distance = fabs(plane_n * (ray_.origin - axis.origin));
	if (distance <= r) {
		if (axis.direction == ray_.direction)
			return p1->distance(ray.origin);
		Vect n_b = (axis.direction % plane_n).getUnitVect();
		lu o_dist_at_b = n_b * (ray_.origin - axis.origin);
		if (o_dist_at_b < 0) return -1; // ray behind pipe.
		double k = axis_x_ray.length();
		double a(pow(k, 2)); 
		double b(-2.0 * k * o_dist_at_b);
		double c(pow(o_dist_at_b, 2) - pow(r, 2) + pow(distance, 2));
		double sq_discr(sqrt(pow(b, 2) - 4 * a * c));
		double x_m = (-b - sq_discr) / (2 * a);
		double x_p = (-b + sq_discr) / (2 * a);
		Vect x_m_ = ray_.origin + ray_.direction * x_m;
		Vect x_p_ = ray_.origin + ray_.direction * x_p;
		if (p1->distance(x_m_) >= 0.0) {
			if (p1->distance(x_p_) < 0.0)
				return p1->crossing(ray_);
			return -1;
		} else if (p2->distance(x_m_) <= 0.0) {
			return x_m;
		}
	}
	return -1;
}

lu Cylinder::checkInnerRay(Ray& ray) const {
	// order of the planes in referense fo ray
	const Plane* p1;
	const Plane* p2;
	if (ray.direction * plane1.normal() < 0) { p1 = &plane1; p2 = &plane2; }
	else {p1 = &plane2; p2 = &plane1; }
		
	// behind secon plane
	if (p2->distance(ray.origin) > DELTA_LU) return -1;
	
	// ray starts inside pipe
	if (rtMath::distance(ray.origin, axis) <= r) {
		lu dist = p1->crossing(ray);
		if (dist > DELTA_LU and rtMath::distance(ray.origin + dist * ray.direction, axis) > r)
			return -1;
	}
	
	Ray ray_; //rays to work with (ray)
	ray_.direction = ray.direction.getUnitVect();
	ray_.origin = ray.origin;
	
	Vect axis_x_ray = axis.direction % ray_.direction;
	Vect plane_n = axis_x_ray.getUnitVect();
	lu distance = fabs(plane_n * (ray_.origin - axis.origin));
	if (distance <= r) {
		if (axis.direction == ray_.direction)
			return -(p2->distance(ray.origin));
		Vect n_b = (axis.direction % plane_n).getUnitVect();
		lu o_dist_at_b = n_b * (ray_.origin - axis.origin);
		//if (o_dist_at_b < 0) return -1;
		double k = axis_x_ray.length();
		double a(pow(k, 2)); 
		double b(-2.0 * k * o_dist_at_b);
		double c(pow(o_dist_at_b, 2) - pow(r, 2) + pow(distance, 2));
		double sq_discr(sqrt(pow(b, 2) - 4 * a * c));
		double x_m = (-b - sq_discr) / (2 * a);
		double x_p = (-b + sq_discr) / (2 * a);
		Vect x_m_ = ray_.origin + ray_.direction * x_m;
		Vect x_p_ = ray_.origin + ray_.direction * x_p;
		// ray starts inside pipe
		if (rtMath::distance(ray_.origin, axis) <= r) {
			lu dist = p2->crossing(ray);
			if (rtMath::distance(ray_.origin + dist * ray_.direction, axis) <= r)
				return dist;
			return x_p;
		} else if (p1->distance(x_m_) >= 0.0) {
			if (p1->distance(x_p_) < 0.0)
				return x_p;
			return -1;
		} else if (p2->distance(x_m_) <= 0.0) {
			if (p2->distance(x_p_) <= 0.0)
				return x_p;
			return p2->crossing(ray_);
		}
	}
	return -1;
}

Vect Cylinder::getNormal(const Vect& position) const {
	if (std::fabs(plane1.distance(position)) <= DELTA_LU)
		return plane1.normal();
	if (std::fabs(plane2.distance(position)) <= DELTA_LU)
		return plane2.normal();
	Vect o_p = position - axis.origin;
	Vect n_0 = o_p * axis.direction * axis.direction;
	Vect ret = (o_p - n_0).getUnitVect();
	/*std::cout << "getting pipe normal\n   " << 
			position.getX() << " " << position.getY() << " " << position.getZ() << "\n    " <<
			ret.getX() << " " << ret.getY() << " " << ret.getZ() << "\n";*/
	return ret;
}
bool Cylinder::wraps(const Vect& position) const {
	return	(plane1.distance(position) <= -DELTA_LU) and
			(plane2.distance(position) <= -DELTA_LU) and
			(rtMath::distance(position, axis) <= r - DELTA_LU);
}
bool Cylinder::onSurface(const Vect& position) const {
	lu dist;
	dist = plane1.distance(position);
	if ((dist < DELTA_LU) and (dist > -DELTA_LU)) return true;
	dist = plane2.distance(position);
	if ((dist < DELTA_LU) and (dist > -DELTA_LU)) return true;
	dist = rtMath::distance(position, axis);
	if ((dist < r + DELTA_LU) and (dist > r - DELTA_LU)) return true;
	return false;
}




