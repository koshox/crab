//
// Created by Kosho on 2020/1/16.
//

#include "obj_list.h"

/**
 * 新建list对象
 */
ObjList *newObjList(VM *vm, uint32_t elementNum) {

    Value *elementArray = NULL;

    if (elementNum > 0) {
        elementArray = ALLOCATE_ARRAY(vm, Value, elementNum);
    }

    ObjList *objList = ALLOCATE(vm, ObjList);

    objList->elements.datas = elementArray;
    objList->elements.capacity = objList->elements.count = elementNum;
    initObjHeader(vm, &objList->objHeader, OT_LIST, vm->listClass);
    return objList;
}

/**
 * 在index初插入元素
 */
void insertElement(VM *vm, ObjList *objList, uint32_t index, Value value) {
    if (index > objList->elements.count - 1) {
        RUN_ERROR("index out bounded!");
    }

    // 增加一个空位
    ValueBufferAdd(vm, &objList->elements, VT_TO_VALUE(VT_NULL));

    // index后面的元素整体后移一位
    uint32_t idx = objList->elements.count - 1;
    while (idx > index) {
        objList->elements.datas[idx] = objList->elements.datas[idx - 1];
        idx--;
    }

    // 插入Value
    objList->elements.datas[index] = value;
}

// 调整list容量
void shrinkList(VM *vm, ObjList *objList, uint32_t newCapacity) {
    uint32_t oldSize = objList->elements.capacity * sizeof(Value);
    uint32_t newSize = newCapacity * sizeof(Value);
    memManager(vm, objList->elements.datas, oldSize, newSize);
    objList->elements.capacity = newCapacity;
}

/**
 * 删除index处元素
 */
Value removeElement(VM *vm, ObjList *objList, uint32_t index) {
    Value valueToRemove = objList->elements.datas[index];

    // index后面的元素整体前移一位
    uint32_t idx = index;
    while (idx < objList->elements.count) {
        objList->elements.datas[idx] = objList->elements.datas[idx + 1];
        idx++;
    }

    // 若容量利用率过低减小容量
    uint32_t capacity = objList->elements.capacity / CAPACITY_GROW_FACTOR;
    if (capacity > objList->elements.count) {
        shrinkList(vm, objList, capacity);
    }

    objList->elements.count--;
    return valueToRemove;
}

