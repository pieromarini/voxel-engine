#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include "../../includes.h"
#include "texture.h"

namespace graphics {

  class TextureAtlas {
	public:
	  // NOTE: This just initializes the default atlas "atlas.png"
	  TextureAtlas();
	  std::vector<float> getTexture(const glm::vec2 &coords);
	  void bind() const;

	private:
	  int m_imageSize;
	  int m_individualTextureSize;
	  graphics::Texture *texture;
  };

}
#endif
