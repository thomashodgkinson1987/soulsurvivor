#include "button.h"

#include "mfn_dynamic_array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct button button_create(int x, int y, int width, int height, unsigned char color_r, unsigned char color_g, unsigned char color_b, unsigned char color_a)
{
    struct button_signal_on_hovered_array signal_on_hovered_array = { 0 };
    MFN_ARRAY_INIT(struct button_signal_on_hovered_array, &signal_on_hovered_array);

    struct button_signal_on_hovering_array signal_on_hovering_array = { 0 };
    MFN_ARRAY_INIT(struct button_signal_on_hovering_array, &signal_on_hovering_array);

    struct button_signal_on_unhovered_array signal_on_unhovered_array = { 0 };
    MFN_ARRAY_INIT(struct button_signal_on_unhovered_array, &signal_on_unhovered_array);

    struct button_signal_on_pressed_array signal_on_pressed_array = { 0 };
    MFN_ARRAY_INIT(struct button_signal_on_pressed_array, &signal_on_pressed_array);

    struct button_signal_on_held_array signal_on_held_array = { 0 };
    MFN_ARRAY_INIT(struct button_signal_on_held_array, &signal_on_held_array);

    struct button_signal_on_released_array signal_on_released_array = { 0 };
    MFN_ARRAY_INIT(struct button_signal_on_released_array, &signal_on_released_array);

    struct button button =
    {
        .x = x,
        .y = y,

        .width = width,
        .height = height,

        .color = { color_r, color_g, color_b, color_a },

        .signal_on_hovered_array = signal_on_hovered_array,
        .signal_on_hovering_array = signal_on_hovering_array,
        .signal_on_unhovered_array = signal_on_unhovered_array,

        .signal_on_pressed_array = signal_on_pressed_array,
        .signal_on_held_array = signal_on_held_array,
        .signal_on_released_array = signal_on_released_array,

        .is_hovering = false,
        .was_hovering = false,

        .is_pressed = false,
        .was_pressed = false,

        .on_draw = NULL
    };

    return button;
}
void button_free(struct button* button)
{
    button->x = 0;
    button->y = 0;

    button->width = 0;
    button->height = 0;

    memset(button->color, 0, sizeof(button->color));

    MFN_ARRAY_FREE(struct button_signal_on_hovered_array, &button->signal_on_hovered_array);
    MFN_ARRAY_FREE(struct button_signal_on_hovering_array, &button->signal_on_hovering_array);
    MFN_ARRAY_FREE(struct button_signal_on_unhovered_array, &button->signal_on_unhovered_array);
    MFN_ARRAY_FREE(struct button_signal_on_pressed_array, &button->signal_on_pressed_array);
    MFN_ARRAY_FREE(struct button_signal_on_held_array, &button->signal_on_held_array);
    MFN_ARRAY_FREE(struct button_signal_on_released_array, &button->signal_on_released_array);

    button->is_hovering = false;
    button->was_hovering = false;

    button->is_pressed = false;
    button->was_pressed = false;

    button->on_draw = NULL;
}

void button_register_signal_on_hovered(struct button* button, void(*on_hovered)(struct button* button))
{
    MFN_ARRAY_APPEND(struct button_signal_on_hovered_array, &button->signal_on_hovered_array, on_hovered);
}
void button_register_signal_on_hovering(struct button* button, void(*on_hovering)(struct button* button))
{
    MFN_ARRAY_APPEND(struct button_signal_on_hovering_array, &button->signal_on_hovering_array, on_hovering);
}
void button_register_signal_on_unhovered(struct button* button, void(*on_unhovered)(struct button* button))
{
    MFN_ARRAY_APPEND(struct button_signal_on_unhovered_array, &button->signal_on_unhovered_array, on_unhovered);
}

void button_register_signal_on_pressed(struct button* button, void(*on_pressed)(struct button* button))
{
    MFN_ARRAY_APPEND(struct button_signal_on_pressed_array, &button->signal_on_pressed_array, on_pressed);
}
void button_register_signal_on_held(struct button* button, void(*on_held)(struct button* button))
{
    MFN_ARRAY_APPEND(struct button_signal_on_held_array, &button->signal_on_held_array, on_held);
}
void button_register_signal_on_released(struct button* button, void(*on_released)(struct button* button))
{
    MFN_ARRAY_APPEND(struct button_signal_on_released_array, &button->signal_on_released_array, on_released);
}

void button_unregister_signal_on_hovered(struct button* button, void(*on_hovered)(struct button* button))
{
    size_t index = 0;
    bool was_found = false;

    for (size_t i = 0; i < button->signal_on_hovered_array.count; ++i)
    {
        if (button->signal_on_hovered_array.items[i] == on_hovered)
        {
            index = i;
            was_found = true;
            break;
        }
    }

    assert(was_found);

    for (size_t i = index; i < button->signal_on_hovered_array.count - 1; ++i)
    {
        button->signal_on_hovered_array.items[i] = button->signal_on_hovered_array.items[i + 1];
    }

    button->signal_on_hovered_array.items[--button->signal_on_hovered_array.count] = NULL;
}
void button_unregister_signal_on_hovering(struct button* button, void(*on_hovering)(struct button* button))
{
    size_t index = 0;
    bool was_found = false;

    for (size_t i = 0; i < button->signal_on_hovering_array.count; ++i)
    {
        if (button->signal_on_hovering_array.items[i] == on_hovering)
        {
            index = i;
            was_found = true;
            break;
        }
    }

    assert(was_found);

    for (size_t i = index; i < button->signal_on_hovering_array.count - 1; ++i)
    {
        button->signal_on_hovering_array.items[i] = button->signal_on_hovering_array.items[i + 1];
    }

    button->signal_on_hovering_array.items[--button->signal_on_hovering_array.count] = NULL;
}
void button_unregister_signal_on_unhovered(struct button* button, void(*on_unhovered)(struct button* button))
{
    size_t index = 0;
    bool was_found = false;

    for (size_t i = 0; i < button->signal_on_unhovered_array.count; ++i)
    {
        if (button->signal_on_unhovered_array.items[i] == on_unhovered)
        {
            index = i;
            was_found = true;
            break;
        }
    }

    assert(was_found);

    for (size_t i = index; i < button->signal_on_unhovered_array.count - 1; ++i)
    {
        button->signal_on_unhovered_array.items[i] = button->signal_on_unhovered_array.items[i + 1];
    }

    button->signal_on_unhovered_array.items[--button->signal_on_unhovered_array.count] = NULL;
}

