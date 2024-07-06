#include "animation.h"

struct animation animation_new(char* name, struct frames frames)
{
    struct animation animation =
    {
        .name = name,
        .frames = frames
    };

    return animation;
}
void animation_free(struct animation* animation)
{
    animation->name = NULL;
    animation->frames = (struct frames){ 0 };
}
