#include "include/miner.h"
#include "include/game.h"

Miner* init_miner(Texture2D tex, Vector2 pos, Vector2 size, float speed)
{
    Miner* miner = calloc(1, sizeof(Miner));

    miner->pos = pos;
    miner->size.x = size.x * SIZE_MULTIPLIER;
    miner->size.y = size.y * SIZE_MULTIPLIER;
    miner->speed = speed;
    miner->vel_y = 0;
    miner->tex = tex;

    miner->facing = 1;
    miner->anim_state = 0;

    miner->is_grounded = false;

    miner->dir = (Vector2){ 0 };

    return miner;
}
void update_miner(Miner* miner)
{
    miner->dir.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    miner->dir.y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    miner->facing = miner->dir.x == 0 ? miner->facing : miner->dir.x;

    miner->vel_y = miner->is_grounded ? 0 : miner->vel_y + GRAVITY * GetFrameTime();

    miner->pos.x += miner->dir.x * miner->speed * GetFrameTime();
    miner->pos.y += miner->vel_y * GetFrameTime();

    miner->anim_state += IsKeyPressed(KEY_PAGE_UP) - IsKeyPressed(KEY_PAGE_DOWN);

    if(miner->vel_y == 0){ printf("fukk\n");}
}
void draw_miner(Miner* miner)
{
    if(DEBUG)
        DrawRectangleRec(get_miner_rec(miner), LIGHTGRAY);
    DrawTexturePro(miner->tex, (Rectangle){ .x = miner->anim_state * miner->size.x / SIZE_MULTIPLIER, .y = 0, .width = miner->facing * miner->size.x / SIZE_MULTIPLIER, .height = miner->size.y/SIZE_MULTIPLIER },
    get_miner_rec(miner), (Vector2){ 0 }, 0, WHITE);
}
Rectangle get_miner_rec(Miner* miner)
{
    return (Rectangle){ .x = miner->pos.x, .y = miner->pos.y, .width = miner->size.x, .height = miner->size.y };
}
Vector2 get_mid_of_miner(Miner* miner)
{
    return (Vector2){ .x = miner->pos.x + miner->size.x/2, .y = miner->pos.y + miner->size.y/2 };
}