#include <chrono>
#include <raylib.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include "NightPrjtHdr.hpp"

// Add Gravity
// Add Jump
// Add Some Hands
// Add Some Hand Action


float gravity = 1;
float Player_Y_Velocity = 0;

int Height = GetMonitorHeight(0);
int Width = GetMonitorWidth(0);
const char Title[] = "NightPrjct";

float Mvmt_Speed;
float Rtt_Speed = 0.1f;

Model Gun01_model;
Texture2D Gun01_Texture;

Mesh cube01;
Mesh Player_Mesh;
Model Player_Model;
Model Cube_Mdl;
Texture2D Floor_Txtr;

Shader Tile_shader;
Camera3D camera;
Camera3D FreeCamera;


float frequency = 30;
float amplitude = 0.002f;


float RttZ = 0;
float RttX = 0;
float RttY = 0;
float rtn_Cntr = 0;

void Start();
void Update();


std::stringstream ss;

int main()
{
    camera = { 
    { 0.0f, 0.5f, 0.0f },
    { 1.0f, 0.5f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 90 },
    { CAMERA_PERSPECTIVE }
    };
    
    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_VSYNC_HINT);

    InitWindow(Width, Height, Title);
    SetWindowMonitor(0);
    SetWindowPosition(0, 0);

    Start();

    int FreeCameraMode = CAMERA_FREE;

    while (!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(RAYBLACK);

            BeginMode3D(camera);
                UpdateCameraPro(&camera, Player_Movement(), Player_Rotation(), 0);
            
                Update();

            EndMode3D();

            DrawText(TextFormat("-Movement-"), 550, 0, 40, WHITE);
        EndDrawing();
    }
}

void Start() {
    SetTargetFPS(60);

    HideCursor();
    DisableCursor();

    //Cube
    cube01 = GenMeshCube(1000.0f, 1.0f, 1000.0f);
    Cube_Mdl = LoadModelFromMesh(cube01);
    Floor_Txtr = LoadTexture("GLB format/Textures/Floor_Txtr.png");
    Cube_Mdl.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Floor_Txtr;

    float tiling[2] = {30.0f, 30.0f};
    Tile_shader = LoadShader(0, TextFormat("GLB format/Textures/tiling.fs", 330));
    SetShaderValue(Tile_shader, GetShaderLocation(Tile_shader, "tiling"), tiling, SHADER_UNIFORM_VEC2);
    Cube_Mdl.materials[0].shader = Tile_shader;


    //Player Model
    Player_Mesh = GenMeshCube(1, 10, 1);
    Player_Model = LoadModelFromMesh(Player_Mesh);

    std::cout << Width << " " << Height;
}

void Update() {


    DrawGrid(100, 0.5);

    BeginShaderMode(Tile_shader);
        DrawModel(Cube_Mdl, {0,0,0}, 0.1, WHITE);
        DrawModel(Player_Model, {0,0,0}, 0.1, BLACK);
    EndShaderMode();

    DrawModelEx(Gun01_model, {0, 0, 0}, {0,0,0}, -90.0f, {1.0f, 1.0f, 1.0f}, WHITE);
}
