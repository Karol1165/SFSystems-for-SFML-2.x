#pragma once
#ifndef GETTEXTPARSER_HPP_
#define GETTEXTPARSER_HPP_
#include "CExpressionParser.hpp"
#include <filesystem>
#include <map>
#include <variant>
#include <fstream>
#include "framework.h"
#include <SFML/System.hpp>


namespace SFS {
	namespace GettextParser {
		namespace fs = std::filesystem;
		using namespace SFS;
		using namespace Parser;

		using SingularTranstlation = std::string;
		using PluralTranslation = std::vector<std::string>;
		
		class TranslationMap;

		class Translation {
		private:

			std::variant<SingularTranstlation, PluralTranslation> translations;

			void setTranslation(const SingularTranstlation& translation) {
				translations = translation;
			}

			void setTranslations(const PluralTranslation& translations) {
				this->translations = translations;
			}

			void addToLastTranslation(const std::string& translation);

			void addTranslation(const std::string& translation);

			[[nodiscard]]
			SingularTranstlation getRawTranslation(int64_t form = 0) const;

			[[nodiscard]]
			PluralTranslation getTranslations() const;
			
		public:
			friend class TranslationMap;

			Translation() = default;
			Translation(const SingularTranstlation& translation) : translations(translation) {}
			Translation(const PluralTranslation& translations) : translations(translations) {}

			[[nodiscard]]
			bool isPlural() const {
				return std::holds_alternative<PluralTranslation>(translations);
			}
		};

		struct PoHeader {
			size_t pluralCount = 1;
			std::unique_ptr<CExpressionParser::Expression> pluralForm = nullptr;
		};

		using msgid = std::string;
		using msgctx = std::string;
		using TranslationKey = std::pair<msgid, msgctx>;

		class SFS_U_API TranslationMap {
		private:

			std::map<TranslationKey, Translation> translations;
			PoHeader Header;


		public:
			TranslationMap() = default;

			//This method returns translation with text in raw UTF-8 bytes, make sure to handle encoding properly, or use getText() instead.
			[[nodiscard]]
			Translation getRawTranslation(const TranslationKey& key) const;

			//This method returns text in raw UTF-8 bytes, make sure to handle encoding properly, or use getText() instead.
			[[nodiscard]]
			std::string getRawText(const TranslationKey& key, const int64_t& count = 0) const;

			[[nodiscard]]
			sf::String getText(const TranslationKey& key, const int64_t& count = 0) const;

			void LoadFromFile(const fs::path& filePath);

		};
	}
}

#endif