#include "stdafx.h"
#include "ONB.h"


const float ONB_EPSILON = 0.01f;

void ONB::initFromU(const Vector3& u)
{
	Vector3 n(1, 0, 0);
	Vector3 m(0, 1, 0);
	mU = unitVertor(u);
	mV = cross(mU, n);
	if (mV.length() < ONB_EPSILON )
	{
		mV = cross(mU, m);
	}
	mV = unitVertor(mV);
	mW = cross(mU, mV);
}

void ONB::initFromV(const Vector3& v)
{
	Vector3 n(1, 0, 0);
	Vector3 m(0, 1, 0);
	mV = unitVertor(v);
	mU = cross(mV, n);
	if (mU.length() < ONB_EPSILON)
	{
		mU = cross(mV, m);
	}
	mU = unitVertor(mU);
	mW = cross(mU, mV);
}

void ONB::initFromW(const Vector3& w)
{
	Vector3 n(1, 0, 0);
	Vector3 m(0, 1, 0);
	mW = unitVertor(w);
	mU = cross(mW, n);
	if (mU.length() < ONB_EPSILON)
	{
		mU = cross(mW, m);
	}
	mU = unitVertor(mU);
	mV = cross(mW, mU);
}

void ONB::initFromUV(const Vector3& u, const Vector3& v)
{
	mU = unitVertor(u);
	mW = unitVertor(cross(u, v));
	mV = cross(mW, mU);
}

void ONB::initFromVU(const Vector3& v, const Vector3& u)
{
	mV = unitVertor(v);
	mW = unitVertor(cross(u, v));
	mU = cross(mV, mW);
}

void ONB::initFromUW(const Vector3& u, const Vector3& w)
{
	mU = unitVertor(u);
	mV = unitVertor(cross(w, u));
	mW = cross(mU, mV);
}

void ONB::initFromWU(const Vector3& w, const Vector3& u)
{
	mW = unitVertor(w);
	mV = unitVertor(cross(w, u));
	mU = cross(mV, mW);
}

void ONB::initFromVW(const Vector3& v, const Vector3& w)
{
	mV = unitVertor(v);
	mU = unitVertor(cross(v, w));
	mW = cross(mU, mV);
}

void ONB::initFromWV(const Vector3& w, const Vector3& v)
{
	mW = unitVertor(w);
	mU = unitVertor(cross(v, w));
	mV = cross(mW, mU);
}

bool operator==(const ONB& o1, const ONB& o2)
{
	return (o1.u() == o2.u() && o1.v() == o2.v() && o1.w() == o2.w());
}

std::istream& operator >> (std::istream& in, ONB& t)
{
	Vector3 u, v, w;
	in >> u >> v >> w;
	t.initFromUV(u, v);

	return in;
}

std::ostream& operator<<(std::ostream& os, const ONB& t)
{
	os << t.u() << "\n" << t.v() << "\n" << t.w() << "\n";
	return os;
}
