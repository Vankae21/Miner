#ifndef BLOCK_H
#define BLOCK_H
#include "raylib.h"
#include <stdlib.h>


typedef enum BlockType
{

    BLOCK_GRASS

} BlockType;

typedef struct Block
{

    Vector2 pos;
    int size;
    BlockType type;
    bool is_active;

} Block;

Block* init_block(BlockType type, Vector2 pos, int size);
void draw_block(Texture2D blocks_spritesheet, Block* block);
Rectangle get_block_rec(Block* block);
Vector2 get_mid_of_block(Block* block);

#endif