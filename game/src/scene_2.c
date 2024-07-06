#include "scene.h"
#include "scene_2.h"

#include "raylib.h"

#include <assert.h>
#include <stdlib.h>

size_t SCENE_2_TAG = 0;

struct scene scene_2_new(float x, float y, float z)
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

    struct scene scene = scene_new(SCENE_2_TAG, data);

    return scene;
}
void scene_2_free(struct scene* scene)
{

}
void scene_2_enter(struct scene* scene)
{
    struct scene_2_data* data = scene->data;

    data->t = 0.0f;
}
void scene_2_exit(struct scene* scene)
{
    struct scene_2_data* data = scene->data;

    data->t = 0.0f;
}
void scene_2_tick(struct scene* scene, float delta)
{
    struct scene_2_data* data = scene->data;

    data->t += delta;

    if (data->t >= 2.0f)
    {
        data->t = 0.0f;
    }
}
void scene_2_draw(struct scene* scene)
{
    struct scene_2_data* data = scene->data;

    ClearBackground(BLUE);
    DrawText(TextFormat("%f", data->t), 8, 8, 8, BLACK);
}