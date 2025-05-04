#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include "../token/token.h"
#include <memory>
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include <functional>
#include <unordered_map>

using prefixParseFn = std::function<std::shared_ptr<Expression>()>;
using infixParseFn = std::function<std::shared_ptr<Expression>(std::shared_ptr<Expression>)>;

enum Precedence
{
    LOWEST = 1,
    EQUALS,      // ==
    LESSGREATER, // > or <
    SUM,         // +
    PRODUCT,     // *
    PREFIX,      // -X or !X
    CALL         // myFunction(X)
};
class Parser
{
public:
    Parser(std::shared_ptr<Lexer> lexer) : lexer_{lexer}
    {
        this->nextToken();
        this->nextToken();
        registerPrefix(IDENT, std::bind(&Parser::parseIdentifier, this));
        registerPrefix(INT, std::bind(&Parser::parseIntegerLiteral, this));
    }
    std::shared_ptr<Program> parseProgram();
    std::vector<std::string> logErrors();

    std::unordered_map<std::string, prefixParseFn> prefixParseFns;
    std::unordered_map<std::string, infixParseFn> infixParseFns;

private:
    std::shared_ptr<Lexer> lexer_;
    Token current_token_;
    Token peek_token_;
    void nextToken();

    // CORE
    std::shared_ptr<Statement> parseStatement();
    std::shared_ptr<Statement> praseLetStatement();
    std::shared_ptr<Statement> parseReturnStatement();

    // CORE EXPRESSION
    std::shared_ptr<ExpressionStatement> parseExpressionStatement();
    std::shared_ptr<Expression> parseExpression(Precedence);

    // EXPRESSION FUNCTIONS ASSOCIATED WITH TOKENS
    std::shared_ptr<Expression> parseIdentifier();
    std::shared_ptr<Expression> parseIntegerLiteral();

    // EXPRESSION MAPPER
    void registerPrefix(const std::string &, prefixParseFn);
    void registerInfix(const std::string &, infixParseFn);

    // HELPERS
    bool currentTokenIs(const std::string &);
    bool peekTokenIs(const std::string &);
    bool expectToken(const std::string &);

    std::vector<std::string> errors;

    void peekError(const std::string &);
};

#endif