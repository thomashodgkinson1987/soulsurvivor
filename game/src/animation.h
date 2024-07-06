#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"

struct animation
{
    char* name;
    struct frames frames;
};

struct animations
{
    struct animation* items;
    size_t count;
    size_t capacity;
};

struct animation animation_new(char* name, struct frames frames);
void animation_free(struct animation* animation);

#endif
