#include "pch.h"
#include "Resources.hpp"


namespace SFS {


	void FileConfig::setDirectory(const std::string& newDirectory) {
		this->fileDirectory = std::filesystem::current_path();
		this->fileDirectory /= newDirectory;
	}

	baseResourcesManager::baseResourcesManager(const std::string& directory, const std::string& extension) {
		this->config.setExtension(extension);
		this->config.setDirectory(directory);
	}



	 void TextureManager::loadTexture(const std::string& fileName, sf::Texture& texture) const {
		std::filesystem::path Path(this->config.getDirectory() / (fileName + this->config.getExtension()));
		texture.loadFromFile(Path.string());
	}
}