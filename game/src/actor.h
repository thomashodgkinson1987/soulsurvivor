#ifndef ACTOR_H
#define ACTOR_H

#include "sprite.h"

#include "raylib.h"

struct actor
{
    size_t tag;
    void* data;
};

struct actor_funcs
{
    void(*free)(struct actor* actor);
    void(*tick)(struct actor* actor, float delta);
    void(*draw)(struct actor* actor);
};

struct actor_vtable
{
    struct actor_funcs* items;
    size_t count;
    size_t capacity;
};

void actor_vtable_init(void);
void actor_vtable_free(void);
size_t actor_vtable_register(struct actor_funcs);

void actor_free(struct actor* actor);
void actor_tick(struct actor* actor, float delta);
void actor_draw(struct actor* actor);

struct actor_data
{
    float x;
    float y;
    float vx;
    float vy;
    struct sprite sprite;
};

size_t ACTOR_BASE_TAG;

struct actor actor(Texture2D texture);
void actor_base_free(struct actor* actor);
void actor_base_tick(struct actor* actor, float delta);
void actor_base_draw(struct actor* actor);

#endif
