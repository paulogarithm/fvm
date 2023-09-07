#include <malloc.h>

#include "vmerr.h"
#include "vm.h"

void push_register(vm_t *vm)
{
    s2_t __idc_argument reg = (s2_t)vm_read(vm, sizeof(SIZE_REG_BYTE));
    struct s_plate *p = new_plate;

    if (p == NULL)
        return __idc_return (EXIT(vm, NOMEMORY));
    p->previous = vm->stack;
    vm->stack = p;
}
