//
// Created by Kosho on 2020/1/16.
//

#ifndef _OBJECT_FN_H
#define _OBJECT_FN_H

#include "utils.h"
#include "meta_obj.h"

/**
 * 函数的调试结构
 */
typedef struct {
    // 函数名
    char *fnName;
    // 行号
    IntBuffer lineNo;
} FnDebug;

/**
 * 函数对象
 */
typedef struct {
    ObjHeader objHeader;
    // 函数编译后的指令流
    ByteBuffer instrStream;
    // 函数中的常量表
    ValueBuffer constants;
    // 函数所属的模块
    ObjModule* module;
    // 函数最多需要的栈空间
    uint32_t maxStackSlotUsedNum;
    // 函数所涵盖的upvalue数量
    uint32_t upvalueNum;
    // 函数期望的参数个数
    uint8_t argNum;
#if DEBUG
    FnDebug* debug;
#endif
} ObjFn;

/**
 * upvalue对象
 */
typedef struct upvalue {
    ObjHeader objHeader;
    // 栈是个Value类型的数组,localVarPtr指向upvalue所关联的局部变量
    Value *localVarPtr;
    // 已被关闭的upvalue
    Value closedUpvalue;
    // 用以链接openUpvalue链表
    struct upvalue *next;
} ObjUpvalue;

/**
 * 闭包对象
 */
typedef struct {
    ObjHeader objHeader;
    // 闭包中所要引用的函数
    ObjFn *fn;
    // 用于存储此函数的 "close upvalue"
    ObjUpvalue *upvalues[0];
} ObjClosure;

/**
 * 调用栈帧
 */
typedef struct {
    // 程序计数器，指向下一条指令
    uint8_t *ip;

    // 在本frame中执行的闭包函数
    ObjClosure *closure;

    // frame共享thread.stack
    // 此项用于指向本frame所在thread运行时栈的起始地址
    Value *stackStart;
} Frame;

#define INITIAL_FRAME_NUM 4

ObjUpvalue *newObjUpvalue(VM *vm, Value *localVarPtr);

ObjClosure *newObjClosure(VM *vm, ObjFn *objFn);

ObjFn *newObjFn(VM *vm, ObjModule *objModule, uint32_t maxStackSlotUsedNum);

#endif
