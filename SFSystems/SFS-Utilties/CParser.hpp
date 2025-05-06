#pragma once
#ifndef CPARSER_HPP_
#define CPARSER_HPP_
#include <string>
#include <memory>

namespace SFS::CParser
{

	struct Expression {
		virtual int evaluate(int) const = 0;
		virtual ~Expression() = default;
	};
	
	struct Const : public Expression {
		int value;
		Const(int v) : value(v) {}
		int evaluate(int) const override { return value; }
	};
	
	struct Var : public Expression {
		int evaluate(int x) const override { return x; }
	};

	struct Unary : public Expression {
		std::unique_ptr<Expression> operand;
		enum class Operation { Neg, Not } op;

		Unary(std::unique_ptr<Expression> op, Operation opType) : operand(op), op(opType) {}

		int evaluate(int x) const override;
	};
	
	struct Binary : public Expression {
		std::unique_ptr<Expression> left;
		std::unique_ptr<Expression> right;
	
		enum class Operation { Add, Sub, Mul, Div, Mod, Eq, Neq, Lt, Gt, Le, Ge, And, Or } op;
	
		Binary(Expression* l, Expression* r, Operation op) : left(l), right(r), op(op) {}
	
		int evaluate(int x) const override;
	};
	
	struct Condition : public Expression {
		std::unique_ptr<Expression> condition;
		std::unique_ptr<Expression> trueExpr;
		std::unique_ptr<Expression> falseExpr;

		Condition(Expression* cond, Expression* trueExpr, Expression* falseExpr)
			: condition(cond), trueExpr(trueExpr), falseExpr(falseExpr) {}

		int evaluate(int x) const override;
	};

	void skipWhiteChars(std::string& str, size_t& index) {
		while (index < str.size() && (str[index] == ' ' || str[index] == '\t' || str[index] == '\n')) {
			index++;
		}
	}

	bool match(std::string& str, size_t& index, const std::string& pattern);
	
	std::unique_ptr<Expression> parseExpression(std::string& expr, size_t& pos);

	std::unique_ptr<Expression> parseCondition(std::string& expr, size_t& pos);
	std::unique_ptr<Expression> parseComparision(std::string& expr, size_t& pos);
	std::unique_ptr<Expression> parseLogicalAnd(std::string& expr, size_t& pos);
	std::unique_ptr<Expression> parseLogicalOr(std::string& expr, size_t& pos);
	std::unique_ptr<Expression> parseAdditive(std::string& expr, size_t& pos);
	std::unique_ptr<Expression> parseMultiplicative(std::string& expr, size_t& pos);
	std::unique_ptr<Expression> parseUnary(std::string& expr, size_t& pos);
	std::unique_ptr<Expression> parsePrimary(std::string& expr, size_t& pos);

}

#endif