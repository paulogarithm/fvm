#include <criterion/criterion.h>
#include "vm.h"

Test(new_vm, pc_check) {
    vm_t *vm = vm_new();
    cr_assert_eq(vm->pc, 0, "Expected pc to be 0");
}

Test(new_vm, map_check) {
    vm_t *vm = vm_new();
    cr_assert_neq(vm->map, NULL, "Expected map to be non-null");
}

