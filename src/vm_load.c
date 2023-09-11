#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "vm.h"

static struct s_file get_file_data(const char *filename)
{
    struct s_file res = {0, NULL};
    struct stat st = {};
    int fd = open(filename, O_RDONLY);
    long read_res = 0;

    if (stat(filename, &st) == -1)
        return errfile(errno);
    res.size = st.st_size;
    if (fd == -1)
        return errfile(errno);
    res.data = malloc(sizeof(char) * res.size);
    if (res.data == NULL)
        return errfile(errno);
    read_res = read(fd, res.data, res.size);
    if (read_res == -1) {
        free(res.data);
        return errfile(errno);
    }
    return res;
}

void push_map(struct s_map **a, struct s_map map)
{
    int size = 0;
    struct s_map *new = NULL;

    for (; (*a)[size].begin != -1; ++size);
    new = realloc(*a, (size + 2) * sizeof(struct s_map));
    if (new == NULL)
        return;
    new[size] = map;
    new[size + 1] = empty_map;
    *a = new;
}

int load_data(vm_t *vm, struct s_file filedata)
{
    size_t new_size = vm->size + filedata.size;
    unsigned int new_begin = 0;

    if (new_size > vm->size) {
        vm->mem = realloc(vm->mem, new_size);
        if (vm->mem == NULL) {
            fprintf(stderr, "No more data\n");
            return -1;
        }
        new_begin = vm->size;
        vm->size = new_size;
    } else
        new_begin = vm->size - filedata.size;
    memcpy((char *)vm->mem + new_begin, filedata.data, filedata.size);
    push_map(&vm->map,
        (struct s_map){new_begin, new_begin + filedata.size - 1});
    return new_begin;
}

int load(vm_t *vm, const char *filename)
{
    struct s_file f = get_file_data(filename);
    int ptr = 0;

    if (f.data == NULL) {
        fprintf(stderr, "%s\n", strerror(f.size));
        return -1;
    }
    ptr = load_data(vm, f);
    free(f.data);
    return ptr;
}
