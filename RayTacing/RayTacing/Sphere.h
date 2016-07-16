#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Shape.h"
#include "BBox.h"

class Sphere : public Shape
{
public:
	virtual ~Sphere(){ }
	Sphere(const Vector3& _center, float _radius, rgb _color);
	BBox boundingBox() const;
	bool hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const override;
	bool shadowHit(const Ray& r, float tmin, float tmax, float time) const override;


protected:
private:
	Vector3 mCenter;
	float mRadius;
	rgb mColor;
};

#endif
