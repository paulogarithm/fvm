#ifndef _VMFUNC_H
    #define _VMFUNC_H

    #include "vmdef.h"

short get_size_to_read(s1_t byt);
void ld_data_manual(vm_t *vm, s2_t reg, s1_t byt, void *data);

int load(vm_t *vm, const char *filename);
void execute(vm_t *vm, int ptr);

#endif /* _VMFUNC_H */
