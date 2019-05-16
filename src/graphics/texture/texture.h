#ifndef TEXTURE_H
#define TEXTURE_H


#include <GL/glew.h>
#include <glm/common.hpp>

#include "../../includes.h"

namespace graphics {

  struct TextureSettings {
	GLenum TextureWrapSMode = GL_CLAMP_TO_EDGE;
	GLenum TextureWrapTMode = GL_CLAMP_TO_EDGE;

	GLenum TextureMinificationFilterMode = GL_NEAREST;
	GLenum TextureMagnificationFilterMode = GL_NEAREST;
	float TextureAnisotropyLevel = 8.0f;

	bool HasMips = false;
	int MipBias = 0;
  };

  class Texture {
	public:
	  Texture();
	  Texture(TextureSettings settings);
	  ~Texture();

	  void generate2DTexture(unsigned int width, unsigned int height, GLenum textureFormat, GLenum dataFormat, const void *data);

	  void bind(int unit = -1);
	  void unbind();

	  void setTextureWrapS(GLenum textureWrapMode, bool shouldBind = false);
	  void setTextureWrapT(GLenum textureWrapMode, bool shouldBind = false);
	  void setTextureMinFilter(GLenum textureFilterMode, bool shouldBind = false);
	  void setTextureMagFilter(GLenum textureFilterMode, bool shouldBind = false);
	  void setAnisotropicFilteringMode(float textureAnisotropyLevel, bool shouldBind = false);

	  void setMipMode(bool shouldGenMips, int mipBias);
	  inline void setTextureSettings(TextureSettings settings) { m_TextureSettings = settings; }
	  unsigned int getWidth() const { return m_Width; }
	  unsigned int getHeight() const { return m_Height; }

	  inline unsigned int getTextureId() { return m_TextureId; }
	private:

	  // TODO: Need support for deletion/cleanup of cubemaps
	  unsigned int m_TextureId;
	  GLenum m_TextureTarget;

	  unsigned int m_Width, m_Height;
	  GLenum m_TextureFormat;

	  TextureSettings m_TextureSettings;
  };

}

#endif
