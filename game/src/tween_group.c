#include "tween_group.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct tween_group tween_group_new(void)
{
    struct tween* tweens = malloc(sizeof(*tweens));
    assert(tweens != NULL);

    struct tween_group tween_group =
    {
        .tweens = tweens,
        .count = 0,
        .capacity = 1,
        .is_complete = false
    };

    return tween_group;
}
void tween_group_free(struct tween_group* tween_group)
{
    if (tween_group->tweens)
    {
        free(tween_group->tweens);
        tween_group->tweens = NULL;
    }
    tween_group->count = 0;
    tween_group->capacity = 0;
    tween_group->is_complete = false;
}

void tween_group_add(struct tween_group* tween_group, struct tween tween)
{
    if (tween_group->count == tween_group->capacity)
    {
        size_t new_capacity = tween_group->capacity * 2;
        struct tween* ptr = realloc(tween_group->tweens, sizeof(*ptr) * new_capacity);
        assert(ptr != NULL);
        tween_group->tweens = ptr;
        tween_group->capacity = new_capacity;
    }

    tween_group->tweens[tween_group->count++] = tween;
}

void tween_group_tick(struct tween_group* tween_group, float delta)
{
    if (tween_group->is_complete)
    {
        return;
    }

    tween_group->is_complete = true;

    for (size_t i = 0; i < tween_group->count; ++i)
    {
        struct tween* tween = &tween_group->tweens[i];
        tween_tick(tween, delta);
        if (!tween->is_complete)
        {
            tween_group->is_complete = false;
        }
    }
}
