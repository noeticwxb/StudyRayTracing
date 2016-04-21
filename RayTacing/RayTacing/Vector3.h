#ifndef _VECTOR3_H_
#define _VECTOR3_H_ 1
#include <cmath>
#include <iostream>

#include "config.h"

struct Vector3
{
public:
	Vector3(){ mV[0] = 0; mV[1] = 0; mV[2] = 0; }
	Vector3(float x, float y, float z){ mV[0] = x; mV[1] = y; mV[2] = z; }
	Vector3(const Vector3& rhs){ *this = rhs; }
	~Vector3(){ }

	float x() const { return mV[0]; }
	float y() const { return mV[1]; }
	float z() const { return mV[2]; }

	const Vector3& operator+() const{ return *this; }
	Vector3 operator-() const { return Vector3(-mV[0], -mV[1], -mV[2]); }
	float operator[](int i) const{ return mV[i]; }
	float& operator[](int i) { return mV[i]; }

	float length() const { return sqrt(squareLength()); }
	float squareLength() const { return mV[0] * mV[0] + mV[1] * mV[1] + mV[2] * mV[2]; }
	void makeUnitVector(){ *this = *this / length(); }

	void setX(float x){ mV[0] = x; }
	void setY(float y){ mV[1] = y; }
	void setZ(float z){ mV[2] = z; }

	float minComponent() const{
		float tmp = mV[0];
		if (mV[1] < tmp) tmp = mV[1];
		if (mV[2] < tmp) tmp = mV[2];
		return tmp;
	}
	float maxComponent() const{
		float tmp = mV[0];
		if (mV[1] > tmp) tmp = mV[1];
		if (mV[2] > tmp) tmp = mV[2];
		return tmp;
	}
	float minAbsComponent() const{
		float tmp = abs(mV[0]);
		if (abs(mV[1]) < tmp) tmp = abs(mV[1]);
		if (abs(mV[2]) < tmp) tmp = abs(mV[2]);
		return tmp;
	}
	float maxAbsComponent() const{
		float tmp = abs(mV[0]);
		if (abs(mV[1]) > tmp) tmp = abs(mV[1]);
		if (abs(mV[2]) > tmp) tmp = abs(mV[2]);
		return tmp;
	}
	int indexOfMinComponen() const
	{
		float tmp = mV[0]; 
		int index = 0;
		if (mV[1] < tmp) {
			tmp = mV[1];
			index = 1;
		}
		if (mV[2] < tmp) {
			index = 2;
		}
		return index;
	}
	int indexOfMaxComponent() const{
		float tmp = mV[0];
		int index = 0;
		if (mV[1] > tmp) {
			tmp = mV[1];
			index = 1;
		}
		if (mV[2] > tmp) {
			index = 2;
		}
		return index;
	}
	int indexOfMinAbsComponen() const
	{
		float tmp = abs(mV[0]);
		int index = 0;
		if (abs(mV[1]) < tmp) {
			tmp = abs(mV[1]);
			index = 1;
		}
		if (abs(mV[2]) < tmp) {
			index = 2;
		}
		return index;

	}
	int indexOfMaxAbsComponent() const
	{
		float tmp = abs(mV[0]);
		int index = 0;
		if (abs(mV[1]) > tmp) {
			tmp = abs(mV[1]);
			index = 1;
		}
		if (abs(mV[2]) > tmp) {
			index = 2;
		}
		return index;
	}

	friend bool operator==(const Vector3& v1, const Vector3& v2);
	friend bool operator!=(const Vector3& v1, const Vector3& v2);

	friend std::istream& operator >> (std::istream &is, Vector3 &t);
	friend std::ostream& operator << (std::ostream &os, const Vector3& v);

	friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
	friend Vector3 operator/(const Vector3& v, float scalar);
	friend Vector3 operator*(const Vector3& v, float scalar);
	friend Vector3 operator*(float scalar, const Vector3& v);

	Vector3& operator=(const Vector3& v2){
		mV[0] = v2.mV[0]; mV[1] = v2.mV[1]; mV[2] = v2.mV[2];
		return *this;
	}
	Vector3& operator+=(const Vector3& v2){
		*this = *this + v2;
		return *this;
	}
	Vector3& operator-=(const Vector3& v2){
		*this = *this - v2;
		return *this;
	}
	Vector3& operator*=(float t){
		*this = *this * t;
		return *this;
	}
	Vector3& operator/=(const float t){
		*this = *this / t;
		return *this;
	}

	friend Vector3 unitVertor(const Vector3& v);
	friend Vector3 minVec(const Vector3& v1, const Vector3& v2);
	friend Vector3 maxVec(const Vector3& v1, const Vector3& v2);
	friend Vector3 cross(const Vector3& v1, const Vector3& v2);
	friend float dot(const Vector3& v1, const Vector3& v2);
	friend float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3);


protected:

	float mV[3];
};

inline bool operator==(const Vector3& v1, const Vector3& v2)
{
	if (v1.mV[0] != v2.mV[1]) return false;
	if (v1.mV[1] != v2.mV[1]) return false;
	if (v1.mV[2] != v2.mV[2]) return false;
	return true;
}
inline bool operator!=(const Vector3& v1, const Vector3& v2)
{
	return !(v1 == v2);
}

inline Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.mV[0] + v2.mV[0], v1.mV[1] + v2.mV[1], v1.mV[2] + v2.mV[2]);
}
inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.mV[0] - v2.mV[0], v1.mV[1] - v2.mV[1], v1.mV[2] - v2.mV[2]);
}
inline Vector3 operator/(const Vector3& v, float scalar)
{
	return Vector3(v.mV[0] / scalar, v.mV[1] / scalar, v.mV[2] / scalar);
}
inline Vector3 operator*(const Vector3& v, float scalar)
{
	return Vector3(v.mV[0] * scalar, v.mV[1] * scalar, v.mV[2] * scalar);
}
inline Vector3 operator*(float scalar, const Vector3& v)
{
	return Vector3(v.mV[0] * scalar, v.mV[1] * scalar, v.mV[2] * scalar);
}

inline Vector3 unitVertor(const Vector3& v)
{
	return v / v.length();
}
inline Vector3 minVec(const Vector3& v1, const Vector3& v2)
{
	Vector3 vec(v1);
	if (v2.x() < v1.x()) {
		vec.setX(v2.x());
	}
	if (v2.y() < v1.y()) {
		vec.setY(v2.y());
	}
	if (v2.z() < v2.z()) {
		vec.setZ(v2.z());
	}
	return vec;
}
inline Vector3 maxVec(const Vector3& v1, const Vector3& v2)
{
	Vector3 vec(v1);
	if (v2.x() > v1.x()) {
		vec.setX(v2.x());
	}
	if (v2.y() > v1.y()) {
		vec.setY(v2.y());
	}
	if (v2.z() > v2.z()) {
		vec.setZ(v2.z());
	}
	return vec;
}
inline Vector3 cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 tmp;
	tmp.mV[0] = v1.y() * v2.z() - v1.z() * v2.y();
	tmp.mV[2] = v1.z() * v2.x() - v1.x() * v2.z();
	tmp.mV[3] = v1.x() * v2.y() - v1.y() * v2.x();
	return tmp;
}
inline float dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

#endif



