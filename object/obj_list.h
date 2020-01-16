//
// Created by Kosho on 2020/1/16.
//

#ifndef _OBJECT_LIST_H
#define _OBJECT_LIST_H

#include "class.h"
#include "vm.h"

/**
 * List object
 */
typedef struct {
    ObjHeader objHeader;
    // list元素
    ValueBuffer elements;
} ObjList;

ObjList *newObjList(VM *vm, uint32_t elementNum);

void insertElement(VM *vm, ObjList *objList, uint32_t index, Value value);

Value removeElement(VM *vm, ObjList *objList, uint32_t index);

#endif
