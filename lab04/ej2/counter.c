#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>


#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter new_count = malloc(sizeof(struct _counter));
    new_count->count = 0;
    return new_count;
}

void counter_inc(counter c) {
    c->count = c->count + 1;
}

bool counter_is_init(counter c) {
    bool res;
    res = (c->count==0);
    return res;
}

void counter_dec(counter c) {
    assert(!(counter_is_init(c)));
    c->count = c->count - 1;
}

counter counter_copy(counter c) {
    counter new_count = malloc(sizeof(counter));
    new_count->count = c->count;
    return new_count;
}

void counter_destroy(counter c) {
    if (c!=NULL){
        free(c);
    }
}
