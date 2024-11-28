#pragma once
#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include<string>
#include<fstream>
#include<unordered_map>
#include<filesystem>
#include<locale>
#include<SFML/Graphics.hpp>



namespace SFGF {

	class FileConfig {
	protected:
		std::filesystem::path fileDirectory;
		std::string fileExtension;
	public:
		[[nodiscard]]
		std::filesystem::path getDirectory() const {
			return this->fileDirectory;
		}

		[[nodiscard]]
		std::string getExtension() const {
			return this->fileExtension;
		}

		void setExtension(const std::string& newExtension) {
			this->fileExtension = newExtension;
		}

		void setDirectory(const std::string& newDirectory);
	};

	class baseResourcesManager {
	protected:
		FileConfig config;
	public:
		baseResourcesManager() = default;
		baseResourcesManager(const std::string& directory, const std::string& extension);
	};

	class LanguageResource {
	private:
		std::unordered_map<std::string, std::wstring> translations;
	public:
		void loadResource(const std::filesystem::path path);

		[[nodiscard]]
		std::wstring getTranslation(const std::string& languageID);
	};


	class LanguageResourcesManager : public baseResourcesManager {
	public:

		LanguageResourcesManager() = default;
		LanguageResourcesManager(const std::string& directory, const std::string& extension) : baseResourcesManager(directory, extension) {}
		~LanguageResourcesManager() = default;

		LanguageResource getResource(const std::string& resourceName) const;

		std::wstring getTranslation(const std::string& resourceName, const std::string& languageID) const;

	};

	class TextureManager : public baseResourcesManager {
	public:
		TextureManager() = default;
		TextureManager(const std::string& directory, const std::string& extension) : baseResourcesManager(directory, extension) {}
		~TextureManager() = default;

		void loadTexture(const std::string& fileName, sf::Texture& texture) const;
	};

}

#endif