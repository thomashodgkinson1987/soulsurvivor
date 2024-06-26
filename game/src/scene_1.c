#include "scene_1.h"
#include "scene.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t SCENE_1_TAG = { 0 };

struct scene scene_1(float x, float y)
{
    struct scene_1_data* data = malloc(sizeof(*data));
    assert(data != NULL);

    *data = (struct scene_1_data)
    {
        .x = x,
        .y = y,
        .t = 0.0f
    };

    struct scene scene =
    {
        .tag = SCENE_1_TAG,
        .data = data
    };

    return scene;
}
void scene_1_init(struct scene* scene)
{

}
void scene_1_free(struct scene* scene)
{
    struct scene_1_data* data = (struct scene_1_data*)scene->data;

    free(data);
}
void scene_1_enter(struct scene* scene)
{
    struct scene_1_data* data = (struct scene_1_data*)scene->data;

    data->t = 0.0f;
}
void scene_1_exit(struct scene* scene)
{
    struct scene_1_data* data = (struct scene_1_data*)scene->data;

    data->t = 0.0f;
}
void scene_1_tick(struct scene* scene, float delta)
{
    struct scene_1_data* data = (struct scene_1_data*)scene->data;

    data->t += delta;
    if (data->t >= 2.0f)
    {
        data->t = 0.0f;
    }
}
void scene_1_draw(struct scene* scene)
{
    struct scene_1_data* data = (struct scene_1_data*)scene->data;

    ClearBackground(WHITE);
    DrawText(TextFormat("%f", data->t), 8, 8, 8, BLACK);
}