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

	struct Translation {
		std::variant<std::wstring, std::vector<std::wstring>> msgstr;
	};

	using TranslationKey = std::pair<std::string, std::optional<std::string>>;
	


	class SFS_U_API LanguageResourcesManager : public baseResourcesManager {
	public:
		LanguageResourcesManager(const std::string& directory);
		~LanguageResourcesManager() = default;

		void loadFromFile(const std::string& path);

		[[nodiscard]]
		Translation getTranslation(TranslationKey key) const;
		
		[[nodiscard]]
		std::wstring getText(TranslationKey key, int pluralCount = 1);


	private:
		std::unordered_map<TranslationKey, Translation> translations;
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
