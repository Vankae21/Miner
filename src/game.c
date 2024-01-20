#include "include/game.h"
#include "include/miner.h"
#include "include/block.h"
#include <math.h>
#include <time.h>

bool DEBUG = true;

const int SIZE_MULTIPLIER = 3;

const int WIDTH = 1366;
const int HEIGHT = 768;

const float BLOCK_OFFSET = 8.5f;

const float GRAVITY = 580.0f;

#define COLS 20
#define ROWS 5

Camera2D* camera;

Miner* miner = NULL;
Block* blocks[COLS][ROWS];

Texture2D blocks_spritesheet;

void init()
{
    // miner
    miner = init_miner(LoadTexture("assets/miner.png"), (Vector2){ .x = 400, .y = 0 }, (Vector2){ .x = 32, .y = 32 }, 100);

    // camera
    camera = calloc(1, sizeof(Camera2D));
    camera->target = miner->pos;
    camera->offset = (Vector2){ WIDTH / 2.0f - miner->size.x / 2, HEIGHT / 2.0f - miner->size.y / 2 };
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;

    // blocks
    blocks_spritesheet = LoadTexture("assets/blocks.png");

    int block_size = 32;
    int block_x = 50;
    int block_y = 300;

    Vector2 block_pos = { .x = block_x, .y = block_y };

    for(int i = 0; i < COLS; i++)
    {
        block_pos.y = block_y;

        for(int j = 0; j < ROWS; j++)
        {
            blocks[i][j] = init_block(BLOCK_GRASS, block_pos, 32);
            block_pos.y += block_size * SIZE_MULTIPLIER;
        }

        block_pos.x += block_size * SIZE_MULTIPLIER;
    }
}
void update()
{
    update_miner(miner);

    bool vertically_collided = false;

    Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), *camera);
    bool mouse_is_clicked = IsMouseButtonPressed(0);
    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            Block* block = blocks[i][j];
            if(!block->is_active) continue;

            if(CheckCollisionPointRec(mouse_pos, get_block_rec(block)) && ((distance(get_mid_of_miner(miner), get_mid_of_block(block)) <= 44.8f * SIZE_MULTIPLIER) || (distance(get_mid_of_miner(miner), get_mid_of_block(block)) <= 48.0f * SIZE_MULTIPLIER && miner->pos.y > block->pos.y)))
            {
                // printf("%0.03f\n", distance(get_mid_of_miner(miner), get_mid_of_block(blocks[i][j])));
                if(mouse_is_clicked)
                    block->is_active = false;
            }

            if(CheckCollisionRecs(get_miner_rec(miner), get_block_rec(block)))
            {
                if(miner->pos.y + miner->size.y >= block->pos.y && miner->pos.y + miner->size.y - block->pos.y <= BLOCK_OFFSET)
                {
                    miner->pos.y = block->pos.y - miner->size.y;
                    vertically_collided = true;
                }
                else if(miner->pos.y <= block->pos.y + block->size && block->pos.y + block->size - miner->pos.y <= BLOCK_OFFSET)
                {
                    miner->pos.y = block->pos.y + block->size;
                }
                else if(miner->pos.x <= block->pos.x + block->size && miner->dir.x != 1)
                {
                    miner->pos.x = block->pos.x + block->size;
                }
                else if(miner->pos.x + miner->size.x >= block->pos.x && miner->dir.x != -1)
                {
                    miner->pos.x = block->pos.x - miner->size.x;
                }
            }
        }
    }

    miner->is_grounded = vertically_collided ? true : false;

    // cam
    camera->target = miner->pos;
}
void late_update()
{
    BeginMode2D(*camera);

    draw_miner(miner);
    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            if(!blocks[i][j]->is_active) continue;
            draw_block(blocks_spritesheet, blocks[i][j]);

            if(DEBUG)
                DrawRectangleLinesEx(get_block_rec(blocks[i][j]), 1.0f, RAYWHITE);
        }
    }

    EndMode2D();
}
void end()
{
    UnloadTexture(blocks_spritesheet);
    free(miner);
    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            free(blocks[i][j]);
        }
    }
}

// functionality
float distance(Vector2 a, Vector2 b)
{
    return fabs(sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}