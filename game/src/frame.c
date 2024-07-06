#include "frame.h"

struct frame frame_new(Texture2D texture, float duration)
{
    struct frame frame =
    {
        .texture = texture,
        .duration = duration
    };

    return frame;
}
void frame_free(struct frame* frame)
{
    frame->texture = (Texture2D){ 0 };
    frame->duration = 0.0f;
}
