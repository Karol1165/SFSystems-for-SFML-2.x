#pragma once
#ifndef RESOURCES_HPP_
#define RESOURCES_HPP_

#include<string>
#include<fstream>
#include<unordered_map>
#include<filesystem>
#include<locale>



namespace SFGF {

	class LanguageResource {
	private:
		std::unordered_map<std::string, std::wstring> translations;

	public:
		void loadResource(const std::filesystem::path path);

		[[nodiscard]]
		std::wstring getTranslation(const std::string& languageID);

	};

	class LanguageResourcesManager {
	private:

		std::filesystem::path resourcesDirectory;

		std::string fileExtension;

	public:
		LanguageResourcesManager() = default;
		LanguageResourcesManager(const std::string& directory, const std::string& extension);

		LanguageResource getResource(const std::string& resourceName) const;

		std::wstring getTranslation(const std::string& resourceName, const std::string& languageID) const;

		void setDirectory(const std::string& newDirectory);

		void setExtension(const std::string& newExtension) {
			this->fileExtension = newExtension;
		}

		[[nodiscard]]
		std::filesystem::path getDirectory() const {
			return this->resourcesDirectory;
		}

		[[nodiscard]]
		std::string getExtension() const {
			return this->fileExtension;
		}
	};

}

#endif