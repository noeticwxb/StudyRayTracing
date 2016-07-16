#include "stdafx.h"
#include "Texture2D.h"
#include "Image.h"

Texture2D::Texture2D(GLuint width, GLuint height)
{
	mWidth = width;
	mHeight = height;
	mData.resize(mWidth*mHeight);
	for (unsigned int i = 0; i < mWidth; ++i)
	{
		for (unsigned int j = 0; j < mHeight; ++j)
		{
			mData.at(i*mHeight + j) = 0x00FF0000;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &mTextureObject);
	glBindTexture(GL_TEXTURE_2D, mTextureObject);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mData[0]);
}
Texture2D::~Texture2D()
{
	glDeleteTextures(0, &mTextureObject);
	mTextureObject = 0;

}
void Texture2D::Update(Image* img)
{
	assert(mWidth == img->Width());
	assert(mHeight == img->Height());
	for (unsigned int i = 0; i < mWidth; ++i)
	{
		for (unsigned int j = 0; j < mHeight; ++j)
		{
			const rgb& color = img->get(i, j);
			mData[i*mHeight + j] = color.toABGR();
		}
	}

	glBindTexture(GL_TEXTURE_2D, mTextureObject);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight,GL_RGBA, GL_UNSIGNED_BYTE, &mData[0]);
}