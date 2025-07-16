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

	
	


	class SFS_U_API LanguageResourcesManager : public baseResourcesManager {
	public:
		LanguageResourcesManager(const std::string& directory);
		~LanguageResourcesManager() = default;

		void loadLanguage(const std::string& fileName);

		[[nodiscard]]
		std::wstring Translate(const std::string& msgid, const int number = 1);



	private:
		std::map<GettextParser::TranslationKey, GettextParser::Translation> translations;
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
