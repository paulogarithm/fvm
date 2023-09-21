#include <stdio.h>

#include "vm.h"
#include "vmerr.h"
#include "opcodes.h"

size8_t vm_read(vm_t *vm, unsigned num_bytes)
{
    size8_t result = 0;

    for (unsigned i = 0; i < num_bytes; ++i) {
        result = (result << 8) | ((size1_t *)vm->mem)[vm->pc];
        vm_inc(vm, 1);
    }
    return result;
}

void execute(vm_t *vm, int ptr)
{
    size1_t opcode = 0x00;

    vm->pc = (size_t)ptr;
    do {
        if (vm->pc >= vm->size) {
            EXIT(vm, REACH_END);
            fprintf(stderr, "Out of memory\n");
            break;
        }
        opcode = ((size1_t *)vm->mem)[vm->pc];
        vm_inc(vm, 1);
        if (OPCODES[opcode] != NULL)
            OPCODES[opcode](vm);
    } while (opcode and (not vm->status));
}
