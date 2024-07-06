#ifndef ACTOR_H
#define ACTOR_H

#include "animated_sprite.h"

#include <stdbool.h>

struct actor
{
    size_t tag;
    void* data;

    float x;
    float y;

    float vx;
    float vy;

    float jump_height;
    size_t jump_limit;
    size_t jump_count;

    float gravity;

    bool is_collision_down;
    bool was_collision_down;

    int input_x;
    int input_y;

    struct animated_sprite animated_sprite;
};

struct actor_funcs
{
    void(*tick)(struct actor* actor, float delta);
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

extern size_t ACTOR_BASE_TAG;

struct actor actor_new(size_t tag, void* data, float x, float y, struct animated_sprite animated_sprite);
void actor_free(struct actor* actor);
void actor_tick(struct actor* actor, float delta);
void actor_draw(struct actor* actor);

extern size_t ACTOR_PLAYER_TAG;

struct actor actor_player_new(float x, float y, struct animated_sprite animated_sprite);
void actor_player_tick(struct actor* actor, float delta);

#endif
