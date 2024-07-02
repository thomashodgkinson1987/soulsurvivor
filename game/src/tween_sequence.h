#ifndef TWEEN_SEQUENCE_H
#define TWEEN_SEQUENCE_H

#include "tween_group.h"

struct tween_sequence
{
    struct tween_group* tween_groups;
    size_t count;
    size_t capacity;
    size_t index;
    bool is_complete;
};

struct tween_sequence tween_sequence_new(void);
void tween_sequence_free(struct tween_sequence* tween_sequence);

void tween_sequence_add(struct tween_sequence* tween_sequence, struct tween_group tween_group);

void tween_sequence_tick(struct tween_sequence* tween_sequence, float delta);

#endif
