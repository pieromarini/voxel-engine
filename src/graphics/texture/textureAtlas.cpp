#include "textureAtlas.h"
#include "../../utils/loaders/textureLoader.h"

namespace graphics {

  TextureAtlas::TextureAtlas() {

	// Load and initialize Texture
	texture = utils::TextureLoader::load2DTexture("resources/textures/atlas.png", false);

	m_imageSize = 256;
	m_individualTextureSize = 16;
  }

  void TextureAtlas::bind() const {
	texture->bind(0);
  }

  std::vector<float> TextureAtlas::getTexture(const glm::vec2 &coords) {
	static const float TEX_PER_ROW = (float)m_imageSize / (float)m_individualTextureSize;
	static const float INDV_TEX_SIZE = 1.0f / TEX_PER_ROW;
	static const float PIXEL_SIZE = 1.0f / (float)m_imageSize;

	float xMin = (coords.x * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;
	float yMin = (coords.y * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;

	float xMax = (xMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;
	float yMax = (yMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;

	return { 
	  xMax, yMax, 
	  xMin, yMax, 
	  xMin, yMin, 
	  xMax, yMin 
	};
  }

}
