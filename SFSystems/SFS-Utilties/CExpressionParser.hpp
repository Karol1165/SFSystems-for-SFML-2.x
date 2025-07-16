#pragma once
#ifndef CPARSER_HPP_
#define CPARSER_HPP_
#include <string>
#include <memory>
#include "Parser.hpp"
#include "framework.h"

namespace SFS {

	namespace CExpressionParser
	{
		using namespace SFS::Parser;
		using std::move;


		struct Expression {
		public:
			virtual int64_t evaluate(int64_t) const = 0;
			virtual ~Expression() = default;
		};

		struct Const : public Expression {
			int value;
		public:
			Const(int v) : value(v) {}
			int64_t evaluate(int64_t) const override { return value; }
		};

		struct Var : public Expression {
		public:
			int64_t evaluate(int64_t x) const override { return x; }
		};

		struct Unary : public Expression {
			std::unique_ptr<Expression> operand;
		public:
			enum class Operation { Neg, Not } op;

			Unary(std::unique_ptr<Expression> op, Operation opType) : op(opType) { this->operand = std::move(op); }

			int64_t evaluate(int64_t x) const override;
		};

		struct Binary : public Expression {
			std::unique_ptr<Expression> left;
			std::unique_ptr<Expression> right;
		public:

			enum class Operation { Add, Sub, Mul, Div, Mod, Eq, Neq, Lt, Gt, Le, Ge, And, Or } op;

			Binary(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r, Operation op) : op(op) {
				this->left = std::move(l);
				this->right = std::move(r);
			}

			int64_t evaluate(int64_t x) const override;
		};

		struct Condition : public Expression {
			std::unique_ptr<Expression> condition;
			std::unique_ptr<Expression> trueExpr;
			std::unique_ptr<Expression> falseExpr;
		public:

			Condition(std::unique_ptr<Expression> cond, std::unique_ptr<Expression> trueExpr, std::unique_ptr<Expression> falseExpr) {
				this->condition = std::move(cond);
				this->trueExpr = std::move(trueExpr);
				this->falseExpr = std::move(falseExpr);
			}

			int64_t evaluate(int64_t x) const override;
		};

		SFS_U_API std::unique_ptr<Expression> parseExpression(const std::string& expr);

		std::unique_ptr<Expression> parseCondition(const std::string& expr, size_t& pos);
		std::unique_ptr<Expression> parseComparision(const std::string& expr, size_t& pos);
		std::unique_ptr<Expression> parseLogicalAnd(const std::string& expr, size_t& pos);
		std::unique_ptr<Expression> parseLogicalOr(const std::string& expr, size_t& pos);
		std::unique_ptr<Expression> parseAdditive(const std::string& expr, size_t& pos);
		std::unique_ptr<Expression> parseMultiplicative(const std::string& expr, size_t& pos);
		std::unique_ptr<Expression> parseUnary(const std::string& expr, size_t& pos);
		std::unique_ptr<Expression> parsePrimary(const std::string& expr, size_t& pos);

	}
}

#endif