#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include "animation.h"

struct animation_player
{
    struct animations animations;
    size_t current_animation_index;
    size_t current_frame_index;
    float elapsed_time;
    bool is_playing;
};

struct animation_player animation_player_new(struct animations animations);
void animation_player_free(struct animation_player* animation_player);

void animation_player_play(struct animation_player* animation_player, char* name);
void animation_player_tick(struct animation_player* animation_player, float delta);

#endif
