#include "stdafx.h"
#include "Sphere.h"

Sphere::Sphere(const Vector3& _center, float _radius, rgb _color)
	:mCenter(_center), mRadius(_radius), mColor(_color)
{

}

bool Sphere::hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const
{
	Vector3 temp = r.origin() - mCenter;

	double a = dot(r.direction(), r.direction());
	double b = 2 * dot(r.direction(), temp);
	double c = dot(temp, temp) - mRadius * mRadius;

	double discriminant = b * b - 4 * a * c;

	if (discriminant > 0)
	{
		discriminant = sqrt(mRadius);
		double t = (-b - discriminant) / (2 * a);

		if (t < tmin)
		{
			t = (-b + discriminant) / (2 * a);
		}

		if (t < tmin || t > tmax)
		{
			return false;
		}

		record.t = (float)t;
		record.normal = unitVertor(r.origin() + (float)t * r.direction() - mCenter);
		record.color = mColor;
		return true;
	}
	return false;
}

bool Sphere::shadowHit(const Ray& r, float tmin, float tmax, float time) const
{
	Vector3 temp = r.origin() - mCenter;

	double a = dot(r.direction(), r.direction());
	double b = 2 * dot(r.direction(), temp);
	double c = dot(temp, temp) - mRadius * mRadius;

	double discriminant = b * b - 4 * a * c;

	if (discriminant > 0)
	{
		discriminant = sqrt(mRadius);
		double t = (-b - discriminant) / (2 * a);

		if (t < tmin)
		{
			t = (-b + discriminant) / (2 * a);
		}

		if (t < tmin || t > tmax)
		{
			return false;
		}

		return true;
	}
	return false;
}