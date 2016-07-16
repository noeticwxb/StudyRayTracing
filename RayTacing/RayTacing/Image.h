#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <ostream>
#include "config.h"
#include "rgb.h"

class Image
{
public:
	Image();
	Image(int w, int h);
	// init with backgroud color
	Image(int w, int h, rgb background);
	virtual ~Image();

	// return false if x or y are out of bound
	bool set(int x, int y, rgb color);

	const rgb& get(int x, int y) const { assert(x >= 0 && x < mWidth && y >= 0 && y < mHeight); return mRaster[x][y]; }

	void gammaCorrect(float gamma = 2.2);

	void writePPM(std::ostream& o);
	void readPPM(std::string fileName);

	int Width() const { return mWidth; }
	int Height() const { return mHeight; }

protected:
	void clear();

protected:
	rgb** mRaster;
	int mWidth;
	int mHeight;
	
};

#endif


