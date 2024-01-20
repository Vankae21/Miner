#ifndef MINER_H
#define MINER_H
#include "raylib.h"
#include <stdlib.h>

typedef struct Miner
{

    Vector2 pos;
    Vector2 size;
    Vector2 dir;
    float speed;
    float vel_y;

    short facing;
    unsigned short anim_state;

    bool is_grounded;

    Texture2D tex;

} Miner;

Miner* init_miner(Texture2D tex, Vector2 pos, Vector2 size, float speed);
void update_miner(Miner* miner);
void draw_miner(Miner* miner);
Rectangle get_miner_rec(Miner* miner);
Vector2 get_mid_of_miner(Miner* miner);

#endif