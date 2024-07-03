#ifndef TWEEN_H
#define TWEEN_H

#include <stdbool.h>

struct tween
{
    float* value;
    float from;
    float to;
    float duration;
    float elapsed;
    bool is_complete;
};

struct tween tween_new(float* value, float from, float to, float duration);
void tween_free(struct tween* tween);

void tween_tick(struct tween* tween, float delta);

#endif
