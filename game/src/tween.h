#ifndef TWEEN_H
#define TWEEN_H

#include <stdbool.h>

struct tween
{
    float from;
    float to;
    float duration;
    float elapsed;
    float value;
    bool is_complete;
};

struct tween tween_new(float from, float to, float duration);
void tween_free(struct tween* tween);

void tween_tick(struct tween* tween, float delta);

#endif
