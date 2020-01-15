//
// Created by Kosho on 2020/1/15.
//

#ifndef _OBJECT_META_OBJ_H
#define _OBJECT_META_OBJ_H

#include "obj_string.h"

/**
 * 模块对象
 */
typedef struct {
    ObjHeader objHeader;
    // 模块中的模块变量名
    SymbolTable moduleVarName;
    // 模块中的模块变量值
    ValueBuffer moduleValue;
    // 模块名
    ObjString *name;
} ObjModule;

/**
 * 对象实例
 */
typedef struct {
    ObjHeader objHeader;
    // 具体字段
    Value fields[0];
} ObjInstance;

ObjModule *newObjModule(VM *vm, const char *modName);

ObjInstance *newObjInstance(VM *vm, Class *class);

#endif