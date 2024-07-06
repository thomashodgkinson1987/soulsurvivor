#include "scene.h"
#include "scene_1.h"

#include "raylib.h"

#include <assert.h>
#include <stdlib.h>

size_t SCENE_1_TAG = 0;

struct scene scene_1_new(float x, float y)
{
    struct scene_1_data* data = malloc(sizeof(*data));
    assert(data != NULL);

    *data = (struct scene_1_data)
    {
        .x = x,
        .y = y,
        .t = 0.0f
    };

    struct scene scene = scene_new(SCENE_1_TAG, data);

    return scene;
}
void scene_1_free(struct scene* scene)
{

}
void scene_1_enter(struct scene* scene)
{
    struct scene_1_data* data = scene->data;

    data->t = 0.0f;
}
void scene_1_exit(struct scene* scene)
{
    struct scene_1_data* data = scene->data;

    data->t = 0.0f;
}
void scene_1_tick(struct scene* scene, float delta)
{
    struct scene_1_data* data = scene->data;

    data->t += delta;

    if (data->t >= 2.0f)
    {
        data->t = 0.0f;
    }
}
void scene_1_draw(struct scene* scene)
{
    struct scene_1_data* data = scene->data;

    ClearBackground(WHITE);
    DrawText(TextFormat("%f", data->t), 8, 8, 8, BLACK);
}