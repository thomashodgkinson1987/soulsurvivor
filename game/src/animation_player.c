#include "animation_player.h"

#include <assert.h>
#include <string.h>

struct animation_player animation_player_new(struct animations animations)
{
    struct animation_player animation_player =
    {
        .animations = animations,
        .current_animation_index = 0,
        .current_frame_index = 0,
        .elapsed_time = 0.0f,
        .is_playing = true
    };

    return animation_player;
}
void animation_player_free(struct animation_player* animation_player)
{
    animation_player->animations = (struct animations){ 0 };
    animation_player->current_animation_index = 0;
    animation_player->current_frame_index = 0;
    animation_player->elapsed_time = 0.0f;
    animation_player->is_playing = false;
}

void animation_player_play(struct animation_player* animation_player, char* name)
{
    size_t animation_index = 0;
    struct animation* animation = NULL;

    for (size_t i = 0; i < animation_player->animations.count; ++i)
    {
        animation = &animation_player->animations.items[i];
        if (strcmp(animation->name, name) == 0)
        {
            animation_index = i;
            break;
        }
    }

    assert(animation != NULL);

    if (animation_index != animation_player->current_animation_index)
    {
        animation_player->current_animation_index = animation_index;
        animation_player->current_frame_index = 0;
        animation_player->elapsed_time = 0.0f;
        animation_player->is_playing = true;
    }
}
void animation_player_tick(struct animation_player* animation_player, float delta)
{
    if (!animation_player->is_playing)
    {
        return;
    }

    animation_player->elapsed_time += delta;

    struct animation* animation = &animation_player->animations.items[animation_player->current_animation_index];

    while (animation_player->elapsed_time >= animation->frames.items[animation_player->current_frame_index].duration)
    {
        animation_player->elapsed_time -= animation->frames.items[animation_player->current_frame_index].duration;
        ++animation_player->current_frame_index;
        if (animation_player->current_frame_index == animation->frames.count)
        {
            animation_player->current_frame_index = 0;
        }
    }
}
