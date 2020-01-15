//
// Created by Kosho on 2020/1/9.
//
#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "vm.h"
#include "core.h"
#include "parser.h"
#include "token.h"

static void runFile(const char *path) {
    const char *lastSlash = strrchr(path, '/');
    if (lastSlash != NULL) {
        char *root = (char *) malloc(lastSlash - path + 2);
        memcpy(root, path, lastSlash - path + 1);
        root[lastSlash - path + 1] = '\0';
        //rootDir = root;
    }

    VM *vm = newVM();
    const char *sourceCode = readFile(path);

    struct parser parser;
    // TODO 模块先临时写NULL
    initParser(vm, &parser, path, sourceCode, NULL);

    while (parser.curToken.type != TOKEN_EOF) {
        getNextToken(&parser);
        printf("%dL: %s [", parser.curToken.lineNo, tokenArray[parser.curToken.type]);
        uint32_t idx = 0;
        while (idx < parser.curToken.length) {
            printf("%c", *(parser.curToken.start + idx++));
        }

        printf("]\n");
    }
}

int main(int argc, const char **argv) {
    if (argc == 1) {

    } else {
        runFile(argv[1]);
    }
    return 0;
}