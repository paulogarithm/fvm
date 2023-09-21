#include <criterion/criterion.h>
#include "vm.h"

void push_data(vm_t *vm, void *data, size1_t byt);
void pop_register(vm_t *vm, unsigned short n);

Test(new_vm, pc_check) {
    vm_t *vm = vm_new();
    cr_assert_eq(vm->pc, 0, "Expected pc to be 0");
}

Test(new_vm, map_check) {
    vm_t *vm = vm_new();
    cr_assert_neq(vm->map, NULL, "Expected map to be non-null");
}

Test(stack, stack_stuff) {
    vm_t *vm = vm_new();
    size4_t n = 3;
    size1_t byt = 0b00000010;
    push_data(vm, &n, byt);
    pop_register(vm, 0);
    cr_assert_eq(*((int *)vm->registers[0]), 3, "Need to be the pushed val");
}
