#include "tween.h"

struct tween tween_new(float from, float to, float duration)
{
    struct tween tween =
    {
        .from = from,
        .to = to,
        .duration = duration,
        .elapsed = 0.0f,
        .value = from,
        .is_complete = false
    };

    return tween;
}
void tween_free(struct tween* tween)
{
    tween->from = 0.0f;
    tween->to = 0.0f;
    tween->duration = 0.0f;
    tween->elapsed = 0.0f;
    tween->value = 0.0f;
    tween->is_complete = false;
}

void tween_tick(struct tween* tween, float delta)
{
    if (tween->is_complete)
        return;

    tween->elapsed += delta;

    if (tween->elapsed < tween->duration)
    {
        float p = tween->elapsed / tween->duration;
        tween->value = tween->from + (p * (tween->to - tween->from));
    }
    else
    {
        tween->elapsed = tween->duration;
        tween->value = tween->to;
        tween->is_complete = true;
    }
}
