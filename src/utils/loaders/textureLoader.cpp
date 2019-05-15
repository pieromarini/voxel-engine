#include "../../includes.h"
#include "textureLoader.h"

namespace utils {

  std::map<std::string, graphics::Texture> TextureLoader::m_TextureCache;
  TextureLoader::DefaultTextures TextureLoader::m_DefaultTextures;

  graphics::Texture* TextureLoader::load2DTexture(std::string path, bool isSRGB, graphics::TextureSettings *settings) {
	
	// Check the texture cache
	auto iter = m_TextureCache.find(path);
	if (iter != m_TextureCache.end()) {
	  return &iter->second;
	}

	// Load the texture
	int width, height, numComponents;
	unsigned char *data = SOIL_load_image(path.c_str(), &width, &height, &numComponents, 0);
	if (!data) {
	  utils::Logger::getInstance().error("[TextureLoader] Couldn't load texture: ", path);
	  SOIL_free_image_data(data);
	  return nullptr;
	}

	GLenum dataFormat = GL_RED;
	switch (numComponents) {
	  case 3: dataFormat = GL_RGB;  break;
	  case 4: dataFormat = GL_RGBA; break;
	}

	GLenum textureFormat = dataFormat;
	if (isSRGB) {
	  switch (dataFormat) {
		case GL_RGB: textureFormat = GL_SRGB; break;
		case GL_RGBA: textureFormat = GL_SRGB_ALPHA; break;
	  }
	}

	graphics::Texture texture;
	if (settings != nullptr)
	  texture.setTextureSettings(*settings);

	texture.generate2DTexture(width, height, textureFormat, dataFormat, data);

	SOIL_free_image_data(data);

	m_TextureCache.insert(std::pair<std::string, graphics::Texture>(path, texture));
	return &m_TextureCache[path];
  }

  graphics::Cubemap* TextureLoader::loadCubemapTexture(const std::string &right, const std::string &left, const std::string &top, const std::string &bottom, const std::string &back, const std::string &front, bool isSRGB, graphics::CubemapSettings *settings) {
	graphics::Cubemap *cubemap = new graphics::Cubemap();
	if (settings != nullptr)
	  cubemap->setCubemapSettings(*settings);

	std::vector<std::string> faces = { right, left, top, bottom, back, front };

	// Load the textures for the cubemap
	int width, height, numComponents;
	for (unsigned int i = 0; i < 6; ++i) {
	  unsigned char *data = SOIL_load_image(faces[i].c_str(), &width, &height, &numComponents, 0);

	  if (data) {
		GLenum dataFormat = GL_RED;
		switch (numComponents) {
		  case 3: dataFormat = GL_RGB;  break;
		  case 4: dataFormat = GL_RGBA; break;
		}

		GLenum textureFormat = dataFormat;
		if (isSRGB) {
		  switch (dataFormat) {
			case GL_RGB: textureFormat = GL_SRGB; break;
			case GL_RGBA: textureFormat = GL_SRGB_ALPHA; break;
		  }
		}

		cubemap->generateCubemapFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, width, height, textureFormat, dataFormat, data);
		SOIL_free_image_data(data);
	  }
	  else {
		utils::Logger::getInstance().error("[CubemapLoader] Couldn't load cubemap from ", faces[i]);
		SOIL_free_image_data(data);
		return cubemap;
	  }
	}

	return cubemap;
  }

  void TextureLoader::initializeDefaultTextures() {
	// Setup texture and minimal filtering because they are 1x1 textures so they require none
	m_DefaultTextures.m_DefaultAlbedo = load2DTexture(std::string("resources/textures/default/defaultAlbedo.png"), true);
	m_DefaultTextures.m_DefaultAlbedo->setAnisotropicFilteringMode(1.0f, true);
	m_DefaultTextures.m_DefaultAlbedo->setTextureMinFilter(GL_NEAREST);
	m_DefaultTextures.m_DefaultAlbedo->setTextureMagFilter(GL_NEAREST);
	m_DefaultTextures.m_DefaultNormal = load2DTexture(std::string("resources/textures/default/defaultNormal.png"), false);
	m_DefaultTextures.m_DefaultNormal->setAnisotropicFilteringMode(1.0f, true);
	m_DefaultTextures.m_DefaultNormal->setTextureMinFilter(GL_NEAREST);
	m_DefaultTextures.m_DefaultNormal->setTextureMagFilter(GL_NEAREST);
	m_DefaultTextures.m_FullMetallic = load2DTexture(std::string("resources/textures/default/white.png"), false);
	m_DefaultTextures.m_FullMetallic->setAnisotropicFilteringMode(1.0f, true);
	m_DefaultTextures.m_FullMetallic->setTextureMinFilter(GL_NEAREST);
	m_DefaultTextures.m_FullMetallic->setTextureMagFilter(GL_NEAREST);
	m_DefaultTextures.m_NoMetallic = load2DTexture(std::string("resources/textures/default/black.png"), false);
	m_DefaultTextures.m_NoMetallic->setAnisotropicFilteringMode(1.0f, true);
	m_DefaultTextures.m_NoMetallic->setTextureMinFilter(GL_NEAREST);
	m_DefaultTextures.m_NoMetallic->setTextureMagFilter(GL_NEAREST);
	m_DefaultTextures.m_FullRoughness = load2DTexture(std::string("resources/textures/default/white.png"), false);
	m_DefaultTextures.m_FullRoughness->setAnisotropicFilteringMode(1.0f, true);
	m_DefaultTextures.m_FullRoughness->setTextureMinFilter(GL_NEAREST);
	m_DefaultTextures.m_FullRoughness->setTextureMagFilter(GL_NEAREST);
	m_DefaultTextures.m_NoRoughness = load2DTexture(std::string("resources/textures/default/black.png"), false);
	m_DefaultTextures.m_NoRoughness->setAnisotropicFilteringMode(1.0f, true);
	m_DefaultTextures.m_NoRoughness->setTextureMinFilter(GL_NEAREST);
	m_DefaultTextures.m_NoRoughness->setTextureMagFilter(GL_NEAREST);
	m_DefaultTextures.m_DefaultAO = load2DTexture(std::string("resources/textures/default/white.png"), false);
	m_DefaultTextures.m_DefaultAO->setAnisotropicFilteringMode(1.0f, true);
	m_DefaultTextures.m_DefaultAO->setTextureMinFilter(GL_NEAREST);
	m_DefaultTextures.m_DefaultAO->setTextureMagFilter(GL_NEAREST);
	m_DefaultTextures.m_DefaultEmission = load2DTexture(std::string("resources/textures/default/black.png"), true);
	m_DefaultTextures.m_DefaultEmission->setAnisotropicFilteringMode(1.0f, true);
	m_DefaultTextures.m_DefaultEmission->setTextureMinFilter(GL_NEAREST);
	m_DefaultTextures.m_DefaultEmission->setTextureMagFilter(GL_NEAREST);
  }

}
