#include "tween_sequence.h"

#include <assert.h>
#include <stdlib.h>

struct tween_sequence tween_sequence_new(void)
{
    struct tween_group* tween_groups = malloc(sizeof(*tween_groups));
    assert(tween_groups != NULL);

    struct tween_sequence tween_sequence =
    {
        .tween_groups = tween_groups,
        .count = 0,
        .capacity = 1,
        .index = 0,
        .is_complete = false
    };

    return tween_sequence;
}
void tween_sequence_free(struct tween_sequence* tween_sequence)
{
    if (tween_sequence->tween_groups)
    {
        for (size_t i = 0; i < tween_sequence->count; ++i)
        {
            tween_group_free(&tween_sequence->tween_groups[i]);
        }
        free(tween_sequence->tween_groups);
        tween_sequence->tween_groups = NULL;
    }
    tween_sequence->count = 0;
    tween_sequence->capacity = 0;
    tween_sequence->index = 0;
    tween_sequence->is_complete = false;
}

void tween_sequence_add(struct tween_sequence* tween_sequence, struct tween_group tween_group)
{
    if (tween_sequence->count == tween_sequence->capacity)
    {
        size_t new_capacity = tween_sequence->capacity * 2;
        struct tween_group* ptr = realloc(tween_sequence->tween_groups, sizeof(*ptr) * new_capacity);
        assert(ptr != NULL);
        tween_sequence->tween_groups = ptr;
        tween_sequence->capacity = new_capacity;
    }

    tween_sequence->tween_groups[tween_sequence->count++] = tween_group;
}

void tween_sequence_tick(struct tween_sequence* tween_sequence, float delta)
{
    if (tween_sequence->is_complete)
    {
        return;
    }

    struct tween_group* tween_group = &tween_sequence->tween_groups[tween_sequence->index];

    tween_group_tick(tween_group, delta);

    if (tween_group->is_complete)
    {
        if (++tween_sequence->index >= tween_sequence->count)
        {
            tween_sequence->is_complete = true;
        }
    }
}
