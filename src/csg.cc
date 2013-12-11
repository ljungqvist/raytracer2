
#include "csg.hh"

// for testing
#include <iostream>

CSG::CSG(Material mat) : SimpleThing(mat), left(NULL), right(NULL), binOp('U') {}
CSG::CSG(Material mat, SimpleThing* l, char b, SimpleThing* r) : SimpleThing(mat), left(l), right(r), binOp(b) {
	if (b != 'U' or b != 'I' or b != 'C') b = 'U'; }
CSG::~CSG() { delete left; delete right; }

void CSG::setLeft(SimpleThing* thing) {
	if (left != NULL) delete left;
	left = thing;
}
void CSG::setRight(SimpleThing* thing) {
	if (right != NULL) delete right;
	right = thing;
}
void CSG::setBinOp(char b) {
	if (b == 'I' or b == 'C') binOp = b;
	else binOp = 'U';
}

lu CSG::checkRay(Ray& ray, const lu max) {
	if (binOp == 'U') {
		lu lu_left = left->checkRay(ray, max);
		lu lu_right = right->checkRay(ray, max);
		if (lu_left <= 0) return lu_right;
		if (lu_right <= 0) return lu_left;
		if (lu_left < lu_right) return lu_left;
		else return lu_right;
	}
	if (binOp == 'I') {
		lu dist = left->checkRay(ray, max);
		if (dist > 0 and right->wraps(ray.origin + ray.direction.getUnitVect() * dist))
			return dist;
		dist = right->checkRay(ray, max);
		if (dist > 0 and left->wraps(ray.origin + ray.direction.getUnitVect() * dist))
			return dist;
		return -1;
	}
	if (binOp == 'C') {
		lu dist;
		if (right->onSurface(ray.origin) or right->wraps(ray.origin)) {
			dist = right->checkInnerRay(ray);
			if (left->wraps(ray.origin + ray.direction.getUnitVect() * dist)) return dist;
			/*else return -1;*/
		}
		dist = left->checkRay(ray, max);
		if (dist > 0 and right->wraps(ray.origin + ray.direction.getUnitVect() * dist)) {	
			dist = right->checkInnerRay(ray);
			if (dist > 0 and left->wraps(ray.origin + ray.direction.getUnitVect() * dist))
				return dist;
			else
				return -1;
		} 
		return dist;
	}
	return -1;
}

lu CSG::checkInnerRay(Ray& ray) const {
	if (binOp == 'U') {
		lu left_dist = left->checkInnerRay(ray);
		lu right_dist = right->checkInnerRay(ray);
		if (left_dist < 0) return right_dist;
		if (right_dist < 0) return left_dist;
		if (left_dist < right_dist)
			if (right->wraps(ray.origin + ray.direction.getUnitVect() * left_dist))
				return right_dist;
			return left_dist;
		if (left->wraps(ray.origin + ray.direction.getUnitVect() * right_dist))
			return left_dist;
		return right_dist;
	}
	if (binOp == 'I') {
		lu left_dist = left->checkInnerRay(ray);
		lu right_dist = right->checkInnerRay(ray);
		if (left_dist < right_dist)
			return left_dist;
		return right_dist;
	}
	if (binOp == 'C') {
		lu dist = right->checkRay(ray, -1);
		if (dist > 0 and left->wraps(ray.origin + ray.direction.getUnitVect() * dist))
			return dist;
		return left->checkInnerRay(ray);
	}
	return -1;
}

Vect CSG::getNormal(const Vect& position) const {
	if (binOp == 'U') {
		if (left->onSurface(position)) return left->getNormal(position);
		return right->getNormal(position);
	} if (binOp == 'I') {
		if (left->onSurface(position)) return left->getNormal(position);
		return right->getNormal(position);
	} if (binOp == 'C') {
		if (left->wraps(position)) return -(right->getNormal(position));
		return left->getNormal(position);
	}
	return Vect::null();
}

bool CSG::wraps(const Vect& position) const {
	if (binOp == 'U') {
		return left->wraps(position) or right->wraps(position);
	}
	if (binOp == 'I') {
		return left->wraps(position) and right->wraps(position);
	}
	if (binOp == 'C') {
		return false;
	}
	return false;
}

bool CSG::onSurface(const Vect& position) const {
	if (binOp == 'U') {
		if (left->onSurface(position) and !(right->wraps(position))) return true;
		if (right->onSurface(position) and !(left->wraps(position))) return true;
		return false;
	}
	if (binOp == 'I') {
		if (left->onSurface(position) and (right->wraps(position))) return true;
		if (right->onSurface(position) and (left->wraps(position))) return true;
		return false;
	}
	if (binOp == 'C') {
		return false;
	}
	return false;
}



