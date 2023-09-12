#include <malloc.h>
#include <string.h>

#include "vm.h"
#include "vmfunc.h"

vm_t *create_new_vm(void)
{
    vm_t *self = (vm_t *)malloc(sizeof(vm_t));

    if (self == NULL)
        return NULL;
    memcpy(self, &((vm_t){
        0, 0, NULL, 0,
        {NULL}, {0}, NULL, NULL,
        NULL, NULL
    }), sizeof(vm_t));
    self->map = malloc(sizeof(struct s_map));
    if (self->map == NULL)
        return NULL;
    self->map[0] = empty_map;
    self->load = load;
    self->execute = execute;
    return self;
}
