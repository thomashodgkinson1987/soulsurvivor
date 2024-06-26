#include "scene_2.h"
#include "scene.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t SCENE_2_TAG = { 0 };

struct scene scene_2(float x, float y, float z)
{
    struct scene_2_data* data = malloc(sizeof(*data));
    assert(data != NULL);

    *data = (struct scene_2_data)
    {
        .x = x,
        .y = y,
        .z = z,
        .t = 0.0f
    };

    struct scene scene =
    {
        .tag = SCENE_2_TAG,
        .data = data
    };

    return scene;
}
void scene_2_init(struct scene* scene)
{

}
void scene_2_free(struct scene* scene)
{
    struct scene_2_data* data = (struct scene_2_data*)scene->data;

    free(data);
}
void scene_2_enter(struct scene* scene)
{
    struct scene_2_data* data = (struct scene_2_data*)scene->data;

    data->t = 0.0f;
}
void scene_2_exit(struct scene* scene)
{
    struct scene_2_data* data = (struct scene_2_data*)scene->data;

    data->t = 0.0f;
}
void scene_2_tick(struct scene* scene, float delta)
{
    struct scene_2_data* data = (struct scene_2_data*)scene->data;

    data->t += delta;
    if (data->t >= 2.0f)
    {
        data->t = 0.0f;
    }
}
void scene_2_draw(struct scene* scene)
{
    struct scene_2_data* data = (struct scene_2_data*)scene->data;

    ClearBackground(BLUE);
    DrawText(TextFormat("%f", data->t), 8, 8, 8, BLACK);
}