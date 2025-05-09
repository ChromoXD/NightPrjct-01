#include <raylib.h>
#include <iostream>

//Fix wave like motion to more walking kind of motion


void Start();
void Update();
bool AllKeyCheck();
Vector3 Player_Movement();
Vector3 Player_Rotation();

unsigned int Height = 700;
unsigned int Width = 1000;
const char Title[] = "NightPrjct";

float Mvmt_Speed;
float Rtt_Speed = 0.1f;

Model Gun01_model;
Texture2D Gun01_Texture;

Mesh cube01;
Model Cube_Mdl;
Texture2D Floor_Txtr;

Shader Tile_shader;
Camera3D camera;

int main()
{


    camera = { 
    { 0.0f, 0.5f, 0.0f },
    { 1.0f, 0.5f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 90 },
    { CAMERA_PERSPECTIVE }
    };


    InitWindow(Width, Height, Title);

    
    Start();

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYBLACK);
            BeginMode3D(camera);
                UpdateCameraPro(&camera, Player_Movement(), Player_Rotation(), 0);
        
                Update();

            EndMode3D();
        EndDrawing();
    }
}

void Start() {
    SetTargetFPS(60);

    HideCursor();
    DisableCursor();

    Gun01_model = LoadModel("GLB format/blaster-a.glb");
    Gun01_Texture = LoadTexture("GLB format/Textures/colormap.png");

    //Cube
    cube01 = GenMeshCube(1000.0f, 1.0f, 1000.0f);
    Cube_Mdl = LoadModelFromMesh(cube01);

    Floor_Txtr = LoadTexture("GLB format/Textures/Floor_Txtr.png");
    Cube_Mdl.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = Floor_Txtr;

    float tiling[2] = {30.0f, 30.0f};
    Tile_shader = LoadShader(0, TextFormat("GLB format/Textures/tiling.fs", 330));
    SetShaderValue(Tile_shader, GetShaderLocation(Tile_shader, "tiling"), tiling, SHADER_UNIFORM_VEC2);
    Cube_Mdl.materials[0].shader = Tile_shader;


    //SetMaterialTexture(&Gun01_model.materials[0], MATERIAL_MAP_DIFFUSE, Gun01_Texture);
    
}

void Update() {


    DrawGrid(100, 0.5);

    BeginShaderMode(Tile_shader);
        DrawModel(Cube_Mdl, {0,0,0}, 0.1, WHITE);
    EndShaderMode();

    DrawModelEx(Gun01_model, {0, 0, 0}, {0,0,0}, -90.0f, {1.0f, 1.0f, 1.0f}, WHITE);
}

Vector3 Player_Movement() {

    float frequency = 30;
    float amplitude = 0.005f;

    float cosFun = 0;
    float sinFun = 0;

    float Move_Y = 0;
    float Move_X = 0;

    if (IsKeyDown(KEY_LEFT_CONTROL))
    {
        Mvmt_Speed = 0.06f;
        if (AllKeyCheck) {
            if (camera.fovy <= 100)
            {
                frequency = 50;
                camera.fovy += 2.5;
            }
        }
    }
    else {
        Mvmt_Speed = 0.03f;
        if (camera.fovy > 90) camera.fovy -= 2.5;
    } 

    //X-Axis Movement
    Move_X = Mvmt_Speed * (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));


    //Y-Axis Movement
    Move_Y = Mvmt_Speed * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));

    if (AllKeyCheck()) {
        sinFun = sin(GetTime() * frequency) * amplitude;
        cosFun = cos(GetTime() * frequency / 2) * amplitude *2 ;
    }


    return { Move_X + cosFun , Move_Y + sinFun, cosFun };
}

Vector3 Player_Rotation() {

    //X-Axis Rotation
    float RttX = Rtt_Speed * GetMouseDelta().x;

    //Y-Axis Rotation
    float RttY = Rtt_Speed * GetMouseDelta().y;

    float RttZ = 0;
    float rtn_Cntr = 0;

    if (IsKeyUp(KEY_A) || IsKeyUp(KEY_A) && rtn_Cntr != 0)
    {
        RttZ = 0;
        rtn_Cntr = 0;
    }

    if (IsKeyDown(KEY_A))
    {
        if (rtn_Cntr >= -1) {
            RttZ -= 0.1;
            rtn_Cntr -= 0.1;
        }
        else
        {
            RttZ += 0.1;
        }
    }

    if (IsKeyDown(KEY_D))
    {
        if (rtn_Cntr <= 1) {
            RttZ += 0.1;
            rtn_Cntr += 0.1;
        }
        else
        {
            RttZ -= 0.1;
        }

    }

    std::cout << rtn_Cntr << " " << RttZ;

    return {RttX, RttY, RttZ };
}

bool AllKeyCheck() {
    if (IsKeyDown(KEY_W) ||
        IsKeyDown(KEY_A) ||
        IsKeyDown(KEY_S) ||
        IsKeyDown(KEY_D)) return true;
    else return false;
}