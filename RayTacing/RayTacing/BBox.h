#ifndef _BBOX_H_
#define _BBOX_H_
#include "Ray.h"

class BBox
{
public:
	BBox(){}
	BBox(const Vector3& a, const Vector3& b) { mPP[0] = a; mPP[1] = b; }
	const Vector3& min() const { return mPP[0]; }
	const Vector3& max() const { return mPP[1]; }

	bool rayIntersect(const Ray& r, float tmin, float tmax) const;

protected:
private:
	Vector3 mPP[2];
};

inline BBox surround(const BBox& b1, const BBox& b2)
{
	return BBox(
		Vector3(
		b1.min().x() < b2.min().x() ? b1.min().x() : b2.min().x(),
		b1.min().y() < b2.min().y() ? b1.min().y() : b2.min().y(),
		b1.min().z() < b2.min().z() ? b1.min().z() : b2.min().z()
		),
		Vector3(
		b1.max().x() > b2.max().x() ? b1.max().x() : b2.max().x(),
		b1.max().y() > b2.max().y() ? b1.max().y() : b2.max().y(),
		b1.max().z() > b2.max().z() ? b1.max().z() : b2.max().z()
		)
		);
}

inline bool BBox::rayIntersect(const Ray& r, float tmin, float tmax) const
{
	float interval_min = tmin;
	float interval_max = tmax;

	// x 
	int posneg = r.posneg()[0];
	float t0 = (mPP[posneg].x() - r.origin().x()) * r.invDirection().x();
	float t1 = (mPP[1 - posneg].x() - r.origin().x()) * r.invDirection().x();
	if ( t0 > interval_min )
	{
		interval_min = t0;
	}

	if (t1 < interval_max )
	{
		interval_max = t1;
	}

	if (interval_min > interval_max)
	{
		return false;
	}

	// y 
	posneg = r.posneg()[1];
	t0 = (mPP[posneg].y() - r.origin().y()) * r.invDirection().y();
	t1 = (mPP[1 - posneg].y() - r.origin().y()) * r.invDirection().y();
	if (t0 > interval_min)
	{
		interval_min = t0;
	}

	if (t1 < interval_max)
	{
		interval_max = t1;
	}

	if (interval_min > interval_max)
	{
		return false;
	}

	// z 
	posneg = r.posneg()[2];
	t0 = (mPP[posneg].z() - r.origin().z()) * r.invDirection().z();
	t1 = (mPP[1 - posneg].z() - r.origin().z()) * r.invDirection().z();
	if (t0 > interval_min)
	{
		interval_min = t0;
	}

	if (t1 < interval_max)
	{
		interval_max = t1;
	}

	if (interval_min > interval_max)
	{
		return false;
	}
	else
	{
		return true; 
	}

}

#endif
