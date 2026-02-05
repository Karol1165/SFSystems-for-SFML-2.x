#include "pch.h"
#include "Resources.hpp"


namespace SFS {
	
	void FileConfig::setExtension(const std::string& newExtension) {
		if (newExtension[0] != '.')
			this->fileExtension = '.' + newExtension;
		else
			this->fileExtension = newExtension;
	}

	void FileConfig::setDirectory(const std::string& newDirectory) {
		this->fileDirectory = std::filesystem::current_path();
		this->fileDirectory /= newDirectory;
	}

	baseResourcesManager::baseResourcesManager(const std::string& directory, const std::string& extension) {
		this->config.setExtension(extension);
		this->config.setDirectory(directory);
	}

	LanguageResourcesManager::LanguageResourcesManager() : baseResourcesManager("", ".po") {}

	LanguageResourcesManager::LanguageResourcesManager(const std::string& directory) : baseResourcesManager(directory, ".po") {}

	void LanguageResourcesManager::loadLanguage(const std::string& fileName) {
		this->translations.LoadFromFile(this->config.getDirectory() / (fileName + this->config.getExtension()));
	}

	sf::String LanguageResourcesManager::getText(const std::string& msgid, const std::string& msgctxt, const int& count) const {
		return this->translations.getText({msgid, msgctxt}, count);
	}

	sf::String LanguageResourcesManager::getText(const std::string& msgid, const int& count) const {
		return this->getText(msgid, "", count);
	}

	void TextureManager::loadTexture(const std::string& fileName, std::optional<std::string> name) {
		textures[name.value_or(fileName)].loadFromFile(config.getPath(fileName).string());
	}

}