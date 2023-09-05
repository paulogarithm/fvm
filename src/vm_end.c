#include <malloc.h>
#include <string.h>

#include "vm.h"

static void rem(struct s_map **a, int element)
{
    int index_to_remove = 0;

    for (int size = 0; (*a)[size].begin != -1; ++size) {
        if ((*a)[size].begin != element)
            continue;
        index_to_remove = size;
        for (; (*a)[index_to_remove + 1].begin != -1; ++index_to_remove)
            (*a)[index_to_remove] = (*a)[index_to_remove + 1];
        (*a)[index_to_remove].begin = -1;
        return;
    }
}

bool free_data(vm_t *vm, int index)
{
    if (vm->map == NULL || index < 0)
        return false;

    struct s_map current = empty_map;
    for (unsigned n = 0; vm->map[n].begin != -1; ++n)
        if (vm->map[n].begin == index)
            current = vm->map[n];
    if (current.begin == -1)
        return false;
    memset((char *)vm->mem + current.begin, 0, current.end - current.begin + 1);
    rem(&vm->map, index);
    return true;
}

static void free_registers(vm_t *vm)
{
    for (unsigned short n = 0; n < LEN_REG; ++n)
        if (vm->registers[n] != NULL)
            free(vm->registers[n]);
}

void destroy_vm(vm_t *vm)
{
    if (vm == NULL)
        return;
    free_registers(vm);
    if (vm->mem != NULL)
        free(vm->mem);
    if (vm->map != NULL)
        free(vm->map);
    if (vm != NULL)
        free(vm);
}
