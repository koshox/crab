//
// Created by Kosho on 2019/8/12.
//

#include <stdlib.h>
#include "vm.h"
#include "utils.h"

//初始化虚拟机
void initVM(VM* vm) {
    vm->allocatedBytes = 0;
    vm->curParser = NULL;
}

VM* newVM() {
    VM* vm = (VM*)malloc(sizeof(VM));
    if (vm == NULL) {
        MEM_ERROR("allocate VM failed!");
    }
    initVM(vm);
    return vm;
}
