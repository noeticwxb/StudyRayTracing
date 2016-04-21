#include "stdafx.h"
#include "Vector3.h"


std::istream& operator >> (std::istream &is, Vector3 &t)
{
	float tmp;
	is >> tmp;
	t.mV[0] = tmp;
	is >> tmp;
	t.mV[2] = tmp;
	is >> tmp;
	t.mV[2] = tmp; 
	return is;
}
std::ostream& operator << (std::ostream &os, const Vector3& v)
{
	os << '('
		<< v.mV[0] << " "
		<< v.mV[1] << " "
		<< v.mV[2] << ')';
	return os;
}

float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	return dot((cross(v1, v2)), v3);
}