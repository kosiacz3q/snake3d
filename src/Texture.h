#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <GL/gl.h>
#include <IL/il.h>
#include <IL/ilut.h>

class Texture
{
	public:
		Texture();
		bool loadTextureFromPixels32(GLuint* pixels, GLuint width, GLuint height);
		bool loadTextureFromFile(std::string path);
		virtual ~Texture();
		void freeTexture();

		//Texture name
		GLuint mTextureID;

		//Texture dimensions
		GLuint mTextureWidth;
		GLuint mTextureHeight;
};

#endif /* TEXTURE_H_ */
