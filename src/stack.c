#include <malloc.h>
#include <string.h>

#include "vmerr.h"
#include "vm.h"
#include "vmfunc.h"

void push_data(vm_t *vm, void *data, size1_t byt)
{
    struct s_plate *p = new_plate;

    if (p == NULL)
        return DONT_CARE_RET (EXIT(vm, NO_MEMORY));
    p->previous = vm->stack;
    p->data = data;
    p->byt = byt;
    vm->stack = p;
}

void push_register(vm_t *vm)
{
    size2_t reg = (size2_t)vm_read(vm, 2);
    size1_t byt = vm->registersinfo[reg];
    short size = get_size_to_read(byt);

    if (size == -2)
        return DONT_CARE_RET (EXIT(vm, WEIRD_ERR));
    push_data(vm, vm->registers[reg], byt);
}

void pop_register(vm_t *vm, unsigned short n)
{
    struct s_plate *plate = vm->stack;

    ld_data_manual(vm, n, plate->byt, plate->data);
    vm->stack = vm->stack->previous;
    free(plate);
}
