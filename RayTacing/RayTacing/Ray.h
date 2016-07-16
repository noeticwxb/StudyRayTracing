#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"
class Ray
{
public:
	Ray(){}
	Ray(const Vector3& a, const Vector3& b){ mData[0] = a; setDirection(b); }
	Ray(const Ray& r){ *this = r; }
	Ray& operator=(const Ray& original)
	{
		setOrigin(original.origin());
		setDirection(original.direction());
	}
	
	const Vector3& origin() const { return mData[0]; };
	
	const Vector3& direction() const { return mData[1]; }

	const Vector3& invDirection() const { return mData[2]; }

	void setOrigin(const Vector3& v){ mData[0] = v; }

	void setDirection(const Vector3& v)
	{
		mData[1] = v;
		mData[2] = Vector3(1.0f / v.x(), 1.0f / v.y(), 1.0f / v.z());

		mPosneg[0] = (mData[1].x() > 0 ? 0 : 1);
		mPosneg[1] = (mData[1].y() > 0 ? 0 : 1);
		mPosneg[2] = (mData[1].z() > 0 ? 0 : 1);
	}

	Vector3 pointAtParameter(float t) const
	{
		return mData[0] + t * mData[1];
	}

	const int* posneg() const { return mPosneg; }


protected:

private:
	Vector3 mData[3];
	int mPosneg[3];
};

inline std::ostream& operator << (std::ostream& os, const Ray &r)
{
	os << "(" << r.origin() << ") + t(" << r.direction() << ")";
	return os;
}




#endif	//	_RAY_H_