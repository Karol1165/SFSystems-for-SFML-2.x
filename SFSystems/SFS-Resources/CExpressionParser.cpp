#include "pch.h"
#include "CExpressionParser.hpp"

namespace SFS {

	namespace CExpressionParser
	{

		int64_t Unary::evaluate(int64_t x) const {
			int64_t operandValue = this->operand->evaluate(x);
			switch (op) {
			case Operation::Neg: return -operandValue;
			case Operation::Not: return !operandValue;
			}
			return 0;
		}

		int64_t Binary::evaluate(int64_t x) const {
			int64_t leftValue = this->left->evaluate(x);
			int64_t rightValue = this->right->evaluate(x);
			switch (op) {
			case Operation::Add: return leftValue + rightValue;
			case Operation::Sub: return leftValue - rightValue;
			case Operation::Mul: return leftValue * rightValue;
			case Operation::Div: return leftValue / rightValue;
			case Operation::Mod: return leftValue % rightValue;
			case Operation::Eq:  return leftValue == rightValue;
			case Operation::Neq: return leftValue != rightValue;
			case Operation::Lt:  return leftValue < rightValue;
			case Operation::Gt:  return leftValue > rightValue;
			case Operation::Le:  return leftValue <= rightValue;
			case Operation::Ge:  return leftValue >= rightValue;
			case Operation::And: return leftValue && rightValue;
			case Operation::Or:  return leftValue || rightValue;
			}
			return 0;
		}

		int64_t Condition::evaluate(int64_t x) const {
			return this->condition->evaluate(x) ? this->trueExpr->evaluate(x) : this->falseExpr->evaluate(x);
		}

		std::unique_ptr<Expression> parseExpression(const std::string& expr) {
			std::unique_ptr<Expression> left;
			size_t pos = 0;
			left = parseCondition(expr, pos);

			return left;
		}

		std::unique_ptr<Expression> parseCondition(const std::string& expr, size_t& pos) {
			std::unique_ptr<Expression> condition = parseLogicalOr(expr, pos);

			skipWhiteChars(expr, pos);

			if (!match(expr, pos, "?"))
				return condition;

			std::unique_ptr<Expression> trueExpr = parseCondition(expr, pos);

			skipWhiteChars(expr, pos);

			if (!match(expr, pos, ":"))
				throw std::runtime_error("Excepted ':' after '?' at" + std::to_string(pos));

			std::unique_ptr<Expression> falseExpr = parseCondition(expr, pos);

			return std::make_unique<Condition>(move(condition), move(trueExpr), move(falseExpr));
		}

		std::unique_ptr<Expression> parseComparision(const std::string& expr, size_t& pos) {
			std::unique_ptr<Expression> left = parseAdditive(expr, pos);

			skipWhiteChars(expr, pos);

			if (match(expr, pos, "=="))
				return std::make_unique<Binary>(move(left), parseComparision(expr, pos), Binary::Operation::Eq);
			else if (match(expr, pos, "!="))
				return std::make_unique<Binary>(move(left), parseComparision(expr, pos), Binary::Operation::Neq);
			else if (match(expr, pos, "<="))
				return std::make_unique<Binary>(move(left), parseComparision(expr, pos), Binary::Operation::Le);
			else if (match(expr, pos, ">="))
				return std::make_unique<Binary>(move(left), parseComparision(expr, pos), Binary::Operation::Ge);
			else if (match(expr, pos, "<"))
				return std::make_unique<Binary>(move(left), parseComparision(expr, pos), Binary::Operation::Lt);
			else if (match(expr, pos, ">"))
				return std::make_unique<Binary>(move(left), parseComparision(expr, pos), Binary::Operation::Gt);
			else
				return left;

		}

		std::unique_ptr<Expression> parseLogicalAnd(const std::string& expr, size_t& pos) {
			std::unique_ptr<Expression> left = parseComparision(expr, pos);

			skipWhiteChars(expr, pos);

			if (!match(expr, pos, "&&"))
				return left;

			std::unique_ptr<Expression> right = parseLogicalAnd(expr, pos);

			return std::make_unique<Binary>(move(left), move(right), Binary::Operation::And);
		}

		std::unique_ptr<Expression> parseLogicalOr(const std::string& expr, size_t& pos) {
			std::unique_ptr<Expression> left = parseLogicalAnd(expr, pos);

			skipWhiteChars(expr, pos);

			if (!match(expr, pos, "||"))
				return left;

			std::unique_ptr<Expression> right = parseLogicalOr(expr, pos);

			return std::make_unique<Binary>(move(left), move(right), Binary::Operation::Or);
		}

		std::unique_ptr<Expression> parseAdditive(const std::string& expr, size_t& pos) {
			std::unique_ptr<Expression> left = parseMultiplicative(expr, pos);

			skipWhiteChars(expr, pos);

			if (match(expr, pos, "+"))
				return std::make_unique<Binary>(std::move(left), parseAdditive(expr, pos), Binary::Operation::Add);
			else if (match(expr, pos, "-"))
				return std::make_unique<Binary>(std::move(left), parseAdditive(expr, pos), Binary::Operation::Sub);
			else
				return std::move(left);
		}

		std::unique_ptr<Expression> parseMultiplicative(const std::string& expr, size_t& pos) {
			std::unique_ptr<Expression> left = parseUnary(expr, pos);

			skipWhiteChars(expr, pos);

			if (match(expr, pos, "*"))
				return std::make_unique<Binary>(std::move(left), parseMultiplicative(expr, pos), Binary::Operation::Mul);
			else if (match(expr, pos, "/"))
				return std::make_unique<Binary>(std::move(left), parseMultiplicative(expr, pos), Binary::Operation::Div);
			else if (match(expr, pos, "%"))
				return std::make_unique<Binary>(std::move(left), parseMultiplicative(expr, pos), Binary::Operation::Mod);
			else
				return left;
		}



		std::unique_ptr<Expression> parseUnary(const std::string& expr, size_t& pos) {
			skipWhiteChars(expr, pos);

			if (match(expr, pos, "!"))
				return std::make_unique<Unary>(parseUnary(expr, pos), Unary::Operation::Not);
			else if (match(expr, pos, "-"))
				return std::make_unique<Unary>(parseUnary(expr, pos), Unary::Operation::Neg);
			else
				return parsePrimary(expr, pos);
		}

		std::unique_ptr<Expression> parsePrimary(const std::string& expr, size_t& pos) {
			skipWhiteChars(expr, pos);

			std::unique_ptr<Expression> left;

			if (match(expr, pos, "(")) {
				left = parseCondition(expr, pos);

				skipWhiteChars(expr, pos);

				if (!match(expr, pos, ")"))
					throw std::runtime_error("Excepted ')' at " + std::to_string(pos));
			}
			else if (isdigit(expr[pos])) {
				int value = 0;
				while (pos < expr.size() && isdigit(expr[pos])) {
					value = value * 10 + (expr[pos] - '0');
					pos++;
				}
				left = std::make_unique<Const>(value);
			}
			else if (match(expr, pos, "n")) {
				left = std::make_unique<Var>();
			}
			else
				throw std::runtime_error("Unexcepted character at " + std::to_string(pos));

			return left;
		}
	}
}