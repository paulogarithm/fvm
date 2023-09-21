#ifndef _VM_H
    #define _VM_H

    #include <stdbool.h>
    #include <stddef.h>
    #include <iso646.h>

    #include "vmdef.h"

struct s_map {
    int begin;
    int end;
};

struct s_file {
    long size;
    void *data;
};

struct s_plate {
    struct s_plate *previous;
    void *data;
    size1_t byt;
};

struct s_vm {
    size_t pc;
    int status;
    void *mem;
    size_t size;

    void *registers[LEN_REG];
    size1_t registersinfo[LEN_REG];
    struct s_plate *stack;
    struct s_map *map;

    int (*load)(struct s_vm *, const char *);
    void (*execute)(struct s_vm *, int ptr);
};

void d__register(vm_t *vm, unsigned short n);

    #ifndef _HAS_DESTROY
        void vm_destroy(vm_t *vm);
        #define _HAS_DESTROY
    #endif /* _HAS_DESTROY */

    #define vm_load(vm, filename) vm->load(vm, filename)
    #define vm_inc(vm, n) vm->pc += n
    #define vm_exe(vm, ptr) vm->execute(vm, ptr)

    #define MASK(a, b) ((a & b) == b)

    #define DONT_CARE_RET (void)
    #define DONT_CARE_ARG __attribute__((unused))

    #define EXIT(vm, n) vm->status = n
    #define ERR(vm) do { vm_destroy(vm); return 42; } while (0)
    #define ERRN(vm, n) do { vm_destroy(vm); return n; } while (0)
    #define OK(vm) do { vm_destroy(vm); return 0; } while (0)

    #define empty_map ((struct s_map){-1, 0})
    #define errfile(errno) ((struct s_file){errno, NULL})
    #define new_plate (struct s_plate *)malloc(sizeof(struct s_plate))

#endif /* _VM_H */
