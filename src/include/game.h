#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

extern const int WIDTH;
extern const int HEIGHT;
extern const int SIZE_MULTIPLIER;

extern const float GRAVITY;

#define TITLE "Miner"
#define FPS 60

extern bool DEBUG;

//main
void init();
void update();
void late_update();
void end();


// functionality
float distance(Vector2 a, Vector2 b);

#endif