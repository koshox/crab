//
// Created by Kosho on 2020/1/14.
//

#ifndef _OBJECT_STRING_H
#define _OBJECT_STRING_H

#include "object_header.h"

typedef struct {
    ObjHeader objHeader;
    uint32_t hashCode;
    CharValue value;
} ObjString;

uint32_t hashString(const char *str, uint32_t length);

void hashObjString(ObjString *objString);

ObjString *newObjString(VM *vm, const char *str, uint32_t length);

#endif
