#ifndef _VMDEF_H
    #define _VMDEF_H

    #include <stdint.h>

    #define SIZE_REG_BYTE s2_t
    #define LEN_REG __SHRT_MAX__ * 2

typedef uint8_t s1_t;
typedef uint16_t s2_t;
typedef uint32_t s4_t;
typedef uint64_t s8_t;

typedef struct s_vm vm_t;

#endif /* _VMDEF_H */
