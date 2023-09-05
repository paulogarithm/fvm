#ifndef _OPCODES_H
    #define _OPCODES_H

    #include "vm.h"

void ld_func(vm_t *vm);

typedef void (*func)(vm_t *);

func OPCODES[] = {
    [0] = NULL,
    ld_func,
    NULL
};

#endif /* _OPCODES_H */
