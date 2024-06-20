#include "raylib.h"

int main(void)
{
    InitWindow(512, 512, "soulsurvivor");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);

        DrawFPS(8, 8);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
