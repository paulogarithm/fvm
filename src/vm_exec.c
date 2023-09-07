#include <stdio.h>

#include "vm.h"
#include "vmerr.h"
#include "opcodes.h"

s8_t read_bytes(vm_t *vm, unsigned num_bytes)
{
    s8_t result = 0;

    for (unsigned i = 0; i < num_bytes; ++i) {
        result = (result << 8) | ((s1_t *)vm->mem)[vm->pc];
        vm_inc(vm, 1);
    }
    return result;
}

void execute(vm_t *vm, int ptr)
{
    s1_t opcode = 0x00;

    vm->pc = (size_t)ptr;
    do {
        if (vm->pc >= vm->size) {
            EXIT(vm, REACHEND);
            dprintf(2, "Out of memory\n");
            break;
        }
        opcode = ((s1_t *)vm->mem)[vm->pc];
        vm_inc(vm, 1);
        if (OPCODES[opcode] != NULL)
            OPCODES[opcode](vm);
    } while (opcode and (not vm->status));
}
