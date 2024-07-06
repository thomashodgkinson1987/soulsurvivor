#include "actor.h"

#include "mfn_dynamic_array.h"

#include <math.h>

static struct actor_vtable vtable = { 0 };

size_t ACTOR_BASE_TAG = 0;
size_t ACTOR_PLAYER_TAG = 0;

void actor_vtable_init(void)
{
    MFN_ARRAY_INIT(struct actor_funcs, &vtable);

    ACTOR_BASE_TAG = actor_vtable_register((struct actor_funcs)
    {
        .tick = NULL
    });

    ACTOR_PLAYER_TAG = actor_vtable_register((struct actor_funcs)
    {
        .tick = actor_player_tick
    });
}
void actor_vtable_free(void)
{
    MFN_ARRAY_FREE(&vtable);

    ACTOR_BASE_TAG = 0;
    ACTOR_PLAYER_TAG = 0;
}
size_t actor_vtable_register(struct actor_funcs funcs)
{
    size_t tag = vtable.count;

    MFN_ARRAY_APPEND(struct actor_funcs, &vtable, funcs);

    return tag;
}

struct actor actor_new(size_t tag, void* data, float x, float y, struct animated_sprite animated_sprite)
{
    struct actor actor =
    {
        .tag = tag,
        .data = data,
        .x = x,
        .y = y,
        .vx = 0.0f,
        .vy = 0.0f,
        .jump_height = 64.0f,
        .jump_limit = 1,
        .jump_count = 0,
        .gravity = 500.0f,
        .is_collision_down = false,
        .was_collision_down = false,
        .input_x = 0,
        .input_y = 0,
        .animated_sprite = animated_sprite
    };

    return actor;
}

void actor_free(struct actor* actor)
{
    actor->tag = 0;

    if (actor->data)
    {
        free(actor->data);
        actor->data = NULL;
    }

    actor->x = 0.0f;
    actor->y = 0.0f;

    actor->vx = 0.0f;
    actor->vy = 0.0f;

    actor->jump_height = 0.0f;
    actor->jump_limit = 0;
    actor->jump_count = 0;

    actor->gravity = 0.0f;

    actor->is_collision_down = false;
    actor->was_collision_down = false;

    actor->input_x = 0;
    actor->input_y = 0;

    actor->animated_sprite = (struct animated_sprite){ 0 };
}
void actor_tick(struct actor* actor, float delta)
{
    if (vtable.items[actor->tag].tick)
    {
        vtable.items[actor->tag].tick(actor, delta);
    }
}
void actor_draw(struct actor* actor)
{
    animated_sprite_draw(&actor->animated_sprite);
}

struct actor actor_player_new(float x, float y, struct animated_sprite animated_sprite)
{
    struct actor actor = actor_new(ACTOR_PLAYER_TAG, NULL, x, y, animated_sprite);

    return actor;
}
void actor_player_tick(struct actor* actor, float delta)
{
    actor->was_collision_down = actor->is_collision_down;
    actor->is_collision_down = false;

    //

    actor->input_x = 0;
    actor->input_y = 0;

    if (IsKeyDown(KEY_LEFT)) --actor->input_x;
    if (IsKeyDown(KEY_RIGHT)) ++actor->input_x;

    //

    actor->x += 4.0f * actor->input_x;

    //

    actor->vy += actor->gravity * delta / 2.0f;
    if (IsKeyPressed(KEY_SPACE) && actor->jump_count < actor->jump_limit)
    {
        ++actor->jump_count;
        actor->vy = -sqrtf(2.0f * actor->gravity * actor->jump_height);
    }
    actor->vy += actor->gravity * delta / 2.0f;

    //

    actor->x += actor->vx * delta;
    actor->y += actor->vy * delta;

    //

    if (actor->x < 0)
    {
        actor->x = 0.0f;
    }
    if (actor->x > GetScreenWidth() - 22.0f)
    {
        actor->x = GetScreenWidth() - 22.0f;
    }
    if (actor->y < 0)
    {
        actor->y = 0.0f;
        actor->vy = 0.0f;
    }
    if (actor->y > GetScreenHeight() - 22.0f)
    {
        actor->y = GetScreenHeight() - 22.0f;
        actor->vy = 0.0f;
        actor->jump_count = 0;
        actor->is_collision_down = true;
    }

    //

    if (!actor->is_collision_down)
    {
        animated_sprite_play(&actor->animated_sprite, "jump");
    }
    else if (actor->input_x == 0)
    {
        animated_sprite_play(&actor->animated_sprite, "idle");
    }
    else
    {
        animated_sprite_play(&actor->animated_sprite, "walk");
    }

    if (actor->input_x == -1)
    {
        actor->animated_sprite.is_flip_x = true;
    }
    else if (actor->input_x == 1)
    {
        actor->animated_sprite.is_flip_x = false;
    }

    //

    animated_sprite_tick(&actor->animated_sprite, delta);
    actor->animated_sprite.x = actor->x;
    actor->animated_sprite.y = actor->y;
}
