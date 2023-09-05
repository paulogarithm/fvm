#include <malloc.h>

#include "vm.h"

int load(vm_t *vm, const char *filename);
void execute(vm_t *vm, int ptr);

vm_t *create_new_vm(void)
{
    vm_t *self = (vm_t *)malloc(sizeof(vm_t));

    if (self == NULL)
        return NULL;
    self->pc = 0;
    self->mem = NULL;
    self->size = 0;
    self->map = malloc(sizeof(struct s_map));
    if (self->map == NULL)
        return NULL;
    self->map[0] = empty_map;
    self->load = load;
    self->execute = execute;
    for (unsigned i = 0; i < LEN_REG; ++i) {
        self->registers[i] = NULL;
        self->registersinfo[i] = 0;
    }
    self->status = 0;
    return self;
}
