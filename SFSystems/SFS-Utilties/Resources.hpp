#pragma once
#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include<string>
#include<fstream>
#include<unordered_map>
#include<filesystem>
#include<locale>
#include<variant>
#include<SFML/Graphics.hpp>
#include "GettextParser.hpp"
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

		void setExtension(const std::string& newExtension);

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

	
	

	//Language resources manager for loading and managing translations from .po files in gettext format. 
	class SFS_U_API LanguageResourcesManager : public baseResourcesManager {
	public:
		LanguageResourcesManager(const std::string& directory);
		~LanguageResourcesManager() = default;

		void loadLanguage(const std::string& fileName);

		[[nodiscard]]
		sf::String getText(const std::string& msgid, const std::string& msgctxt = "", const int& count = 1) const;

		[[nodiscard]]
		sf::String getText(const std::string& msgid, const int& count) const;

	private:

		GettextParser::TranslationMap translations;

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
