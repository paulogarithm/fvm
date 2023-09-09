#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "vmerr.h"
#include "vm.h"

short get_size_to_read(s1_t byt)
{
    s1_t bool_mask = 0b00000100;
    s1_t cutsom_mask = 0b10000000;

    if (MASK(byt, cutsom_mask))
        return byt - cutsom_mask;
    if (MASK(byt, bool_mask) or byt == 0)
        return 0;
    if (byt == 1)
        return -1;
    switch (byt) {
        case 2:
        return sizeof(s4_t);
        break;
        case 3:
        return sizeof(s8_t);
        break;
        default:
        return 0;
    }
    return -2;
}

void ld_data_manual(vm_t *vm, s2_t reg, s1_t byt, void *data)
{
    short rd = get_size_to_read(byt);

    if (rd == -2)
        return __idc_return (EXIT(vm, WEIRD_ERR));
    vm->registersinfo[reg] = byt;
    if (vm->registers[reg] != NULL) {
        free(vm->registers[reg]);
        vm->registers[reg] = NULL;
    }
    if (rd == 0)
        return;
    if (rd == -1)
        return;
    vm->registers[reg] = malloc(rd * sizeof(s1_t));
    if (vm->registers[reg] == NULL)
        return __idc_return (EXIT(vm, NO_MEMORY));
    memcpy(vm->registers[reg], data, rd * sizeof(s1_t));
}

static void ld_data(vm_t *vm, s2_t reg, short rd)
{
    void *data = (void *)vm_read(vm, rd);

    if (rd == -1)
        return;
    vm->registers[reg] = malloc(rd * sizeof(s1_t));
    if (vm->registers[reg] == NULL)
        return __idc_return (EXIT(vm, NO_MEMORY));
    memcpy(vm->registers[reg], &data, rd * sizeof(s1_t));
}

/**
 * LD <REG:REG_SIZE> <BYT:1> <VAL:???>
**/
void ld_func(vm_t *vm)
{
    s2_t reg = (s2_t)vm_read(vm, sizeof(SIZE_REG_BYTE));
    s1_t byt = (s1_t)vm_read(vm, 1);
    short rd = get_size_to_read(byt);

    if (rd == -2)
        return __idc_return (EXIT(vm, WEIRD_ERR));
    vm->registersinfo[reg] = byt;
    if (vm->registers[reg] != NULL) {
        free(vm->registers[reg]);
        vm->registers[reg] = NULL;
    }
    if (rd == 0)
        return;
    ld_data(vm, reg, rd);
}
