#include "tween.h"

#include <stddef.h>

struct tween tween_new(float* value, float from, float to, float duration)
{
    struct tween tween =
    {
        .value = value,
        .from = from,
        .to = to,
        .duration = duration,
        .elapsed = 0.0f,
        .is_complete = false
    };

    return tween;
}
void tween_free(struct tween* tween)
{
    tween->value = NULL;
    tween->from = 0.0f;
    tween->to = 0.0f;
    tween->duration = 0.0f;
    tween->elapsed = 0.0f;
    tween->is_complete = false;
}

void tween_tick(struct tween* tween, float delta)
{
    if (tween->is_complete)
    {
        return;
    }

    tween->elapsed += delta;

    if (tween->elapsed < tween->duration)
    {
        float p = tween->elapsed / tween->duration;
        *tween->value = tween->from + (p * (tween->to - tween->from));
    }
    else
    {
        *tween->value = tween->to;
        tween->elapsed = tween->duration;
        tween->is_complete = true;
    }
}
