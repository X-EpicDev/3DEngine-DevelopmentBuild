#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int WinMain()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    float deltaTime = GetFrameTime();


    InitWindow(screenWidth, screenHeight, "3D Camera Test");

    // create the camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 35.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    DisableCursor();                    // Limit cursor to relative movement inside the window
    UpdateCamera(&camera, CAMERA_FREE);

    int across = 10;
    int back = 10;
    int up = 10;

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        deltaTime += GetFrameTime()*1000;

        if(deltaTime >= 16.66f) {
            UpdateCamera(&camera, CAMERA_FREE);
            deltaTime = GetFrameTime()*1000;
        }
        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText(TextFormat("Delta Time: %f", deltaTime), 0, 0, 20, BLACK);
        DrawFPS(0,20);

        BeginMode3D(camera);
        for(int i = 0; i <= across; i++)
        {
            for(int j = 0; j < back; j++)
            {
                for(int k = 0; k < up; k++)
                {

                    DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, BLACK);
                    DrawCubeWires(cubePosition, 1.0f, 1.0f, 1.0f, BLUE);
                    cubePosition.y += 1.5;
                }
                cubePosition.y = 0;
                cubePosition.z -= 1.5;
            }
            cubePosition.z = 0;
            cubePosition.x += 1.5;
        }
        cubePosition.x = 0;



        EndMode3D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}