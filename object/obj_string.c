//
// Created by Kosho on 2020/1/14.
//

#include <stdlib.h>
#include <string.h>
#include "vm.h"
#include "utils.h"
#include "common.h"
#include "obj_string.h"

const uint32_t FNV_OFFSET_BASIS = 2166136261;
const uint32_t FNV_PRIME = 16777619;

/**
 * fnv-1a hash
 */
uint32_t hashString(const char *str, uint32_t length) {
    uint32_t hash = FNV_OFFSET_BASIS;
    for (int i = 0; i < length; i++) {
        hash ^= str[i];
        hash *= FNV_PRIME;
    }
    return hash;
}

/**
 * 为string计算哈希码并将值存储到string->hash
 */
void hashObjString(ObjString *objString) {
    objString->hashCode =
            hashString(objString->value.start, objString->value.length);
}

/**
 * 以str字符串创建ObjString对象,允许空串""
 */
ObjString *newObjString(VM *vm, const char *str, uint32_t length) {

    ASSERT(length == 0 || str != NULL, "str length don`t match str!");

    ObjString *objString = ALLOCATE_EXTRA(vm, ObjString, length + 1);

    if (objString != NULL) {
        initObjHeader(vm, &objString, OT_STRING, vm->stringClass);
        objString->value.length = length;

        // 支持空字符串: str为null,length为0
        // 如果非空则复制其内容
        if (length > 0) {
            memcpy(objString->value.start, str, length);
        }
        objString->value.start[length] = '\0';
        hashObjString(objString);
    } else {
        MEM_ERROR("Allocating ObjString failed!");
    }
    return objString;
}
