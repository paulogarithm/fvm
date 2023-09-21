#include <stdio.h>

#include "vm.h"

void split_double(size4_t (*a)[], size8_t doublie)
{
    unsigned int n = (sizeof(doublie) * 2);

    (*a)[0] = (size4_t)(doublie >> n * 2);
    (*a)[1] = ((size4_t)(doublie << n) >> n);
}

void d__register(vm_t *vm, unsigned short n)
{
    size1_t byt = vm->registersinfo[n];
    bool is_neg = MASK(byt, 0b01000000);
    size4_t a[2] = {0};

    if (MASK(byt, 0b00000100) and not MASK(byt, 128))
        return DONT_CARE_RET printf("%s\n", MASK(byt, 1) ? "true" : "false");
    if (byt == 0b00000010)
        return DONT_CARE_RET printf("%s%d\n",
            is_neg ? "-" : "", *((int *)vm->registers[n]));
    if (byt == 0b00000011){
        split_double(&a, *((size8_t *)vm->registers[n]));
        return DONT_CARE_RET printf("%s%d.%d\n", is_neg ? "-" : "", a[0], a[1]);
    }
    return DONT_CARE_RET printf("0x%p\n", ((void *)vm->registers[n]));
}
