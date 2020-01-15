//
// Created by Kosho on 2020/1/16.
//

#include "meta_obj.h"
#include "class.h"
#include "vm.h"
#include "obj_fn.h"

/**
 * 创建空函数
 */
ObjFn* newObjFn(VM* vm, ObjModule* objModule, uint32_t slotNum) {
    ObjFn* objFn = ALLOCATE(vm, ObjFn);
    if (objFn == NULL) {
        MEM_ERROR("Failed to allocate ObjFn!");
    }
    initObjHeader(vm, &objFn->objHeader, OT_FUNCTION, vm->fnClass);
    ByteBufferInit(&objFn->instrStream);
    ValueBufferInit(&objFn->constants);
    objFn->module = objModule;
    objFn->maxStackSlotUsedNum = slotNum;
    objFn->upvalueNum = objFn->argNum = 0;
#ifdef DEBUG
    objFn->debug = ALLOCATE(vm, FnDebug);
    objFn->debug->fnName = NULL;
    IntBufferInit(&objFn->debug->lineNo);
#endif
    return objFn;
}

/**
 * 以函数fn创建一个闭包
 */
ObjClosure* newObjClosure(VM* vm, ObjFn* objFn) {
    ObjClosure* objClosure = ALLOCATE_EXTRA(vm, ObjClosure, sizeof(ObjUpvalue*) * objFn->upvalueNum);
    initObjHeader(vm, &objClosure->objHeader, OT_CLOSURE, vm->fnClass);
    objClosure->fn = objFn;

    // 显式初始化为NULL 避免GC闭包对象错误
    for (int i = 0; i < objFn->upvalueNum; i++) {
        objClosure->upvalues[i] = NULL;
    }

    return objClosure;
}

/**
 * 创建upvalue对象
 */
ObjUpvalue* newObjUpvalue(VM* vm, Value* localVarPtr) {
    ObjUpvalue* objUpvalue = ALLOCATE(vm, ObjUpvalue);
    initObjHeader(vm, &objUpvalue->objHeader, OT_UPVALUE, NULL);
    objUpvalue->localVarPtr = localVarPtr;
    objUpvalue->closedUpvalue = VT_TO_VALUE(VT_NULL);
    objUpvalue->next = NULL;
    return objUpvalue;
}