#ifndef _VM_H
    #define _VM_H

    #include <stdbool.h>
    #include <stddef.h>
    #include <iso646.h>
    #include <stdint.h>

typedef uint8_t s1_t;
typedef uint16_t s2_t;
typedef uint32_t s4_t;
typedef uint64_t s8_t;

typedef struct s_vm vm_t;

    #define SIZE_REG_BYTE s2_t
    #define LEN_REG __SHRT_MAX__ * 2

struct s_map {
    int begin;
    int end;
};

struct s_file {
    __ssize_t size;
    void *data;
};

struct s_vm {
    size_t pc;
    int status;
    void *mem;
    size_t size;

    void *registers[LEN_REG];
    s1_t registersinfo[LEN_REG];

    struct s_map *map;

    int (*load)(struct s_vm *, const char *);
    void (*execute)(struct s_vm *, int ptr);
};



vm_t *create_new_vm(void);
void destroy_vm(vm_t *vm);
s8_t read_bytes(vm_t *vm, unsigned num_bytes);

    #define vm_new() create_new_vm()
    #define vm_destroy(vm) destroy_vm(vm);
    #define vm_load(vm, filename) vm->load(vm, filename)
    #define vm_inc(vm, n) vm->pc += n
    #define vm_exe(vm, ptr) vm->execute(vm, ptr)
    #define vm_read(vm, n) read_bytes(vm, n)

    #define EXIT(vm, n) vm->status = n
    #define ERR(vm) do { vm_destroy(vm) return 42; } while (0)
    #define ERRN(vm, n) do { vm_destroy(vm) return n; } while (0)
    #define OK(vm) do { vm_destroy(vm) return 0; } while (0)

    #define empty_map ((struct s_map){-1, 0})
    #define errfile(errno) ((struct s_file){errno, NULL})

#endif /* _VM_H */