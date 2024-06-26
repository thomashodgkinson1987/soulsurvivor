#include "animated_sprite.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct animated_sprite animated_sprite_new(void)
{
    struct frame* items = malloc(sizeof(*items));
    assert(items != NULL);
    memset(items, 0, sizeof(*items));

    struct frames frames =
    {
        .items = items,
        .count = 0,
        .capacity = 1
    };

    struct animated_sprite animated_sprite =
    {
        .x = 0,
        .y = 0,
        .is_playing = true,
        .frames = frames,
        .current_index = 0,
        .elapsed_time = 0.0f
    };

    return animated_sprite;
}
void animated_sprite_free(struct animated_sprite* animated_sprite)
{
    animated_sprite->x = 0;
    animated_sprite->y = 0;

    free(animated_sprite->frames.items);
    animated_sprite->frames.items = NULL;
    animated_sprite->frames.count = 0;
    animated_sprite->frames.capacity = 0;

    animated_sprite->current_index = 0;
    animated_sprite->elapsed_time = 0.0f;
}

void animated_sprite_add_frame(struct animated_sprite* animated_sprite, Texture2D texture, float duration)
{
    if (animated_sprite->frames.count == animated_sprite->frames.capacity)
    {
        struct frame* ptr = realloc(animated_sprite->frames.items, sizeof(*ptr) * animated_sprite->frames.capacity * 2);
        assert(ptr != NULL);
        memset(&ptr[animated_sprite->frames.count], 0, sizeof(*ptr) * animated_sprite->frames.capacity);
        animated_sprite->frames.items = ptr;
        animated_sprite->frames.capacity *= 2;
    }

    struct frame frame =
    {
        .texture = texture,
        .duration = duration
    };

    animated_sprite->frames.items[animated_sprite->frames.count++] = frame;
}

void animated_sprite_tick(struct animated_sprite* animated_sprite, float delta)
{
    if (!animated_sprite->is_playing) return;

    animated_sprite->elapsed_time += delta;

    while (animated_sprite->elapsed_time >= animated_sprite->frames.items[animated_sprite->current_index].duration)
    {
        animated_sprite->elapsed_time -= animated_sprite->frames.items[animated_sprite->current_index].duration;
        ++animated_sprite->current_index;
        if (animated_sprite->current_index == animated_sprite->frames.count)
        {
            animated_sprite->current_index = 0;
        }
    }
}
void animated_sprite_draw(struct animated_sprite* animated_sprite)
{
    Texture texture = animated_sprite->frames.items[animated_sprite->current_index].texture;
    int x = animated_sprite->x;
    int y = animated_sprite->y;
    Color tint = WHITE;
    DrawTexture(texture, x, y, tint);
}

void animated_sprite_reset(struct animated_sprite* animated_sprite)
{
    animated_sprite->is_playing = true;
    animated_sprite->current_index = 0;
    animated_sprite->elapsed_time = 0.0f;
}
