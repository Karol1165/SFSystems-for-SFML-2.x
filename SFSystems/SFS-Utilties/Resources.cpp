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

	void LanguageResource::loadResource(const std::filesystem::path Path) {

		if (!std::filesystem::is_regular_file(Path)) {
			throw std::filesystem::filesystem_error("File does not exist", Path, std::error_code());
		}

		std::wifstream resourceFile(Path);

		resourceFile.imbue(std::locale(".UTF-8"));

		std::wstring line;



		while (!resourceFile.eof()) {
			std::getline(resourceFile, line);

			std::string language;
			std::wstring resource;

			bool isLanguageExtracted = false;
			for (auto& i : line) {
				if (isLanguageExtracted == false) {
					if (i == ':') {
						isLanguageExtracted = true;
						continue;
					}
					language += i;
				}
				else {
					resource += i;
				}
			}

			this->translations[language] = resource;
		}

		resourceFile.close();

	}

	std::wstring LanguageResource::getTranslation(const std::string& languageID) {
		return this->translations[languageID];
	}

	LanguageResource LanguageResourcesManager::getResource(const std::string& resourceName) const {
		LanguageResource resource;
		resource.loadResource(this->config.getDirectory() /  (resourceName + this->config.getExtension()) );
		return resource;
	}

	std::wstring LanguageResourcesManager::getTranslation(const std::string& resourceName, const std::string& languageID) const {
		return this->getResource(resourceName).getTranslation(languageID);
	}

	 void TextureManager::loadTexture(const std::string& fileName, sf::Texture& texture) const {
		std::filesystem::path Path(this->config.getDirectory() / (fileName + this->config.getExtension()));
		texture.loadFromFile(Path.string());
	}
}