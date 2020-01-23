//
// Created by Kosho on 2020/1/23.
//

#ifndef CRAB_OBJ_THREAD_H
#define CRAB_OBJ_THREAD_H

#include "obj_fn.h"

/**
 * 线程对象
 */
typedef struct objThread {
    ObjHeader objHeader;

    //运行时栈的栈底
    Value *stack;
    //运行时栈的栈顶
    Value *esp;
    //栈容量
    uint32_t stackCapacity;

    // 运行栈帧
    Frame *frames;
    // 已使用的frame数量
    uint32_t usedFrameNum;
    // frame容量
    uint32_t frameCapacity;

    // 打开的upvalue链表首结点
    ObjUpvalue *openUpvalues;

    // 当前thread的调用者
    struct objThread *caller;

    // 导致运行时错误的对象会放在此处,否则为空
    Value errorObj;
} ObjThread;

void prepareFrame(ObjThread *objThread, ObjClosure *objClosure, Value *stackStart);

ObjThread *newObjThread(VM *vm, ObjClosure *objClosure);

void resetThread(ObjThread *objThread, ObjClosure *objClosure);

#endif
