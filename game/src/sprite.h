#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

struct sprite
{
    size_t tag;
    void* data;
};

struct sprite_funcs
{
    void(*draw)(struct sprite* sprite);
    void(*free)(struct sprite* sprite);
};

struct sprite_vtable
{
    struct sprite_funcs* items;
    size_t count;
    size_t capacity;
};

struct sprite_data
{
    Texture2D texture;
    Rectangle source;
    Rectangle dest;
    Vector2 origin;
    float rotation;
    Color tint;
};

void sprite_vtable_init(void);
size_t sprite_vtable_register(struct sprite_funcs funcs);
void sprite_vtable_free(void);

size_t SPRITE_BASE_TAG;

struct sprite sprite_new(Texture2D texture);

void sprite_free(struct sprite* sprite);
void sprite_draw(struct sprite* sprite);

void sprite_base_free(struct sprite* sprite);
void sprite_base_draw(struct sprite* sprite);

#endif
