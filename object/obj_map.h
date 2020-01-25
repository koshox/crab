//
// Created by Kosho on 2020/1/23.
//

#ifndef _OBJECT_MAP_H
#define _OBJECT_MAP_H

#include "object_header.h"

#define MAP_LOAD_PERCENT 0.8

typedef struct {
    Value key;
    Value value;
} Entry;

typedef struct {
    ObjHeader objHeader;
    // 容量
    uint32_t capacity;
    // 当前size
    uint32_t count;
    // Entry数组
    Entry *entries;
} ObjMap;

ObjMap *newObjMap(VM *vm);

void mapSet(VM *vm, ObjMap *objMap, Value key, Value value);

Value mapGet(ObjMap *objMap, Value key);

void clearMap(VM *vm, ObjMap *objMap);

Value removeKey(VM *vm, ObjMap *objMap, Value key);

#endif
