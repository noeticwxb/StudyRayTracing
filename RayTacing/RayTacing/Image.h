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

	void gammaCorrect(float gamma = 2.2);

	void writePPM(std::ostream& o);
	void readPPM(std::string fileName);

protected:
	void clear();

protected:
	rgb** mRaster;
	int mWidth;
	int mHeight;
	
};

#endif


