#include "pch.h"
#include "GettextParser.hpp"

namespace SFS {
	namespace GettextParser {


		void Translation::addToLastTranslation(const std::string& translation) {
			if (isPlural())
				std::get<std::vector<std::string>>(this->translations).back().append(translation);
			else
				std::get<std::string>(this->translations).append(translation);
		}

		void Translation::addTranslation(const std::string& translation) {
			if (std::holds_alternative<std::string>(this->translations)) {
				setTranslations({ std::get<std::string>(this->translations), translation });
			}
			else {
				std::get<std::vector<std::string>>(this->translations).push_back(translation);
			}
		}

		std::vector<std::string> Translation::getTranslations() const {
			if (isPlural())
				return std::get<std::vector<std::string>>(translations);
			else
				return  { std::get<std::string>(translations) };
		}

		std::string Translation::getRawTranslation(int64_t form) const {
			if (isPlural())
				return std::get<std::vector<std::string>>(translations)[form];
			else 
				return std::get<std::string>(translations);
		}

		static void tryCommit(std::optional<std::string>& msgid, std::optional<Translation>& msgstr, std::optional<std::string>& msgctx,
			std::map<TranslationKey, Translation>& container) {
			if (msgid) {
				TranslationKey key;
				key.first = msgid.value();

				if (msgctx)
					key.second = msgctx.value();
				else
					key.second = "";

				if (msgstr) {
					container[key] = msgstr.value();
					msgid.reset();
					msgstr.reset();
					msgctx.reset();
				}
				else
					return;
			}
		}

		static std::string extractString(const std::string& line, size_t& pos) {
			std::string rawData;
			while (line.at(pos) != '\"') {
				rawData += line[pos++];
			}
			return parseEscapeSequences(rawData);
		}

		void TranslationMap::LoadFromFile(const fs::path& filePath) {
			enum class LastParsedState {msgid, msgstr, msgctx, header, start};

			LastParsedState lastParsedState = LastParsedState::start;

			std::ifstream file;
			file.imbue(std::locale("en_US.UTF-8")); // Set locale to UTF-8

			file.open(filePath);

			if (!file.is_open())
				throw std::runtime_error("Could not open file: " + filePath.string());

			std::string line;
			size_t pos;

			std::optional<std::string> msgid;
			std::optional<Translation> msgstr;
			std::optional<std::string> msgctxt;

			while (std::getline(file, line)) {
				pos = 0;

				//Ignored elements
				if (line.empty() || match(line, pos, "#") || match(line, pos, "msgid_plural"))
					continue;
				
				if (match(line, pos, "msgid")) {
					exceptedString(line, pos, "\"");

					//Parse header msgid
					if (match(line, pos, "\"")) {
						if(lastParsedState != LastParsedState::start)
							throw std::runtime_error("Non-Header msgid must not be empty");

						lastParsedState = LastParsedState::header;
						continue;
					}

					//Try commit previous translation
					tryCommit(msgid, msgstr, msgctxt, this->translations);

					if (msgid)
						throw std::runtime_error("msgid already defined");


					msgid = extractString(line, pos);

					lastParsedState = LastParsedState::msgid;
				}
				else if (match(line, pos, "msgstr")) {
					if (lastParsedState == LastParsedState::header)
						continue;

					if (match(line, pos, "[")) {
						while(!match(line, pos, "]")) {
							pos++;
						}

						if (msgstr.has_value()) {
							if(!msgstr->isPlural())
								throw std::runtime_error("Combining plural and non-plural msgstr");

							if(!match(line, pos, "\""))
								throw std::runtime_error("Expected \" after plural msgstr definition");

							if(Header.pluralCount <= msgstr.value().getTranslations().size())
								throw std::runtime_error("Too many plural forms defined in msgstr, expected " + std::to_string(Header.pluralCount) + " but got " + std::to_string(msgstr.value().getTranslations().size()));

							msgstr->addTranslation(extractString(line, pos));
						}
						else
						{
							if (!match(line, pos, "\""))
								throw std::runtime_error("Expected \" after plural msgstr definition");

							msgstr = Translation(PluralTranslation( { extractString(line, pos) } ));
						}
						lastParsedState = LastParsedState::msgstr;
						continue;
					}

					exceptedString(line, pos, "\"");

					if(msgstr)
						throw std::runtime_error("msgstr already defined");

					msgstr = Translation(extractString(line, pos));

					lastParsedState = LastParsedState::msgstr;

				}
				else if (match(line, pos, "msgctxt")) {
					exceptedString(line, pos, "\"");

					if (match(line, pos, "\""))
						throw std::runtime_error("msgctxt must not be empty");

					tryCommit(msgid, msgstr, msgctxt, this->translations);

					if (msgctxt)
						throw std::runtime_error("msgctxt already defined");

					msgctxt = extractString(line, pos);

					lastParsedState = LastParsedState::msgctx;
				}
				else if (match(line, pos, "\"")) {

					switch (lastParsedState) {
						case LastParsedState::msgid: {
							if (!msgid)
								throw std::runtime_error("msgid parsed, but empty");
							msgid.value() += extractString(line, pos);
							break;
						}
						case LastParsedState::msgstr: {
							msgstr.value().addToLastTranslation(extractString(line, pos));
							break;
						}
						case LastParsedState::msgctx: {
							if (!msgctxt)
								throw std::runtime_error("msgctxt parsed, but empty");

							msgctxt.value() += extractString(line, pos);
							break;
						}
						case LastParsedState::header: {
							if (match(line, pos, "Plural-Forms:")) {

								size_t nplurals = 0;
								std::unique_ptr<CExpressionParser::Expression> form = nullptr;

								if (match(line, pos, "nplurals")) {
									if (match(line, pos, "=")) {

										std::string rawData;

										while (!match(line, pos, ";")) {
											rawData += line[pos++];
										}

										nplurals = std::stoi(rawData);

									} else
										throw std::runtime_error("Invalid plural forms");
								} else
									throw std::runtime_error("Invalid plural forms");

								if (match(line, pos, "plural")) {
									if (match(line, pos, "=")) {

										std::string rawData;

										while (!match(line, pos, ";")) {
											rawData += line[pos++];
										}

										form  = CExpressionParser::parseExpression(rawData);

									} 
								}
								Header = PoHeader{nplurals, std::move(form)};
							}
							break;
						}
						default:
							break;
					}
				} 


			}
			tryCommit(msgid, msgstr, msgctxt, this->translations);

			file.close();
		}

		Translation TranslationMap::getRawTranslation(const TranslationKey& key) const {
			return this->translations.at(key);
		}

		std::string TranslationMap::getRawText(const TranslationKey& key, const int64_t& count) const {
			return this->getRawTranslation(key).getRawTranslation(this->Header.pluralForm->evaluate(count));
		}

		sf::String TranslationMap::getText(const TranslationKey& key, const int64_t& count) const {
			std::string rawText = this->getRawText(key, count);
			return sf::String::fromUtf8(rawText.begin(), rawText.end());
		}

	}

}