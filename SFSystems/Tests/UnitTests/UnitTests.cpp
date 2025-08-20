#include "pch.h"
#include "CppUnitTest.h"
#include "CExpressionParser.hpp"
#include "GettextParser.hpp"
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <locale>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	using namespace SFS::CExpressionParser;
	using namespace SFS::GettextParser;

	void handleException(const std::exception& e) {
		std::wstringstream ss;
		ss << L"Exception: " << e.what();
		Assert::Fail(ss.str().c_str());
	}

	inline TranslationKey makeKey(const std::string& msgid, const std::string& msgctx = "") {
		return { msgid, msgctx };
	}


	std::wstring utf8_to_wstring(const std::string& utf8str) {
		if (utf8str.empty()) return std::wstring();

		int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8str.data(), (int)utf8str.size(), nullptr, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, utf8str.data(), (int)utf8str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}

	TEST_CLASS(CExpressionParserTests)
	{
	public:
		
		TEST_METHOD(ParserVarTest)
		{
			std::unique_ptr<Expression> expr;
			expr = parseExpression("n");
			Assert::AreEqual(0, static_cast<int>(expr->evaluate(0)));
		}

		TEST_METHOD(ParserConstTest)
		{
			std::unique_ptr<Expression> expr;
			expr = parseExpression("5");
			Assert::AreEqual(5, static_cast<int>(expr->evaluate(0)));
		}

		TEST_METHOD(ParserComparisionTest1) {
			std::unique_ptr<Expression> expr;
			expr = parseExpression("5 == 5");
			Assert::AreEqual(1, static_cast<int>(expr->evaluate(0)));

			expr = parseExpression("5 != 5");
			Assert::AreEqual(0, static_cast<int>(expr->evaluate(0)));

			expr = parseExpression("5 < 10");
			Assert::AreEqual(1, static_cast<int>(expr->evaluate(0)));

			expr = parseExpression("5 > 10");
			Assert::AreEqual(0, static_cast<int>(expr->evaluate(0)));
		}

		TEST_METHOD(ParserNegTest)
		{
			std::unique_ptr<Expression> expr;
			expr = parseExpression("-5");
			Assert::AreEqual(-5, static_cast<int>(expr->evaluate(0)));
		}

		TEST_METHOD(ParserNotTest)
		{
			std::unique_ptr<Expression> expr;
			expr = parseExpression("!(5 > 10)");
			Assert::AreEqual(1, static_cast<int>(expr->evaluate(0)));
		}

		TEST_METHOD(ParserConditionTest) {
			std::unique_ptr<Expression> expr;
			expr = parseExpression("n != 1 ? 0 : 1");

			Assert::AreEqual(1, static_cast<int>(expr->evaluate(1)));
			Assert::AreEqual(0, static_cast<int>(expr->evaluate(2)));
		}

		TEST_METHOD(ExampleTest) {
			std::unique_ptr<Expression> expr;
			expr = parseExpression("n==1 ? 0 : (n%10>=2 && n%10<=4 && (n%100<10 || n%100>=20) ? 1 : 2)");
			Assert::AreEqual(0, static_cast<int>(expr->evaluate(1)));
			Assert::AreEqual(2, static_cast<int>(expr->evaluate(13)));
			Assert::AreEqual(2, static_cast<int>(expr->evaluate(130)));
		}
	};

	TEST_CLASS(TranslationMapTests)
	{
	private:
		TranslationMap translations;

	public:

		TEST_METHOD_INITIALIZE(Setup)
		{
			translations.LoadFromFile("test.po");
		}

		TEST_METHOD(SimpleTranslation)
		{
			auto key = makeKey("Open");
			auto result = translations.getText(key);
			Assert::AreEqual(sf::String("Otwórz") == result, true);
		}

		TEST_METHOD(ContextTranslation)
		{
			auto key = makeKey("File", "Menu");
			auto result = translations.getText(key);
			Assert::AreEqual(sf::String("Plik") == result, true);
		}

		TEST_METHOD(EmptyContextIsHandled)
		{
			auto key = makeKey("Open", "");
			auto result = translations.getText(key);
			Assert::AreEqual(sf::String("Otwórz") == result, true);
		}
	};
}
