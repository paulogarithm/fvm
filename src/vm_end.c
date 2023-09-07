#include <malloc.h>
#include <string.h>

#include "vm.h"

static void free_registers(vm_t *vm)
{
    for (unsigned short n = 0; n < LEN_REG; ++n)
        if (vm->registers[n] != NULL)
            free(vm->registers[n]);
}

static void free_stack(vm_t *vm)
{
    struct s_plate *p = vm->stack;

    while (p != NULL) {
        if (p->data != NULL)
            free(p->data);
        p = p->previous ;
        free(p);
    }
}

void destroy_vm(vm_t *vm)
{
    if (vm == NULL)
        return;
    free_registers(vm);
    free_stack(vm);
    if (vm->mem != NULL)
        free(vm->mem);
    if (vm->map != NULL)
        free(vm->map);
    if (vm != NULL)
        free(vm);
}
