#ifndef TWEEN_GROUP_H
#define TWEEN_GROUP_H

#include "tween.h"

#include <stddef.h>

struct tweens
{
    struct tween* items;
    size_t count;
    size_t capacity;
};

struct tween_group
{
    struct tweens tweens;
    bool is_complete;
};

struct tween_group tween_group_new(void);
void tween_group_free(struct tween_group* tween_group);

void tween_group_add(struct tween_group* tween_group, struct tween tween);

void tween_group_tick(struct tween_group* tween_group, float delta);

#endif
