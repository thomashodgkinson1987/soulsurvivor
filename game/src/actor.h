#ifndef ACTOR_H
#define ACTOR_H

#include "animated_sprite.h"

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

struct actor_data
{
    float x;
    float y;
    float vx;
    float vy;
    float jump_height;
    size_t jump_count;
    size_t jump_limit;
    float gravity;
    bool is_collision_down;
    bool was_collision_down;
    int input_x;
    int input_y;
    struct animated_sprite animated_sprite;
};

size_t ACTOR_BASE_TAG;

void actor_vtable_init(void);
void actor_vtable_free(void);
size_t actor_vtable_register(struct actor_funcs);

struct actor actor_new(float x, float y, float jump_height, size_t jump_limit, float gravity, struct animated_sprite animated_sprite);

void actor_free(struct actor* actor);
void actor_tick(struct actor* actor, float delta);
void actor_draw(struct actor* actor);

void actor_base_free(struct actor* actor);
void actor_base_tick(struct actor* actor, float delta);
void actor_base_draw(struct actor* actor);

#endif
