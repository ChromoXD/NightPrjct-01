#pragma once
#include <iostream>
#include <chrono>
#include <raylib.h>

//Magic Salts...
extern int Height;
extern int Width;
extern const char Title[];

extern float Mvmt_Speed;
extern float Rtt_Speed;

extern float frequency;
extern float amplitude;

extern float RttZ;
extern float rtn_Cntr;

extern Camera3D camera;

extern float RttY;
extern float RttX;

extern float gravity;
extern float Player_Y_Velocity;

Vector3 Player_Movement();
Vector3 Player_Rotation();