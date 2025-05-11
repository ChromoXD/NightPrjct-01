#include "NightPrjtHdr.hpp"

Vector3 Player_Movement() {
    //Maigc Salts...
    float cosFun = 0;
    float sinFun = 0;
   float jumpFun = 0;
    float Move_Y = 0;
    float Move_X = 0;
    float Normalises_speed = (float)2 / 3;


    //Movemnt Magic
    if (IsKeyDown(KEY_W) ||
        IsKeyDown(KEY_A) ||
        IsKeyDown(KEY_S) ||
        IsKeyDown(KEY_D))
    {
        //Run Magic
        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            Mvmt_Speed = 0.06f;
            if (camera.fovy <= 100)
            {
                amplitude = 0.004f;
                frequency = 50;
                camera.fovy += 2.5;
            }
        }
        //Sneak Magic
        else if (IsKeyDown(KEY_LEFT_SHIFT)) {
            Mvmt_Speed = 0.01f;
            if (camera.fovy > 80)
            {
                frequency = 10;
                amplitude = 0.001f;
                camera.fovy -= 2.5;
            }
        }
        //No Run no Walk Magic
        else {
            Mvmt_Speed = 0.03f;
            if (camera.fovy > 90) camera.fovy -= 2.5;
            if (camera.fovy < 90) camera.fovy += 2.5;


            frequency = 30;
            amplitude = 0.002f;
        }
    }

    //X-Axis Movement
    Move_X = Mvmt_Speed * (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));

    //Y-Axis Movement
    Move_Y = Mvmt_Speed * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));

    //Movemnt Normalization Magic
    if ((IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) ||
        (IsKeyDown(KEY_D) && IsKeyDown(KEY_S)) ||
        (IsKeyDown(KEY_A) && IsKeyDown(KEY_S)) ||
        (IsKeyDown(KEY_A) && IsKeyDown(KEY_W))) {
        Move_X = Move_X * Normalises_speed;
        Move_Y = Move_Y * Normalises_speed;
    }

    //View Bob Magic
    if (IsKeyDown(KEY_W) ||
        IsKeyDown(KEY_A) ||
        IsKeyDown(KEY_S) ||
        IsKeyDown(KEY_D)) {
        sinFun = sin(GetTime() * frequency) * amplitude;
        cosFun = cos(GetTime() * frequency / 2) * amplitude;
    }

    auto start = 0.0f;
    auto end = 0.0f;

    //Jump Magic
    if (camera.position.y < 2)
    {
        jumpFun -= Player_Y_Velocity;
        Player_Y_Velocity += gravity;
    }
    else
    {
        jumpFun = 2;
    }


    //Final Magical Values
    return { Move_X + cosFun , Move_Y + sinFun, jumpFun + cosFun };
}