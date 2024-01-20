#include "include/block.h"
#include "include/game.h"

Block* init_block(BlockType type, Vector2 pos, int size)
{
    Block* block = calloc(1, sizeof(Block));

    block->pos = pos;   
    block->size = size * SIZE_MULTIPLIER;
    block->type = type;
    
    block->is_active = true;

    return block;
}
void draw_block(Texture2D blocks_spritesheet, Block* block)
{
    DrawTexturePro(blocks_spritesheet, (Rectangle){ .x = block->type * block->size/SIZE_MULTIPLIER, .y = 0, .width = block->size/SIZE_MULTIPLIER, .height = block->size/SIZE_MULTIPLIER },
    get_block_rec(block), (Vector2){ 0 }, 0, WHITE);
}
Rectangle get_block_rec(Block* block)
{
    return (Rectangle){ .x = block->pos.x, .y = block->pos.y, .width = block->size, .height = block->size };
}
Vector2 get_mid_of_block(Block* block)
{
    return (Vector2){ .x = block->pos.x + block->size/2, .y = block->pos.y + block->size/2 };
}