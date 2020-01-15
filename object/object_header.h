//
// Created by Kosho on 2020/1/12.
//

#ifndef _OBJECT_HEADER_H
#define _OBJECT_HEADER_H

#include "utils.h"

/**
 * 对象类型
 */
typedef enum {
    OT_CLASS,
    OT_LIST,
    OT_MAP,
    OT_MODULE,
    OT_RANGE,
    OT_STRING,
    OT_UPVALUE,
    OT_FUNCTION,
    OT_CLOSURE,
    OT_INSTANCE,
    OT_THREAD
} ObjType;

/**
 * 对象头 <br/>
 * 用于记录元数据和GC
 */
typedef struct objHeader {
    ObjType type;
    // 对象是否可达
    bool isDark;
    // 对象所属的类
    Class* class;
    // 链接所有分配对象
    struct objHeader* next;
} ObjHeader;

/**
 * Value类型
 */
typedef enum {
    VT_UNDEFINED,
    VT_NULL,
    VT_FALSE,
    VT_TRUE,
    VT_NUM,
    VT_OBJ
} ValueType;

/**
 * Value
 */
typedef struct {
    ValueType type;
    union {
        double num;
        ObjHeader* objHeader;
    };
} Value;

DECLARE_BUFFER_TYPE(Value)

void initObjHeader(VM* vm, ObjHeader* objHeader, ObjType objType, Class* class);

#endif
