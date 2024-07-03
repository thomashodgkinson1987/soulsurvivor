#include "tween_group.h"

#include "mfn_dynamic_array.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct tween_group tween_group_new(void)
{
    struct tween_group tween_group =
    {
        .tweens = { 0 },
        .is_complete = false
    };

    MFN_ARRAY_INIT(struct tween, &tween_group.tweens);

    return tween_group;
}
void tween_group_free(struct tween_group* tween_group)
{
    MFN_ARRAY_FREE(&tween_group->tweens);
    tween_group->is_complete = false;
}

void tween_group_add(struct tween_group* tween_group, struct tween tween)
{
    MFN_ARRAY_APPEND(struct tween, &tween_group->tweens, tween);
}

void tween_group_tick(struct tween_group* tween_group, float delta)
{
    if (tween_group->is_complete)
    {
        return;
    }

    tween_group->is_complete = true;

    for (size_t i = 0; i < tween_group->tweens.count; ++i)
    {
        struct tween* tween = &tween_group->tweens.items[i];
        tween_tick(tween, delta);
        if (!tween->is_complete)
        {
            tween_group->is_complete = false;
        }
    }
}
