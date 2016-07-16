#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include "Shape.h"

class Triangle: public Shape
{
public:
	virtual ~Triangle(){ }
	Triangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, const rgb& _color);
	bool hit(const Ray& r, float tmin, float tmax, float time, HitRecord& recode) const override;;
	bool shadowHit(const Ray& r, float tmin, float tmax, float time) const override;;

protected:
private:
	Vector3 mP0;
	Vector3 mP1;
	Vector3 mP2;
	rgb mColor;
};

#endif
