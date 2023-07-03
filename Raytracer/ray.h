#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// The ray class is intended to construct the rays that will be sent to the scene / camera via the raytracer.

class ray {
public:
	// Constructors:
	ray() {}
	ray(const point3& origin, const vec3& direction)
		: orig(origin), dir(direction)
	{}

	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }

	// Identifying a point on the 3D ray:
	point3 at(double t) const {
		return orig + t * dir;
	}

public:
	point3 orig;
	vec3 dir;
};

#endif