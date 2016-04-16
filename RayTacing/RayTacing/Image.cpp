#include "stdafx.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include "Image.h"

using namespace std;

Image::Image()
: mRaster(0)
, mWidth(0)
, mHeight(0)
{
}
Image::Image(int w, int h)
{
	mWidth = w;
	mHeight = h;

	mRaster = NEW_ARRAY(rgb*,mWidth);
	for (int i = 0; i < mWidth;++i)
	{
		mRaster[i] = NEW_ARRAY(rgb,mHeight);
	}
}

Image::Image(int w, int h, rgb background)
: Image(w,h)
{
	for (int i = 0; i < mWidth;++i)
	{
		for (int j = 0; j < mHeight;++j)
		{
			mRaster[i][j] = background;
		}
	}
}


Image::~Image()
{
	clear();
}

void Image::clear()
{
	for (int i = 0; i < mWidth; ++i)
	{
		SAFE_DELETE_ARRAY(mRaster[i]);
	}
	SAFE_DELETE_ARRAY(mRaster);
	mWidth = 0;
	mHeight = 0;
}

bool Image::set(int x, int y, rgb color)
{
	if (0 > x || x > mWidth)
	{
		return false;
	}

	if (0 > y || y > mHeight)
	{
		return false;
	}

	mRaster[x][y] = color;
	return true;
}

void Image::gammaCorrect(float gamma /* = 2.2 */)
{
	rgb tmp;
	float power = 1.0f / gamma;
	for (int i = 0; i < mWidth; ++i)
	{
		for (int j = 0; j < mHeight; ++j)
		{
			tmp = mRaster[i][j];
			mRaster[i][j] = rgb(pow(tmp.r(), power), pow(tmp.g(), power), pow(tmp.b(), power));
		}
	}
}

void Image::writePPM(ostream& o)
{
	o << "P6\n";
	o << mWidth << ' ' << mHeight << '\n';
	o << "255\n";

	int i, j;
	unsigned int ired, igreen, iblue;
	unsigned char red, green, blue;
	for (i = mHeight - 1; i >= 0; i--)
	{
		for (j = 0; j < mWidth;++j)
		{
			ired = (unsigned int)(256 * mRaster[j][i].r());
			igreen = (unsigned int)(256 * mRaster[j][i].g());
			iblue = (unsigned int)(256 * mRaster[j][i].b());
			if (ired > 255) ired = 255;
			if (igreen > 255) igreen = 255;
			if (iblue > 255) iblue = 255;
			red = (unsigned char)ired;
			green = (unsigned char)igreen;
			blue = (unsigned char)iblue;
			o.put(red);
			o.put(green);
			o.put(blue);
		}
	}		
}

void Image::readPPM(string fileName)
{
	ifstream in;
	in.open(fileName);
	if (!in.is_open())
	{
		std::cerr << "Error: Can not open File" << fileName.c_str() << std::endl;
		exit(-1);
	}

	char ch, type;
	char red, green, blue;
	int i, j, cols, rows;
	int num;

	in.get(ch);
	in.get(type);
	in >> cols >> rows >> num;

	clear();

	mWidth = cols;
	mHeight = rows;

	mRaster = NEW_ARRAY(rgb*, mWidth);
	for (int i = 0; i < mWidth; ++i)
	{
		mRaster[i] = NEW_ARRAY(rgb, mHeight);
	}

	// clean up newline
	in.get(ch);

	for ( i = mHeight -1;i >=0;--i)
	{
		for (j = 0; j < mWidth; ++j)
		{
			in.get(red);
			in.get(green);
			in.get(blue);

			mRaster[i][j] = rgb(
				(float)((unsigned char)red) / 255.0f,
				(float)((unsigned char)green) / 255.0f,
				(float)((unsigned char)blue) / 255.0f);
			
		}
	}

}





