#include "../arraylist.h"
#include "../linear_allocator.h"
#include <assert.h>
#include <stdlib.h>

void tarraylist_init() {
    linear_allocator *alloc = linear_allocator_init(1024);
    ArrayList list;
    arraylist_init(&list, alloc, sizeof(int));

    assert(list.element_size == sizeof(int));
    assert(list.capacity == 4);
    assert(list.size == 0);
    assert(list.data != NULL);
    assert(list.allocator == alloc);

    arraylist_free(&list);
    linear_allocator_deinit(alloc);
}

void tarraylist_add() {
    linear_allocator *alloc = linear_allocator_init(1024);
    ArrayList list;
    arraylist_init(&list, alloc, sizeof(int));

    for (int i = 0; i < 5; i++) {
        arraylist_add(&list, &i);
    }
    assert(list.size == 5);
    assert(list.capacity == 8);

    for (int i = 0; i < 5; i++) {
        int *val = (int *)arraylist_get(&list, i);
        assert(*val == i);
    }

    arraylist_free(&list);
    linear_allocator_deinit(alloc);
}

void tarraylist_get() {
    linear_allocator *alloc = linear_allocator_init(1024);
    ArrayList list;
    arraylist_init(&list, alloc, sizeof(int));

    int a = 10, b = 20, c = 30;
    arraylist_add(&list, &a);
    arraylist_add(&list, &b);
    arraylist_add(&list, &c);

    assert(*(int *)arraylist_get(&list, 0) == 10);
    assert(*(int *)arraylist_get(&list, 1) == 20);
    assert(*(int *)arraylist_get(&list, 2) == 30);

    arraylist_free(&list);
    linear_allocator_deinit(alloc);
}

void tarraylist_delete() {
    linear_allocator *alloc = linear_allocator_init(1024);
    ArrayList list;
    arraylist_init(&list, alloc, sizeof(int));

    int a = 1, b = 2, c = 3;
    arraylist_add(&list, &a);
    arraylist_add(&list, &b);
    arraylist_add(&list, &c);

    arraylist_del(&list);
    assert(list.size == 2);
    assert(*(int *)arraylist_get(&list, 1) == 2);

    arraylist_del(&list);
    assert(list.size == 1);
    assert(*(int *)arraylist_get(&list, 0) == 1);

    arraylist_free(&list);
    linear_allocator_deinit(alloc);
}

void tarraylist_free() {
    linear_allocator *alloc = linear_allocator_init(1024);
    ArrayList list;
    arraylist_init(&list, alloc, sizeof(int));

    arraylist_add(&list, &alloc);
    arraylist_free(&list);

    assert(list.data == NULL);
    assert(list.size == 0);
    assert(list.capacity == 0);
    assert(list.allocator == NULL);

    linear_allocator_deinit(alloc);
}

void tarraylist_edge() {
    linear_allocator *alloc = linear_allocator_init(1024);
    ArrayList list;
    arraylist_init(&list, alloc, sizeof(int));

    arraylist_free(&list);
    linear_allocator_deinit(alloc);
}

int main() {
    tarraylist_init();
    tarraylist_add();
    tarraylist_get();
    tarraylist_delete();
    tarraylist_free();
    tarraylist_edge();
    return 0;
}
