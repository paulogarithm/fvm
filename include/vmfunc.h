#ifndef _VMFUNC_H
    #define _VMFUNC_H

    #include "vmdef.h"

short get_size_to_read(size1_t byt);
void ld_data_manual(vm_t *vm, size2_t reg, size1_t byt, void *data);

int load(vm_t *vm, const char *filename);
void execute(vm_t *vm, int ptr);

vm_t *vm_new(void);
size8_t vm_read(vm_t *vm, unsigned num_bytes);

    #ifndef _HAS_DESTROY
        void vm_destroy(vm_t *vm);
        #define _HAS_DESTROY
    #endif /* _HAS_DESTROY */

#endif /* _VMFUNC_H */
