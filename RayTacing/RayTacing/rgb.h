#ifndef _RGB_H_
#define _RGB_H_ 1

#include <ostream>
#include "config.h"

struct rgb
{
public:
	rgb() { mR = 0; mG = 0; mB = 0; }
	rgb(float r, float g, float b) : mR(r), mG(g), mB(b){  }
	rgb(const rgb& color){ *this = color; }
	~rgb(){ }

	void setRed(float red){ mR = red; }
	void setGreen(float green){ mG = green; }
	void setBlue(float blue){ mB = blue; }

	// operator
	rgb& operator=(const rgb& rhs){
		mR = rhs.mR; mG = rhs.mG; mB = rhs.mB;
		return *this;
	}
	rgb& operator+=(const rgb& rhs){
		*this = *this + rhs;
		return *this; 
	}
	rgb& operator*=(const rgb& rhs){
		*this = *this * rhs;
		return *this; 
	}
	rgb& operator/=(const rgb& rhs){
		*this = *this / rhs;
		return *this;
	}
	rgb& operator*=(float rhs)
	{
		*this = *this * rhs;
		return *this;
	}
	rgb& operator/=(float rhs)
	{
		*this = *this / rhs;
		return *this;
	}

	rgb operator+()const { return *this; }
	rgb operator-()const{ return rgb(-mR, -mG, -mB); }

	float r() const { return mR; }
	float g() const { return mG; }
	float b() const { return mB; }

	void clamp();

	unsigned int toABGR() const
	{
		unsigned int r = unsigned(mR * 255) & 0x000000FF;
		unsigned int g = unsigned(mG * 255) & 0x000000FF;
		unsigned int b = unsigned(mB * 255) & 0x000000FF;

		//return (r << 24) + (g << 16) + (b << 8) + 0xFF;	
		int c = 0xFF000000 | (b << 16) | (g << 8 ) | r;
		return c;
	}

	// not member function, so declare as friend
	friend std::ostream& operator<<(std::ostream& out, const rgb& c);
	friend rgb operator*(const rgb& c, float f);
	friend rgb operator*(float f, const rgb& c);
	friend rgb operator/(const rgb& c, float f);
	friend rgb operator*(const rgb& c1, const rgb& c2);
	friend rgb operator/(const rgb& c1, const rgb& c2);
	friend rgb operator+(const rgb& c1, const rgb& c2);

protected:
	float mR;
	float mG;
	float mB;
};

inline void rgb::clamp()
{
	if( mR > 1.0f)
	{
		mR = 1.0f;
	}

	if (mG > 1.0f)
	{
		mG = 1.0f;
	}

	if (mB > 1.0f)
	{
		mB = 1.0f;
	}

	if (mR < 0.0f)
	{
		mR = 0.0f;
	}
	if (mG < 0.0f)
	{
		mG = 0.0f;
	}
	if (mB < 0.0f)
	{
		mB = 0.0f;
	}
}

inline std::ostream& operator<<(std::ostream& out, const rgb& c)
{
	out << c.mR << ' '
		<< c.mG << ' '
		<< c.mB << ' ';
	return out;
}

inline rgb operator*(const rgb& c, float f)
{
	return rgb(c.mR*f, c.mG*f, c.mB*f);
}

inline rgb operator*(float f, const rgb& c)
{
	return rgb(c.mR*f, c.mG*f, c.mB*f);
}

inline rgb operator/(const rgb&c, float f)
{
	return rgb(c.mR / f, c.mG / f, c.mB / f);
}

inline rgb operator*(const rgb& c1, const rgb& c2)
{
	return rgb(c1.mR*c2.mR, c1.mG*c2.mG, c1.mB*c2.mB); 
}

inline rgb operator/(const rgb& c1, const rgb& c2)
{
	return rgb(c1.mR / c1.mR, c1.mG / c2.mG, c1.mB / c2.mB); 
}

inline rgb operator+(const rgb& c1, const rgb& c2)
{
	return rgb(c1.mR + c2.mR, c1.mG + c2.mG, c1.mB + c2.mB);
}

#endif




