#pragma once
#ifndef GETTEXTPARSER_HPP_
#define GETTEXTPARSER_HPP_
#include "CExpressionParser.hpp"
#include <filesystem>
#include <map>
#include <variant>
#include <fstream>
#include "framework.h"


//TODO: Do conversions from bytes to UTF-8 in get text methods. Add [[depractaded]] to old methods that return std::string and add new methods that return sf::String.

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
			SingularTranstlation getTranslation(unsigned int form = 0) const;

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

			[[nodiscard]]
			Translation getTranslation(const TranslationKey& key) const;

			[[nodiscard]]
			Translation getTranslation(const std::string& id, const std::optional<std::string>& context) const;

			[[nodiscard]]
			std::string getText(const TranslationKey& key, const int64_t& count = 0) const;

			[[nodiscard]]
			std::string getText(const std::string& id, const std::optional<std::string>& context, const int64_t& count = 0) const;
		

			void LoadFromFile(const fs::path& filePath);

		};
	}
}

#endif