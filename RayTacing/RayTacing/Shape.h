#ifndef _SHARP_H_
#define _SHARP_H_

#include "Ray.h"
#include "Vector3.h"
#include "rgb.h"

struct HitRecord
{
	float t;
	Vector3 normal;
	rgb color;
};

class Shape
{
public:
	virtual ~Shape(){ }
	virtual bool hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const = 0;
	virtual bool shadowHit(const Ray& r, float tmin, float tmax, float time) const = 0;
protected:
private:
};




#endif
