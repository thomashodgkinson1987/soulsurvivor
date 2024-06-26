#include "actor.h"

#include "sprite.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct actor_vtable vtable = { 0 };

void actor_vtable_init(void)
{
    struct actor_funcs* items = malloc(sizeof(*items));
    assert(items != NULL);
    memset(items, 0, sizeof(*items));

    vtable = (struct actor_vtable)
    {
        .items = items,
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

struct actor actor_new(struct animated_sprite animated_sprite)
{
    struct actor_data* data = malloc(sizeof(*data));
    assert(data != NULL);

    *data = (struct actor_data)
    {
        .x = 0.0f,
        .y = 0.0f,
        .vx = 0.0f,
        .vy = 0.0f,
        .animated_sprite = animated_sprite
    };

    struct actor actor =
    {
        .data = data,
        .tag = ACTOR_BASE_TAG
    };

    return actor;
}

void actor_base_free(struct actor* actor)
{
    struct actor_data* data = (struct actor_data*)actor->data;

    free(data);
}
void actor_base_tick(struct actor* actor, float delta)
{
    struct actor_data* data = (struct actor_data*)actor->data;

    int input_x = 0;

    if (IsKeyDown(KEY_LEFT)) --input_x;
    if (IsKeyDown(KEY_RIGHT)) ++input_x;

    if (input_x == 0)
    {
        animated_sprite_play(&data->animated_sprite, "idle");
    }
    else
    {
        data->x += 4.0f * input_x;
        animated_sprite_play(&data->animated_sprite, "walk");
        data->animated_sprite.is_flip_x = input_x == -1;
    }

    data->vy += 98.1f * delta;

    if (IsKeyPressed(KEY_SPACE))
    {
        data->vy = -120.0f;
    }

    data->x += data->vx * delta;
    data->y += data->vy * delta;

    if (data->x < 0) data->x = 0.0f;
    if (data->x > GetScreenWidth() - 22.0f) data->x = GetScreenWidth() - 22.0f;
    if (data->y < 0)
    {
        data->y = 0.0f;
        data->vy = 0.0f;
    }
    if (data->y > GetScreenHeight() - 22.0f)
    {
        data->y = GetScreenHeight() - 22.0f;
        data->vy = 0.0f;
    }

    animated_sprite_tick(&data->animated_sprite, delta);
    data->animated_sprite.x = (int)data->x;
    data->animated_sprite.y = (int)data->y;
}
void actor_base_draw(struct actor* actor)
{
    struct actor_data* data = (struct actor_data*)actor->data;

    animated_sprite_draw(&data->animated_sprite);
}
