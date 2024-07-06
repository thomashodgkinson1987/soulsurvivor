#ifndef FRAME_H
#define FRAME_H

#include "raylib.h"

struct frame
{
    Texture2D texture;
    float duration;
};

struct frames
{
    struct frame* items;
    size_t count;
    size_t capacity;
};

struct frame frame_new(Texture2D texture, float duration);
void frame_free(struct frame* frame);

#endif
