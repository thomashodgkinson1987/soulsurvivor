#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "raylib.h"

struct frame
{
    Texture2D texture;
    float duration;
};

struct frames
{
    struct frame* items;
    size_t count;
    size_t capacity;
};

struct animation
{
    char* name;
    struct frames frames;
};

struct animated_sprite
{
    int x;
    int y;
    bool is_playing;
    struct frames frames;
    size_t current_index;
    float elapsed_time;
};

struct animated_sprite animated_sprite_new(void);
void animated_sprite_free(struct animated_sprite* animated_sprite);

void animated_sprite_add_frame(struct animated_sprite* animated_sprite, Texture2D texture, float duration);

void animated_sprite_tick(struct animated_sprite* animated_sprite, float delta);
void animated_sprite_draw(struct animated_sprite* animated_sprite);

void animated_sprite_reset(struct animated_sprite* animated_sprite);

#endif
