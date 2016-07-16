#ifndef _RNG_H_
#define _RNG_H_ 1
#include "config.h"

// random number generator
class RNG
{
public:
	RNG(unsigned long long _seed = 7564231ULL)
	{
		mSeed = _seed;
		mMult = 62089911ULL;
		mLong_Max = 4294967295ULL;
		mFloat_Max = 4294967295.0f;
	}

	//[0,1)
	float operator()()
	{
		mSeed = mMult * mSeed;
		return float(mSeed % mLong_Max) / mFloat_Max;
	}

protected:
	unsigned long long mSeed;
	unsigned long long mMult;
	unsigned long long mLong_Max; 
	float mFloat_Max;
private:
};
#endif