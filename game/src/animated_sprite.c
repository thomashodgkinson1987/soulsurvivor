#include "animated_sprite.h"

#include "mfn_dynamic_array.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct animated_sprite animated_sprite_new(int x, int y)
{
    struct animations animations = { 0 };
    MFN_ARRAY_INIT(struct animation, &animations);

    struct animated_sprite animated_sprite =
    {
        .x = x,
        .y = y,
        .origin = (Vector2){ 0.0f, 0.0f },
        .rotation = 0.0f,
        .tint = WHITE,
        .is_flip_x = false,
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

    animated_sprite->origin = (Vector2){ 0.0f, 0.0f };
    animated_sprite->rotation = 0.0f;
    animated_sprite->tint = BLANK;

    animated_sprite->is_flip_x = false;

    animated_sprite->is_playing = false;

    for (size_t i = 0; i < animated_sprite->animations.count; ++i)
    {
        struct animation* animation = &animated_sprite->animations.items[i];
        MFN_ARRAY_FREE(struct frame, &animation->frames);
    }

    MFN_ARRAY_FREE(struct animation, &animated_sprite->animations);

    animated_sprite->current_animation_index = 0;
    animated_sprite->elapsed_time = 0.0f;
}

void animated_sprite_create_animation(struct animated_sprite* animated_sprite, char* animation_name)
{
    struct frames frames = { 0 };
    MFN_ARRAY_INIT(struct frame, &frames);

    struct animation animation =
    {
        .name = animation_name,
        .frames = frames,
        .current_frame_index = 0
    };

    MFN_ARRAY_APPEND(struct animation, &animated_sprite->animations, animation);
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

    struct frame frame =
    {
        .texture = texture,
        .duration = duration
    };

    MFN_ARRAY_APPEND(struct frame, &animation->frames, frame);
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
    Rectangle source = (Rectangle){ 0.0f, 0.0f, animated_sprite->is_flip_x ? -(float)texture.width : (float)texture.width, (float)texture.height };
    Rectangle dest = (Rectangle){ 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Vector2 origin = animated_sprite->origin;
    float rotation = animated_sprite->rotation;
    Color tint = animated_sprite->tint;

    dest.x += animated_sprite->x;
    dest.y += animated_sprite->y;

    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}
