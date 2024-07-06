#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

struct sprite
{
    float x;
    float y;

    Texture2D texture;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;

    bool is_flip_x;
    bool is_flip_y;
};

struct sprite sprite_new(Texture2D texture);
void sprite_free(struct sprite* sprite);
void sprite_draw(struct sprite* sprite);

#endif
