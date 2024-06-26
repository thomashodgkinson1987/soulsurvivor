#ifndef SCENE_1
#define SCENE_1

struct scene_1_data
{
    float x;
    float y;
    float t;
};

size_t SCENE_1_TAG;

struct scene scene_1(float x, float y);
void scene_1_init(struct scene* scene);
void scene_1_free(struct scene* scene);
void scene_1_enter(struct scene* scene);
void scene_1_exit(struct scene* scene);
void scene_1_tick(struct scene* scene, float delta);
void scene_1_draw(struct scene* scene);

#endif
