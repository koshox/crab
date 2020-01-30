// 
// Created by Kosho on 2020/1/6.
// 

#ifndef _PARSER_PARSER_H
#define _PARSER_PARSER_H

#include "compiler.h"
#include "meta_obj.h"
#include "common.h"
#include "vm.h"

typedef enum {
    TOKEN_UNKNOWN,

    TOKEN_NUM,             // 数字    --- 数据类型
    TOKEN_STRING,          // 字符串
    TOKEN_ID,              // 变量名
    TOKEN_INTERPOLATION,   // 内嵌表达式


    TOKEN_VAR,             // 'var'   --- 关键字(系统保留字)
    TOKEN_FUN,             // 'fun'
    TOKEN_IF,              // 'if'
    TOKEN_ELSE,            // 'else'
    TOKEN_TRUE,            // 'true'
    TOKEN_FALSE,           // 'false'
    TOKEN_WHILE,           // 'while'
    TOKEN_FOR,             // 'for'
    TOKEN_BREAK,           // 'break'
    TOKEN_CONTINUE,        // 'continue'
    TOKEN_RETURN,          // 'return'
    TOKEN_NULL,            // 'null'

    TOKEN_CLASS,           // 'class' --- 关于类和模块导入的token
    TOKEN_THIS,            // 'this'
    TOKEN_STATIC,          // 'static'
    TOKEN_IS,              // 'is'
    TOKEN_SUPER,           // 'super'
    TOKEN_IMPORT,          // 'import'

    TOKEN_COMMA,           // ','     --- 分隔符
    TOKEN_COLON,           // ':'
    TOKEN_LEFT_PAREN,      // '('
    TOKEN_RIGHT_PAREN,     // ')'
    TOKEN_LEFT_BRACKET,    // '['
    TOKEN_RIGHT_BRACKET,   // ']'
    TOKEN_LEFT_BRACE,      // '{'
    TOKEN_RIGHT_BRACE,     // '}'
    TOKEN_DOT,             // '.'
    TOKEN_DOT_DOT,         // '..'

    TOKEN_ADD,             // '+'     --- 简单双目运算符
    TOKEN_SUB,             // '-'
    TOKEN_MUL,             // '*'
    TOKEN_DIV,             // '/'
    TOKEN_MOD,             // '%'

    TOKEN_ASSIGN,          // '='     --- 赋值运算符

    TOKEN_BIT_AND,         // '&'     --- 位运算符
    TOKEN_BIT_OR,          // '|'
    TOKEN_BIT_NOT,         // '~'
    TOKEN_BIT_SHIFT_RIGHT, // '>>'
    TOKEN_BIT_SHIFT_LEFT,  // '<<'

    TOKEN_LOGIC_AND,       // '&&'    --- 逻辑运算符
    TOKEN_LOGIC_OR,        // '||'
    TOKEN_LOGIC_NOT,       // '!'

    TOKEN_EQUAL,           // '=='    --- 关系操作符
    TOKEN_NOT_EQUAL,       // '!='
    TOKEN_GREATE,          // '>'
    TOKEN_GREATE_EQUAL,    // '>='
    TOKEN_LESS,            // '<'
    TOKEN_LESS_EQUAL,      // '<='

    TOKEN_QUESTION,        // '?'

    TOKEN_EOF              // 'EOF'   --- 文件结束标记, 仅词法分析时使用
} TokenType;

typedef struct {
    TokenType type;
    const char *start;
    uint32_t length;
    uint32_t lineNo;
    Value value;
} Token;

struct parser {
    const char *file;
    const char *sourceCode;
    const char *nextCharPtr;
    char curChar;

    Token curToken;
    Token preToken;

    ObjModule *curModule;                 // 当前编译模块
    CompileUnit *curCompileUnit;          // 当前编译单元

    int interpolationExpectRightParenNum; // 处于内嵌表达式之中时, 期望的右括号数量, 用于跟踪小括号对的嵌套
    struct parser *parent;                // 指向父parser
    VM *vm;
};

#define PEEK_TOKEN(parserPtr) parserPtr->curToken.type

char lookAheadChar(Parser *parser);

void getNextToken(Parser *parser);

bool matchToken(Parser *parser, TokenType expected);

void consumeCurToken(Parser *parser, TokenType expected, const char *errMsg);

void consumeNextToken(Parser *parser, TokenType expected, const char *errMsg);

uint32_t getByteNumOfEncodeUtf8(int value);

uint8_t encodeUtf8(uint8_t *buf, int value);

void initParser(VM *vm, Parser *parser, const char *file, const char *sourceCode, ObjModule *objModule);

#endif