void button_unregister_signal_on_pressed(struct button* button, void(*on_pressed)(struct button* button))
{
    size_t index = 0;
    bool was_found = false;

    for (size_t i = 0; i < button->signal_on_pressed_array.count; ++i)
    {
        if (button->signal_on_pressed_array.items[i] == on_pressed)
        {
            index = i;
            was_found = true;
            break;
        }
    }

    assert(was_found);

    for (size_t i = index; i < button->signal_on_pressed_array.count - 1; ++i)
    {
        button->signal_on_pressed_array.items[i] = button->signal_on_pressed_array.items[i + 1];
    }

    button->signal_on_pressed_array.items[--button->signal_on_pressed_array.count] = NULL;
}
void button_unregister_signal_on_held(struct button* button, void(*on_held)(struct button* button))
{
    size_t index = 0;
    bool was_found = false;

    for (size_t i = 0; i < button->signal_on_held_array.count; ++i)
    {
        if (button->signal_on_held_array.items[i] == on_held)
        {
            index = i;
            was_found = true;
            break;
        }
    }

    assert(was_found);

    for (size_t i = index; i < button->signal_on_held_array.count - 1; ++i)
    {
        button->signal_on_held_array.items[i] = button->signal_on_held_array.items[i + 1];
    }

    button->signal_on_held_array.items[--button->signal_on_held_array.count] = NULL;
}
void button_unregister_signal_on_released(struct button* button, void(*on_released)(struct button* button))
{
    size_t index = 0;
    bool was_found = false;

    for (size_t i = 0; i < button->signal_on_released_array.count; ++i)
    {
        if (button->signal_on_released_array.items[i] == on_released)
        {
            index = i;
            was_found = true;
            break;
        }
    }

    assert(was_found);

    for (size_t i = index; i < button->signal_on_released_array.count - 1; ++i)
    {
        button->signal_on_released_array.items[i] = button->signal_on_released_array.items[i + 1];
    }

    button->signal_on_released_array.items[--button->signal_on_released_array.count] = NULL;
}

void button_on_hovered(struct button* button)
{
    for (size_t i = 0; i < button->signal_on_hovered_array.count; ++i)
    {
        button->signal_on_hovered_array.items[i](button);
    }
}
void button_on_hovering(struct button* button)
{
    for (size_t i = 0; i < button->signal_on_hovering_array.count; ++i)
    {
        button->signal_on_hovering_array.items[i](button);
    }
}
void button_on_unhovered(struct button* button)
{
    for (size_t i = 0; i < button->signal_on_unhovered_array.count; ++i)
    {
        button->signal_on_unhovered_array.items[i](button);
    }
}

void button_on_pressed(struct button* button)
{
    for (size_t i = 0; i < button->signal_on_pressed_array.count; ++i)
    {
        button->signal_on_pressed_array.items[i](button);
    }
}
void button_on_held(struct button* button)
{
    for (size_t i = 0; i < button->signal_on_held_array.count; ++i)
    {
        button->signal_on_held_array.items[i](button);
    }
}
void button_on_released(struct button* button)
{
    for (size_t i = 0; i < button->signal_on_released_array.count; ++i)
    {
        button->signal_on_released_array.items[i](button);
    }
}

void button_tick(struct button* button, int cursor_x, int cursor_y, bool is_pressed, bool was_pressed)
{
    // Update previous states
    button->was_hovering = button->is_hovering;
    button->was_pressed = button->is_pressed;

    // Determine if the cursor is within button bounds
    bool cursor_within_bounds = (cursor_x >= button->x && cursor_x < button->x + button->width &&
        cursor_y >= button->y && cursor_y < button->y + button->height);

    // Update current states
    button->is_hovering = cursor_within_bounds;
    button->is_pressed = button->is_hovering && is_pressed;

    // Handle hover events
    if (!was_pressed && !is_pressed && !button->was_hovering && button->is_hovering)
    {
        button_on_hovered(button);
    }
    else if (!was_pressed && !is_pressed && button->was_hovering && button->is_hovering)
    {
        button_on_hovering(button);
    }
    else if (!was_pressed && !is_pressed && button->was_hovering && !button->is_hovering)
    {
        button_on_unhovered(button);
    }

    // Handle pressed events
    if (!was_pressed && is_pressed && button->is_hovering)
    {
        button_on_pressed(button);
    }
    else if (was_pressed && is_pressed && button->is_hovering)
    {
        button_on_held(button);
    }
    else if (was_pressed && !is_pressed && button->is_hovering)
    {
        button_on_released(button);
    }
}
void button_draw(struct button* button)
{
    if (button->on_draw != NULL)
    {
        button->on_draw(button);
    }
}
