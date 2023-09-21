#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

#include "vm.h"
#include "vmfunc.h"

void dump_data(vm_t *vm)
{
    if (vm->mem != NULL) {
        printf("Data in vm->data: ");
        for (size_t i = 0; i < vm->size; ++i) {
            char c = ((char *)vm->mem)[i];
            printf("%c", (c < ' ' or c > '~') ? '.' : c);
        }
        printf("\n");
    } else
        printf("vm->data is NULL\n");
}

void dump_map(vm_t *vm)
{
    printf("Map contents: ");
    for (int i = 0; vm->map[i].begin < 0 or vm->map[i].end < 0; ++i)
        printf("(%d, %d) ", vm->map[i].begin, vm->map[i].end);
    printf("\n");
}

int disperr(vm_t *vm, const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    ERR(vm);
}

int main(int argc, char const *argv[])
{
    vm_t *vm = NULL;
    int ptr = 0;
    int ret = 0;

    if (argc < 2)
        return disperr(vm, "Need at least 1 argument");
    vm = vm_new();
    if (vm == NULL)
        return disperr(vm, "Memory error");
    ptr = vm_load(vm, argv[1]);
    if (ptr == -1)
        ERR(vm);
    vm_exe(vm, ptr);
    ret = vm->status;
    if (ret)
        ERRN(vm, ret);
    d__register(vm, 0);
    OK(vm);
}
