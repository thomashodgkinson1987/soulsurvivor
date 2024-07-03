#include "tween_sequence.h"

#include "mfn_dynamic_array.h"

#include <assert.h>
#include <stdlib.h>

struct tween_sequence tween_sequence_new(void)
{
    struct tween_sequence tween_sequence =
    {
        .tween_groups = { 0 },
        .index = 0,
        .is_complete = false
    };

    MFN_ARRAY_INIT(struct tween_group, &tween_sequence.tween_groups);

    return tween_sequence;
}
void tween_sequence_free(struct tween_sequence* tween_sequence)
{
    for (size_t i = 0; i < tween_sequence->tween_groups.count; ++i)
    {
        tween_group_free(&tween_sequence->tween_groups.items[i]);
    }

    MFN_ARRAY_FREE(&tween_sequence->tween_groups);

    tween_sequence->index = 0;
    tween_sequence->is_complete = false;
}

void tween_sequence_add(struct tween_sequence* tween_sequence, struct tween_group tween_group)
{
    MFN_ARRAY_APPEND(struct tween_group, &tween_sequence->tween_groups, tween_group);
}

void tween_sequence_tick(struct tween_sequence* tween_sequence, float delta)
{
    if (tween_sequence->is_complete)
    {
        return;
    }

    struct tween_group* tween_group = &tween_sequence->tween_groups.items[tween_sequence->index];

    tween_group_tick(tween_group, delta);

    if (tween_group->is_complete)
    {
        if (++tween_sequence->index == tween_sequence->tween_groups.count)
        {
            tween_sequence->is_complete = true;
        }
    }
}
