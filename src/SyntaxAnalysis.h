#pragma once

#define Syntax_ERR 1
using namespace antlr4;
class SyntaxAnalysis : public antlr4::tree::ParseTreeListener {
public:
    virtual void enterEveryRule(ParserRuleContext* ctx) override {}
    virtual void visitTerminal(tree::TerminalNode* node) override {}
    virtual void visitErrorNode(tree::ErrorNode* node) override {
        std::cout << "Err: Syntax: "<< node->getText() << std::endl;
        exit(Syntax_ERR);
    }
    virtual void exitEveryRule(ParserRuleContext* ctx) override {}
};
