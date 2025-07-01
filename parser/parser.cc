#include "parser.h"


std::unordered_map<std::string,Precedence> precedence_map =
{
    {EQUALITY,EQUALS},
    {INEQUALITY,EQUALS},

    {LT,LESSGREATER},
    {GT,LESSGREATER},

    {PLUS,SUM},
    {MINUS,SUM},

    {ASTERISK,PRODUCT},
    {SLASH,PRODUCT},
};

void Parser::nextToken()
{
    current_token_ = peek_token_;
    peek_token_ = lexer_->next_token();
}

std::shared_ptr<Program> Parser::parseProgram()
{
    std::shared_ptr<Program> program = std::make_shared<Program>();
    while (current_token_.Type != EOF)
    {
        std::shared_ptr<Statement> stmt = parseStatement();
        if (stmt != nullptr)
        {
            program->statements_.push_back(stmt);
        }
        nextToken();
    }
    return program;
}

std::shared_ptr<Statement> Parser::parseStatement()
{
    if (current_token_.Type == LET)
    {
        return praseLetStatement();
    }
    else if (current_token_.Type == RETURN)
    {
        return parseReturnStatement();
    }
    else
    {
        return parseExpressionStatement();
    }
}

std::shared_ptr<Statement> Parser::praseLetStatement()
{
    auto letStatement = std::make_shared<LetStatement>(current_token_);
    if (!expectToken(IDENT))
    {
        return nullptr;
    }

    letStatement->name_ = std::make_shared<Identifier>(current_token_);

    if (!expectToken(ASSIGN))
    {
        return nullptr;
    }

    while (!currentTokenIs(SEMICOLON))
    {
        nextToken();
    }
    return letStatement;
}

bool Parser::currentTokenIs(const std::string &token)
{
    if (current_token_.Type == token)
    {
        return true;
    }
    return false;
}

bool Parser::peekTokenIs(const std::string &token)
{
    if (peek_token_.Type == token)
    {
        return true;
    }
    return false;
}

bool Parser::expectToken(const std::string &token)
{
    if (peekTokenIs(token))
    {
        nextToken();
        return true;
    }
    peekError(token);
    return false;
}

std::vector<std::string> Parser::logErrors()
{
    return errors;
}

void Parser::peekError(const std::string &t)
{
    std::string error_message = "Expected : " + t + ", Got : " + peek_token_.Type;
    errors.push_back(error_message);
}

void Parser::noPrefixParseFnError(const std::string &t) {

    std::string error_message = "no prefix parse function for "+t+" found";
    errors.push_back(error_message);
}

std::shared_ptr<Statement> Parser::parseReturnStatement()
{
    auto stmt = std::make_shared<ReturnStatement>(current_token_);

    nextToken();

    if (!expectToken(SEMICOLON))
    {
        nextToken();
    }
    return stmt;
}

std::shared_ptr<ExpressionStatement> Parser::parseExpressionStatement()
{
    auto expressionStatement = std::make_shared<ExpressionStatement>(current_token_);

    expressionStatement->Expr = parseExpression(LOWEST);

    if (peekTokenIs(SEMICOLON))
        nextToken();
    return expressionStatement;
}

void Parser::registerPrefix(const std::string &token, prefixParseFn func)
{
    prefixParseFns[token] = func;
}
void Parser::registerInfix(const std::string &token, infixParseFn func)
{
    infixParseFns[token] = func;
}

std::shared_ptr<Expression> Parser::parseExpression(Precedence pre)
{
    auto prefix = prefixParseFns[current_token_.Type];
    if (prefix == nullptr){
        noPrefixParseFnError(current_token_.Literal);
        return nullptr;
    }
    auto leftExp = prefix();

    while(!peekTokenIs(SEMICOLON) && pre < peekPrecedence()){
        auto infixFn = infixParseFns[peek_token_.Type];
        if (infixFn == nullptr)
            return leftExp;
        nextToken();
        leftExp = infixFn(leftExp);
    }

    return leftExp;
}

std::shared_ptr<Expression> Parser::parseIdentifier()
{
    return std::make_shared<Identifier>(current_token_);
}

std::shared_ptr<Expression> Parser::parseIntegerLiteral()
{
    auto intExpr = std::make_shared<IntegerLiteral>(current_token_);

    try
    {
        intExpr->value_ = stoi(current_token_.Literal);
    }
    catch (const std::exception &e)
    {
        std::string intParseError = "Error while parsing string:"+current_token_.Literal +" as int.";
        errors.push_back(intParseError); 
        return 0;
    }
    return intExpr;
}


std::shared_ptr<Expression> Parser::parsePrefixExpression()
{
    auto prefixExpr = std::make_shared<PrefixExpression>(current_token_);
    prefixExpr->op = current_token_.Literal;

    nextToken();
    prefixExpr->right = parseExpression(PREFIX);
    return prefixExpr;
}

Precedence Parser::peekPrecedence()
{
    Precedence peek_precedence = precedence_map[peek_token_.Type];
    if (peek_precedence == 0)
    {
        return LOWEST;
    }
    return peek_precedence;
}

Precedence Parser::curPrecedence()
{
    Precedence current_precedence = precedence_map[current_token_.Type];
    if (current_precedence == 0)
    {
        return LOWEST;
    }
    return current_precedence;
}

std::shared_ptr<Expression> Parser::parseInfixExpression(std::shared_ptr<Expression> expr)
{
    std::shared_ptr<InfixExpression> infixExpr = std::make_shared<InfixExpression>(current_token_);
    infixExpr->left = expr;
    infixExpr->op = current_token_.Literal;

    Precedence current_token_precedence = curPrecedence();
    nextToken();
    infixExpr->right = parseExpression(current_token_precedence);
    return infixExpr;
}

std::shared_ptr<Expression> Parser::parseBooleanLiteral(){
    std::shared_ptr<BooleanLiteral> expr = std::make_shared<BooleanLiteral>(current_token_);
    if(current_token_.Type == TRUE){
       expr->value_ = true;
    } else {
      expr->value_ = false;
    }
    return expr;
}