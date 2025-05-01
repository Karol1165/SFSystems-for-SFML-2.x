#pragma once
#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include<string>
#include<fstream>
#include<unordered_map>
#include<filesystem>
#include<locale>
#include<SFML/Graphics.hpp>
#include "framework.h"



namespace SFS {
	
	class SFS_U_API FileConfig {
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

	protected:

		std::filesystem::path fileDirectory;
		std::string fileExtension;

	};

	class SFS_U_API baseResourcesManager {
	public:

		baseResourcesManager() = default;
		~baseResourcesManager() = default;
		baseResourcesManager(const std::string& directory, const std::string& extension);

	protected:

		FileConfig config;

	};

	class LanguageResource {
	private:
		std::unordered_map<std::string, std::wstring> translations;
	public:
		void loadResource(const std::filesystem::path path);

		[[nodiscard]]
		std::wstring getTranslation(const std::string& languageID);
	};


	class SFS_U_API LanguageResourcesManager : public baseResourcesManager {
	public:

		LanguageResourcesManager() = default;
		LanguageResourcesManager(const std::string& directory, const std::string& extension) : baseResourcesManager(directory, extension) {}
		~LanguageResourcesManager() = default;

		[[nodiscard]]
		LanguageResource getResource(const std::string& resourceName) const;

		[[nodiscard]]
		std::wstring getTranslation(const std::string& resourceName, const std::string& languageID) const;

	};

	class SFS_U_API TextureManager : public baseResourcesManager {
	public:
		TextureManager() = default;
		TextureManager(const std::string& directory, const std::string& extension) : baseResourcesManager(directory, extension) {}
		~TextureManager() = default;

		void loadTexture(const std::string& fileName, sf::Texture& texture) const;
	};

}

#endif
