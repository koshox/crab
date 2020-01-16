//
// Created by Kosho on 2020/1/17.
//

#ifndef _OBJECT_RANGE_H
#define _OBJECT_RANGE_H

#include "class.h"

/**
 * range对象
 */
typedef struct {
    ObjHeader objHeader;
    // 范围起始
    int from;
    // 范围结束
    int to;
} ObjRange;

ObjRange *newObjRange(VM *vm, int from, int to);

#endif
