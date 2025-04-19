#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include <memory>

TEST(AST, AstStructureTest)
{

    // Let x = y;

    std::shared_ptr<Program> program = std::make_shared<Program>();
    std::shared_ptr<LetStatement> letStatement = std::make_shared<LetStatement>(Token{LET, "let"});
    std::shared_ptr<Identifier> ident1 = std::make_shared<Identifier>(Token{IDENT, "x"});
    std::shared_ptr<Identifier> ident2 = std::make_shared<Identifier>(Token{IDENT, "y"});

    letStatement->name_ = ident1;
    letStatement->value_ = ident2;

    program->statements_.push_back(letStatement);

    if (program->String() != "let x = y;")
        FAIL() << "program.String() output expected: let x = y; got: " << program->String() << std::endl;
}
