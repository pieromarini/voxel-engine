#pragma once

#include <GL/glew.h>
#include <glm/common.hpp>

#include "../../includes.h"

namespace graphics {

  struct TextureSettings {
	GLenum TextureWrapSMode = GL_REPEAT;
	GLenum TextureWrapTMode = GL_REPEAT;

	GLenum TextureMinificationFilterMode = GL_LINEAR_MIPMAP_LINEAR;
	GLenum TextureMagnificationFilterMode = GL_LINEAR;
	float TextureAnisotropyLevel = 8.0f;

	bool HasMips = true;
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
