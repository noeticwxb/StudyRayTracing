#ifndef _ONB_H_
#define _OBN_H_ 1

#include <iostream>

#include "Vector3.h"


// 构建正交基
class ONB
{
public:
	ONB(){ }
	ONB(const Vector3& u, const Vector3& v, const Vector3& w){
		mU = u; mV = v; mW = w;
	}

	void set(const Vector3& u, const Vector3& v, const Vector3& w){
		mU = u; mV = v; mW = w;
	}
	~ONB(){ }

	const Vector3& u() const { return mU; }
	const Vector3& v() const{ return mV; }
	const Vector3& w() const{ return mW; }

	void initFromU(const Vector3& u);
	void initFromV(const Vector3& v);
	void initFromW(const Vector3& w);

	// calculate from two vectors.the direction of first one is fixed but normalized. second is normalized and its direction can be adjusted
	void initFromUV(const Vector3& u, const Vector3& v);
	void initFromVU(const Vector3& v, const Vector3& u);

	void initFromUW(const Vector3& u, const Vector3& w);
	void initFromWU(const Vector3& w, const Vector3& u);

	void initFromVW(const Vector3& v, const Vector3& w);
	void initFromWV(const Vector3& w, const Vector3& v);

	friend std::istream& operator>>(std::istream in, ONB& t);
	friend std::ostream& operator<<(std::ostream o, const ONB& t);
	friend bool operator==(const ONB& o1, const ONB& o2);

protected:
	Vector3 mU, mV, mW;
};

#endif


