#include <stdio.h>

#include "vm.h"

void split_double(s4_t (*a)[], s8_t doublie)
{
    unsigned int n = (sizeof(doublie) * 2);

    (*a)[0] = (s4_t)(doublie >> n * 2);
    (*a)[1] = ((s4_t)(doublie << n) >> n);
}

void register_debug(vm_t *vm, unsigned short n)
{
    s1_t byt = vm->registersinfo[n];
    bool is_neg = false;
    s4_t a[2] = {0};

    is_neg = MASK(byt, 0b01000000);
    if (MASK(byt, 0b00000100) and not MASK(byt, 128))
        return __idc_return printf("%s\n", MASK(byt, 1) ? "true" : "false");
    if (byt == 0b00000010)
        return __idc_return printf("%s%d\n",
            is_neg ? "-" : "", *((int *)vm->registers[n]));
    if (byt == 0b00000011){
        split_double(&a, *((s8_t *)vm->registers[n]));
        return __idc_return printf("%s%d.%d\n", is_neg ? "-" : "", a[0], a[1]);
    }
    return __idc_return printf("0x%p\n", ((void *)vm->registers[n]));
}
