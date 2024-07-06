#include "tween.h"

#include "mfn_dynamic_array.h"

static struct tween_vtable vtable = { 0 };

size_t TWEEN_BASE_TAG = 0;
size_t TWEEN_FLOAT_TAG = 0;
size_t TWEEN_COLOR_TAG = 0;
size_t TWEEN_UNSIGNED_CHAR_TAG = 0;

void tween_vtable_init(void)
{
    MFN_ARRAY_INIT(struct tween_funcs, &vtable);

    TWEEN_BASE_TAG = tween_vtable_register((struct tween_funcs)
    {
        .tick = NULL
    });

    TWEEN_FLOAT_TAG = tween_vtable_register((struct tween_funcs)
    {
        .tick = tween_float_tick
    });

    TWEEN_COLOR_TAG = tween_vtable_register((struct tween_funcs)
    {
        .tick = tween_color_tick
    });

    TWEEN_UNSIGNED_CHAR_TAG = tween_vtable_register((struct tween_funcs)
    {
        .tick = tween_unsigned_char_tick
    });
}
void tween_vtable_free(void)
{
    MFN_ARRAY_FREE(&vtable);

    TWEEN_BASE_TAG = 0;
    TWEEN_FLOAT_TAG = 0;
    TWEEN_COLOR_TAG = 0;
    TWEEN_UNSIGNED_CHAR_TAG = 0;
}
size_t tween_vtable_register(struct tween_funcs funcs)
{
    size_t tag = vtable.count;

    MFN_ARRAY_APPEND(struct tween_funcs, &vtable, funcs);

    return tag;
}

struct tween tween_new(size_t tag, void* data, float duration)
{
    struct tween tween =
    {
        .tag = tag,
        .data = data,
        .duration = duration,
        .elapsed = 0.0f,
        .is_complete = false
    };

    return tween;
}
void tween_free(struct tween* tween)
{
    tween->tag = 0;

    if (tween->data)
    {
        free(tween->data);
        tween->data = NULL;
    }

    tween->duration = 0.0f;
    tween->elapsed = 0.0f;
    tween->is_complete = false;
}
void tween_reset(struct tween* tween)
{
    tween->elapsed = 0.0f;
    tween->is_complete = false;
}
void tween_tick(struct tween* tween, float delta)
{
    if (tween->is_complete)
    {
        return;
    }

    tween->elapsed += delta;

    if (vtable.items[tween->tag].tick)
    {
        vtable.items[tween->tag].tick(tween, delta);
    }

    if (tween->elapsed >= tween->duration)
    {
        tween->elapsed = tween->duration;
        tween->is_complete = true;
    }
}

struct tween tween_float_new(float* value, float from, float to, float duration)
{
    struct tween_float_data* data = malloc(sizeof(*data));
    assert(data != NULL);

    *data = (struct tween_float_data)
    {
        .value = value,
        .from = from,
        .to = to
    };

    struct tween tween = tween_new(TWEEN_FLOAT_TAG, data, duration);

    return tween;
}
void tween_float_tick(struct tween* tween, float delta)
{
    struct tween_float_data* data = tween->data;

    float p = tween->elapsed / tween->duration;
    p = p > 1.0f ? 1.0f : p;
    *data->value = data->from + (p * (data->to - data->from));
}

struct tween tween_color_new(Color* value, Color from, Color to, float duration)
{
    struct tween_color_data* data = malloc(sizeof(*data));
    assert(data != NULL);

    *data = (struct tween_color_data)
    {
        .value = value,
        .from = from,
        .to = to
    };

    struct tween tween = tween_new(TWEEN_COLOR_TAG, data, duration);

    return tween;
}
void tween_color_tick(struct tween* tween, float delta)
{
    struct tween_color_data* data = tween->data;

    float p = tween->elapsed / tween->duration;
    p = p > 1.0f ? 1.0f : p;

    data->value->r = (unsigned char)((float)data->from.r + (p * ((float)data->to.r - (float)data->from.r)));
    data->value->g = (unsigned char)((float)data->from.g + (p * ((float)data->to.g - (float)data->from.g)));
    data->value->b = (unsigned char)((float)data->from.b + (p * ((float)data->to.b - (float)data->from.b)));
    data->value->a = (unsigned char)((float)data->from.a + (p * ((float)data->to.a - (float)data->from.a)));
}

struct tween tween_unsigned_char_new(unsigned char* value, unsigned char from, unsigned char to, float duration)
{
    struct tween_unsigned_char_data* data = malloc(sizeof(*data));
    assert(data != NULL);

    *data = (struct tween_unsigned_char_data)
    {
        .value = value,
        .from = from,
        .to = to
    };

    struct tween tween = tween_new(TWEEN_UNSIGNED_CHAR_TAG, data, duration);

    return tween;
}
void tween_unsigned_char_tick(struct tween* tween, float delta)
{
    struct tween_unsigned_char_data* data = tween->data;

    float p = tween->elapsed / tween->duration;
    p = p > 1.0f ? 1.0f : p;
    *data->value = (unsigned char)((float)data->from + (p * ((float)data->to - (float)data->from)));
}
