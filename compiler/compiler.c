//
// Created by Kosho on 2020/1/25.
//

#include "compiler.h"
#include "parser.h"
#include "core.h"
#include <string.h>

#if DEBUG
#include "debug.h"
#endif

/**
 * 编译单元
 */
struct compileUnit {
    ObjFn *fn;                             // 编译的函数
    LocalVar localVars[MAX_LOCAL_VAR_NUM]; // 作用域中允许的局部变量的个量上限
    uint32_t localVarNum;                  // 已分配的局部变量数
    Upvalue upvalues[MAX_UPVALUE_NUM];     // 本层函数所引用的upvalue
    int scopeDepth;                        // 当前正在编译的代码所处的作用域
    uint32_t stackSlotNum;                 // 当前使用的slot个数
    Loop *curLoop;                         // 当前正在编译的循环层
    ClassBookKeep *enclosingClassBK;       // 当前正编译的类的编译信息
    struct compileUnit *enclosingUnit;     // 包含此编译单元的编译单元,即直接外层
    Parser *curParser;                     // 当前parser
};

/**
 * 在模块中定义名为name,值为value的模块变量
 */
int defineModuleVar(VM *vm, ObjModule *objModule, const char *name, uint32_t length, Value value) {
    if (length > MAX_ID_LEN) {
        // 也许name指向的变量名并不以'\0'结束,将其从源码串中拷贝出来
        char id[MAX_ID_LEN] = {'\0'};
        memcpy(id, name, length);

        // 函数可能是在编译源码文件之前调用的, 那时还没有创建parser
        if (vm->curParser != NULL) {
            COMPILE_ERROR(vm->curParser,
                          "length of identifier \"%s\" should be no more than %d", id, MAX_ID_LEN);
        } else {
            MEM_ERROR("length of identifier \"%s\" should be no more than %d", id, MAX_ID_LEN);
        }
    }

    // 从模块变量名中查找变量,若不存在就添加
    int symbolIndex = getIndexFromSymbolTable(&objModule->moduleVarName, name, length);
    if (symbolIndex == -1) {
        // 添加变量名
        symbolIndex = addSymbol(vm, &objModule->moduleVarName, name, length);
        // 添加变量值
        ValueBufferAdd(vm, &objModule->moduleVarValue, value);

    } else if (VALUE_IS_NUM(objModule->moduleVarValue.datas[symbolIndex])) {
        // 若遇到之前预先声明的模块变量的定义，在此为其赋予正确的值
        // 变量在运行期赋值，编译期为VT_NULL，未定义则为行号
        objModule->moduleVarValue.datas[symbolIndex] = value;
    } else {
        //已定义则返回-1,用于判断重定义
        symbolIndex = -1;
    }

    return symbolIndex;
}

/**
 * 编译模块
 */
ObjFn *compileModule(VM *vm, ObjModule *objModule, const char *moduleCode) {
    // TODO
}
