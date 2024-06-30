#include "actor.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct actor_vtable vtable = { 0 };

void actor_vtable_init(void)
{
    struct actor_funcs* vtable_items = malloc(sizeof(*vtable_items));
    assert(vtable_items != NULL);
    memset(vtable_items, 0, sizeof(*vtable_items));

    vtable = (struct actor_vtable)
    {
        .items = vtable_items,
        .count = 0,
        .capacity = 1
    };

    struct actor_funcs actor_base_funcs = (struct actor_funcs)
    {
        .free = actor_base_free,
        .tick = actor_base_tick,
        .draw = actor_base_draw
    };
    ACTOR_BASE_TAG = actor_vtable_register(actor_base_funcs);
}
void actor_vtable_free(void)
{
    free(vtable.items);
    vtable.items = NULL;
    vtable.count = 0;
    vtable.capacity = 0;
}
size_t actor_vtable_register(struct actor_funcs funcs)
{
    if (vtable.count == vtable.capacity)
    {
        struct actor_funcs* ptr = realloc(vtable.items, sizeof(*ptr) * vtable.capacity * 2);
        assert(ptr != NULL);
        memset(&ptr[vtable.count], 0, sizeof(*ptr) * vtable.capacity);
        vtable.items = ptr;
        vtable.capacity *= 2;
    }

    vtable.items[vtable.count] = funcs;

    return vtable.count++;
}

struct actor actor_new(float x, float y, float jump_height, size_t jump_limit, float gravity, struct animated_sprite animated_sprite)
{
    struct actor_data* data = malloc(sizeof(*data));
    assert(data != NULL);

    *data = (struct actor_data)
    {
        .x = x,
        .y = y,
        .vx = 0.0f,
        .vy = 0.0f,
        .jump_height = jump_height,
        .jump_limit = jump_limit,
        .jump_count = 0,
        .gravity = gravity,
        .is_collision_down = false,
        .was_collision_down = false,
        .input_x = 0,
        .input_y = 0,
        .animated_sprite = animated_sprite
    };

    struct actor actor =
    {
        .data = data,
        .tag = ACTOR_BASE_TAG
    };

    return actor;
}

void actor_free(struct actor* actor)
{
    vtable.items[actor->tag].free(actor);
}
void actor_tick(struct actor* actor, float delta)
{
    vtable.items[actor->tag].tick(actor, delta);
}
void actor_draw(struct actor* actor)
{
    vtable.items[actor->tag].draw(actor);
}

void actor_base_free(struct actor* actor)
{
    struct actor_data* data = (struct actor_data*)actor->data;

    free(data);
}
void actor_base_tick(struct actor* actor, float delta)
{
    struct actor_data* data = (struct actor_data*)actor->data;

    //

    data->was_collision_down = data->is_collision_down;
    data->is_collision_down = false;

    //

    data->input_x = 0;
    data->input_y = 0;

    if (IsKeyDown(KEY_LEFT)) --data->input_x;
    if (IsKeyDown(KEY_RIGHT)) ++data->input_x;

    //

    data->x += 4.0f * data->input_x;

    //

    data->vy += data->gravity * delta / 2.0f;
    if (IsKeyPressed(KEY_SPACE) && data->jump_count < data->jump_limit)
    {
        ++data->jump_count;
        data->vy = -sqrtf(2.0f * data->gravity * data->jump_height);
    }
    data->vy += data->gravity * delta / 2.0f;

    //

    data->x += data->vx * delta;
    data->y += data->vy * delta;

    //

    if (data->x < 0)
    {
        data->x = 0.0f;
    }
    if (data->x > GetScreenWidth() - 22.0f)
    {
        data->x = GetScreenWidth() - 22.0f;
    }
    if (data->y < 0)
    {
        data->y = 0.0f;
        data->vy = 0.0f;
    }
    if (data->y > GetScreenHeight() - 22.0f)
    {
        data->y = GetScreenHeight() - 22.0f;
        data->vy = 0.0f;
        data->jump_count = 0;
        data->is_collision_down = true;
    }

    //

    if (!data->is_collision_down)
    {
        animated_sprite_play(&data->animated_sprite, "jump");
    }
    else if (data->input_x == 0)
    {
        animated_sprite_play(&data->animated_sprite, "idle");
    }
    else
    {
        animated_sprite_play(&data->animated_sprite, "walk");
    }

    if (data->input_x == -1)
        data->animated_sprite.is_flip_x = true;
    else if (data->input_x == 1)
        data->animated_sprite.is_flip_x = false;

    //

    animated_sprite_tick(&data->animated_sprite, delta);
    data->animated_sprite.x = (int)data->x;
    data->animated_sprite.y = (int)data->y;
}
void actor_base_draw(struct actor* actor)
{
    struct actor_data* data = (struct actor_data*)actor->data;

    animated_sprite_draw(&data->animated_sprite);
}
