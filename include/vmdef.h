#ifndef _VMDEF_H
    #define _VMDEF_H

    #include <stdint.h>

    #define SIZE_REG_BYTE size2_t
    #define LEN_REG __SHRT_MAX__ * 2

typedef uint8_t size1_t;
typedef uint16_t size2_t;
typedef uint32_t size4_t;
typedef uint64_t size8_t;

typedef struct s_vm vm_t;

#endif /* _VMDEF_H */
