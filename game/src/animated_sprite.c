#include "animated_sprite.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct animated_sprite animated_sprite_new(int x, int y)
{
    struct animation* animations_items = malloc(sizeof(*animations_items));
    assert(animations_items != NULL);
    memset(animations_items, 0, sizeof(*animations_items));
    struct animations animations =
    {
        .items = animations_items,
        .count = 0,
        .capacity = 1
    };

    struct animated_sprite animated_sprite =
    {
        .x = x,
        .y = y,
        .tint = WHITE,
        .is_playing = true,
        .animations = animations,
        .current_animation_index = 0,
        .elapsed_time = 0.0f
    };

    return animated_sprite;
}
void animated_sprite_free(struct animated_sprite* animated_sprite)
{
    animated_sprite->x = 0;
    animated_sprite->y = 0;

    animated_sprite->tint = BLANK;

    animated_sprite->is_playing = false;

    for (size_t i = 0; i < animated_sprite->animations.count; ++i)
    {
        struct animation* animation = &animated_sprite->animations.items[i];
        struct frame* frames_items = animation->frames.items;
        free(frames_items);
    }

    free(animated_sprite->animations.items);
    animated_sprite->animations.items = NULL;
    animated_sprite->animations.count = 0;
    animated_sprite->animations.capacity = 0;

    animated_sprite->current_animation_index = 0;
    animated_sprite->elapsed_time = 0.0f;
}

void animated_sprite_create_animation(struct animated_sprite* animated_sprite, char* animation_name)
{
    if (animated_sprite->animations.count == animated_sprite->animations.capacity)
    {
        struct animation* ptr = realloc(animated_sprite->animations.items, sizeof(*ptr) * animated_sprite->animations.capacity * 2);
        assert(ptr != NULL);
        memset(&ptr[animated_sprite->animations.count], 0, sizeof(*ptr) * animated_sprite->animations.capacity);
        animated_sprite->animations.items = ptr;
        animated_sprite->animations.capacity *= 2;
    }

    struct frame* frames_items = malloc(sizeof(*frames_items));
    assert(frames_items != NULL);
    memset(frames_items, 0, sizeof(*frames_items));

    struct frames frames =
    {
        .items = frames_items,
        .count = 0,
        .capacity = 1
    };

    struct animation animation =
    {
        .name = animation_name,
        .frames = frames,
        .current_frame_index = 0
    };

    animated_sprite->animations.items[animated_sprite->animations.count++] = animation;
}
void animated_sprite_add_frame(struct animated_sprite* animated_sprite, char* animation_name, Texture2D texture, float duration)
{
    struct animation* animation = NULL;

    for (size_t i = 0; i < animated_sprite->animations.count; ++i)
    {
        animation = &animated_sprite->animations.items[i];
        if (strcmp(animation->name, animation_name) == 0)
        {
            break;
        }
    }

    assert(animation != NULL);

    if (animation->frames.count == animation->frames.capacity)
    {
        struct frame* ptr = realloc(animation->frames.items, sizeof(*ptr) * animation->frames.capacity * 2);
        assert(ptr != NULL);
        memset(&ptr[animation->frames.count], 0, sizeof(*ptr) * animation->frames.capacity);
        animation->frames.items = ptr;
        animation->frames.capacity *= 2;
    }

    struct frame frame =
    {
        .texture = texture,
        .duration = duration
    };

    animation->frames.items[animation->frames.count++] = frame;
}
void animated_sprite_play(struct animated_sprite* animated_sprite, char* animation_name)
{
    size_t index = 0;
    struct animation* animation = NULL;

    for (size_t i = 0; i < animated_sprite->animations.count; ++i)
    {
        animation = &animated_sprite->animations.items[i];
        if (strcmp(animation->name, animation_name) == 0)
        {
            index = i;
            break;
        }
    }

    assert(animation != NULL);

    if (index != animated_sprite->current_animation_index)
    {
        animation->current_frame_index = 0;

        animated_sprite->is_playing = true;
        animated_sprite->current_animation_index = index;
        animated_sprite->elapsed_time = 0.0f;
    }
}

void animated_sprite_tick(struct animated_sprite* animated_sprite, float delta)
{
    if (!animated_sprite->is_playing) return;

    animated_sprite->elapsed_time += delta;

    struct animation* animation = &animated_sprite->animations.items[animated_sprite->current_animation_index];

    while (animated_sprite->elapsed_time >= animation->frames.items[animation->current_frame_index].duration)
    {
        animated_sprite->elapsed_time -= animation->frames.items[animation->current_frame_index].duration;
        ++animation->current_frame_index;
        if (animation->current_frame_index == animation->frames.count)
        {
            animation->current_frame_index = 0;
        }
    }
}
void animated_sprite_draw(struct animated_sprite* animated_sprite)
{
    struct animation* animation = &animated_sprite->animations.items[animated_sprite->current_animation_index];
    struct frame* frame = &animation->frames.items[animation->current_frame_index];

    Texture texture = frame->texture;
    int x = animated_sprite->x;
    int y = animated_sprite->y;
    Color tint = animated_sprite->tint;
    DrawTexture(texture, x, y, tint);
}
