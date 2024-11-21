#include "pch.h"
#include "Resources.hpp"


namespace SFGF {

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

	void LanguageResourcesManager::setDirectory(const std::string& newDirectory) {
		this->resourcesDirectory = std::filesystem::current_path();
		this->resourcesDirectory /= newDirectory;
	}

	LanguageResourcesManager::LanguageResourcesManager(const std::string& directory, const std::string& extension) : fileExtension(extension) {
		this->setDirectory(directory);
	}

	LanguageResource LanguageResourcesManager::getResource(const std::string& resourceName) const {
		LanguageResource resource;
		resource.loadResource(this->resourcesDirectory /  (resourceName + this->fileExtension) );
		return resource;
	}

	std::wstring LanguageResourcesManager::getTranslation(const std::string& resourceName, const std::string& languageID) const {
		return this->getResource(resourceName).getTranslation(languageID);
	}
}