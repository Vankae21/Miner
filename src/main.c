#include "raylib.h"
#include "include/game.h"

int main()
{
    InitWindow(WIDTH, HEIGHT, TITLE);

    SetTargetFPS(FPS);

    SetExitKey(KEY_NULL);

    if(DEBUG)
        SetWindowState(FLAG_WINDOW_RESIZABLE);

    init();

    while(!WindowShouldClose())
    {
        update();
        BeginDrawing();
        ClearBackground(BLACK);
        late_update();
        EndDrawing();
    }
    end();
    CloseWindow();

    return 0;
}