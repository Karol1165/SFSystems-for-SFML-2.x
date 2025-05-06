#include "pch.h"
#include "CParser.hpp"

namespace SFS::CParser
{

	int Unary::evaluate(int x) const {
		int operandValue = this->operand->evaluate(x);
		switch (op) {
			case Operation::Neg: return -operandValue;
			case Operation::Not: return !operandValue;
		}
		return 0;
	}

	int Binary::evaluate(int x) const {
		int leftValue = this->left->evaluate(x);
		int rightValue = this->right->evaluate(x);
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

	int Condition::evaluate(int x) const {
		return this->condition->evaluate(x) ? this->trueExpr->evaluate(x) : this->falseExpr->evaluate(x);
	}

	bool match(std::string& expr, size_t& pos, const std::string& pattern) {
		skipWhiteChars(expr, pos);
		if (expr.compare(pos, pattern.size(), pattern) == 0) {
			pos += pattern.size();
			return true;
		}
		return false;
	}

	std::unique_ptr<Expression> parseExpression(std::string& expr, size_t& pos) {
		std::unique_ptr<Expression> left;

		left = parseCondition(expr, pos);

		return left;
	}

	std::unique_ptr<Expression> parseCondition(std::string& expr, size_t& pos) {
		std::unique_ptr<Expression> condition = parseLogicalOr(expr, pos);

		skipWhiteChars(expr, pos);

		if (!match(expr, pos, "?"))
			return condition;
		
		std::unique_ptr<Expression> trueExpr = parseCondition(expr, pos);

		skipWhiteChars(expr, pos);

		if(!match(expr, pos, ":"))
			throw std::runtime_error("Excepted ':' after '?' at" + std::to_string(pos));

		std::unique_ptr<Expression> falseExpr = parseCondition(expr, pos);

		return std::make_unique<Condition>(condition.release(), trueExpr.release(), falseExpr.release());
	}

	std::unique_ptr<Expression> parseComparision(std::string& expr, size_t& pos) {
		std::unique_ptr<Expression> left = parseAdditive(expr, pos);

		skipWhiteChars(expr, pos);

		if (match(expr, pos, "=="))
			return std::make_unique<Binary>(left.release(), parseComparision(expr, pos).release(), Binary::Operation::Eq);
		else if (match(expr, pos, "!="))
			return std::make_unique<Binary>(left.release(), parseComparision(expr, pos).release(), Binary::Operation::Neq);
		else if (match(expr, pos, "<="))
			return std::make_unique<Binary>(left.release(), parseComparision(expr, pos).release(), Binary::Operation::Le);
		else if (match(expr, pos, ">="))
			return std::make_unique<Binary>(left.release(), parseComparision(expr, pos).release(), Binary::Operation::Ge);
		else if (match(expr, pos, "<"))
			return std::make_unique<Binary>(left.release(), parseComparision(expr, pos).release(), Binary::Operation::Lt);
		else if (match(expr, pos, ">"))
			return std::make_unique<Binary>(left.release(), parseComparision(expr, pos).release(), Binary::Operation::Gt);
		else
			return left;

	}

	std::unique_ptr<Expression> parseLogicalAnd(std::string& expr, size_t& pos) {
		std::unique_ptr<Expression> left = parseComparision(expr, pos);

		skipWhiteChars(expr, pos);

		if (!match(expr, pos, "&&"))
			return left;

		std::unique_ptr<Expression> right = parseLogicalAnd(expr, pos);

		return std::make_unique<Binary>(left.release(), right.release(), Binary::Operation::And);
	}

	std::unique_ptr<Expression> parseLogicalOr(std::string& expr, size_t& pos) {
		std::unique_ptr<Expression> left = parseLogicalAnd(expr, pos);

		skipWhiteChars(expr, pos);

		if (!match(expr, pos, "||"))
			return left;

		std::unique_ptr<Expression> right = parseLogicalOr(expr, pos);

		return std::make_unique<Binary>(left.release(), right.release(), Binary::Operation::Or);
	}

	std::unique_ptr<Expression> parseAdditive(std::string& expr, size_t& pos) {
		std::unique_ptr<Expression> left = parseMultiplicative(expr, pos);

		skipWhiteChars(expr, pos);

		if (match(expr, pos, "+"))
			return std::make_unique<Binary>(left.release(), parseAdditive(expr, pos).release(), Binary::Operation::Add);
		else if (match(expr, pos, "-"))
			return std::make_unique<Binary>(left.release(), parseAdditive(expr, pos).release(), Binary::Operation::Sub);
		else
			return left;
	}

	std::unique_ptr<Expression> parseMultiplicative(std::string& expr, size_t& pos) {
		std::unique_ptr<Expression> left = parseUnary(expr, pos);

		skipWhiteChars(expr, pos);

		if (match(expr, pos, "*"))
			return std::make_unique<Binary>(left.release(), parseMultiplicative(expr, pos).release(), Binary::Operation::Mul);
		else if (match(expr, pos, "/"))
			return std::make_unique<Binary>(left.release(), parseMultiplicative(expr, pos).release(), Binary::Operation::Div);
		else if (match(expr, pos, "%"))
			return std::make_unique<Binary>(left.release(), parseMultiplicative(expr, pos).release(), Binary::Operation::Mod);
		else
			return left;
	}



	std::unique_ptr<Expression> parseUnary(std::string& expr, size_t& pos) {
		skipWhiteChars(expr, pos);

		if (match(expr, pos, "!"))
			return std::make_unique<Unary>(parseUnary(expr, pos), Unary::Operation::Not);
		else if (match(expr, pos, "-"))
			return std::make_unique<Unary>(parseUnary(expr, pos), Unary::Operation::Neg);
		else
			return parsePrimary(expr, pos);
	}

	std::unique_ptr<Expression> parsePrimary(std::string& expr, size_t& pos) {
		skipWhiteChars(expr, pos);

		std::unique_ptr<Expression> left;

		if (match(expr, pos, "(")) {
			pos++;
			left = parseCondition(expr, pos);

			skipWhiteChars(expr, pos);

			if (!match(expr, pos, ")"))
				throw std::runtime_error("Excepted ')' at " + std::to_string(pos));
		} else if (isdigit(expr[pos])) {
			int value = 0;
			while (pos < expr.size() && isdigit(expr[pos])) {
				value = value * 10 + (expr[pos] - '0');
				pos++;
			}
			left = std::make_unique<Const>(value);
		} else if (match(expr, pos, "n")) {
			left = std::make_unique<Var>();
		} else
			throw std::runtime_error("Unexcepted character at " + std::to_string(pos));

		return left;
	}
}