#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#include <glut.h>
#include <vector>

class Image;

class Texture2D
{
public:
	Texture2D(GLuint width, GLuint height);
	~Texture2D();
	void Update(Image* img);
	GLuint GetGLObject(){ return mTextureObject; }

private:
	GLuint mTextureObject;
	std::vector<GLuint> mData;
	GLuint mWidth;
	GLuint mHeight;
};


#endif
