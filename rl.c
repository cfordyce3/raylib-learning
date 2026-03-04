#include <stdio.h>
#include "raylib.h"

int main () {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;


    InitWindow(screenWidth, screenHeight, "Raylib Learning Environment");
    SetExitKey(KEY_CAPS_LOCK); // must be after the init window

    SetTargetFPS(240);

    // player facing
    typedef enum {
        UP = 90,
        DOWN = 270,
        LEFT = 180,
        RIGHT = 0,
        UPLEFT = 135,
        UPRIGHT = 45,
        DOWNLEFT = 225,
        DOWNRIGHT = 315
    } Direction;

    // Player starts in middle of screen
    Vector2 playerPosition = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    // Player starts facing right
    Direction playerDirection = RIGHT;
    // Player x and y speed start at 0
    Vector2 playerSpeed = { 0.0f, 0.0f };
    bool playerMoving = false;
    


    const float speedTarget = 200.0f;
    float currentSpeed = 0;
    const float circleRadius = 16.0f;


    while (!WindowShouldClose()) {
        // Update
        // --------------------------------------------------

        // keys not pressed together
        if ( 
                ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))) ||
                ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)))
        ) { // speed is zero and thus is not moving
            currentSpeed = 0;
            playerMoving = false;
        }
        else if (
                IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || 
                IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ||
                IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ||
                IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)
        ) playerMoving = true;
        else currentSpeed = 0;

        // TODO: figure this math out
        float deltaMoveSpeed = GetFrameTime() * speedTarget;
        float speedDiff = speedTarget - deltaMoveSpeed;
        float speedFinal = speedTarget + speedDiff;

        //printf("target:\t%f\ndeltaspeed:\t%f\nfinal:\t%f\n", speedTarget, deltaMoveSpeed, speedFinal);
        printf("speed x:\t%f\nspeed y:\t%f\n", playerSpeed.x, playerSpeed.y);

        if (!playerMoving) playerSpeed.x = 0; playerSpeed.y = 0;
        // movement keys
        // TODO: add IsKeyPressed event to properly handle speed
        //       such that when you press a key once, it adds the directional 
        //       speed to the total (two keys pressed = more speed)
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) { 
            playerPosition.y -= deltaMoveSpeed;
            currentSpeed = speedTarget;
            playerSpeed.y = deltaMoveSpeed;
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) playerDirection = UPLEFT;
            else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) playerDirection = UPRIGHT;
            else playerDirection = UP;
        }
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            playerPosition.y += deltaMoveSpeed;
            currentSpeed = speedTarget;
            playerSpeed.y = deltaMoveSpeed;
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) playerDirection = DOWNLEFT;
            else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) playerDirection = DOWNRIGHT;
            else playerDirection = DOWN;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            playerPosition.x -= deltaMoveSpeed;
            currentSpeed = speedTarget;
            playerSpeed.x = deltaMoveSpeed;
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) playerDirection = UPLEFT;
            else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) playerDirection = DOWNLEFT;
            else playerDirection = LEFT;
        }
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            playerPosition.x += deltaMoveSpeed;
            currentSpeed = speedTarget;
            playerSpeed.x = deltaMoveSpeed;
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) playerDirection = UPRIGHT;
            else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) playerDirection = DOWNRIGHT;
            else playerDirection = RIGHT;
        }

        if (playerPosition.x > screenWidth) playerPosition.x = 0;
        if (playerPosition.x < 0) playerPosition.x = screenWidth;
        if (playerPosition.y > screenHeight) playerPosition.y = 0;
        if (playerPosition.y < 0) playerPosition.y = screenHeight;

        if (IsKeyPressed(KEY_R)) {
            playerPosition.x = (float)screenWidth / 2.0f;
            playerPosition.y = (float)screenHeight / 2.0f;
            playerDirection = RIGHT;
        }


        // --------------------------------------------------
        // Draw
        // --------------------------------------------------
        BeginDrawing(); // start drawing and quasi block
            ClearBackground(BLACK); // white background

            // Draw player to screen
            DrawCircleV(playerPosition, circleRadius, RED);

            // Draw FPS
            //const char *fpsText = 0;
            //if (currentFPS <= 0) fpsText = TextFormat("FPS: unlimited (%i)", GetFPS());
            //else fpsText = TextFormat("FPS: %i", GetFPS());
            //DrawText(fpsText, 10, 10, 20, DARKGRAY);

            // Player speed 
            // TODO: get actual speed of player
            char playerMovingText = 'N';
            (playerMoving) ? playerMovingText = 'Y' : 'N';
            DrawText(TextFormat("Player moving? %c | speed? %f", playerMovingText, (playerMoving) ? currentSpeed : 0), 10, 10, 20, YELLOW);

            // player position
            DrawText(TextFormat("Player Position: \nX: %f\nY: %f", playerPosition.x, playerPosition.y), 10, 70, 20, GREEN);

            // player direction
            const char* directionText = "Right";
            switch (playerDirection) {
                case 90: directionText = "Up"; break;
                case 270: directionText = "Down"; break;
                case 180: directionText = "Left"; break;
                case 0: directionText = "Right"; break;
                case 135: directionText = "Up Left"; break;
                case 45: directionText = "Up Right"; break;
                case 225: directionText = "Down Left"; break;
                case 315: directionText = "Down Right"; break;
                default: directionText = "Error"; break;
            }
            DrawText(TextFormat("Player Direction: %s", directionText), 10, 40, 20, BLUE);

        EndDrawing(); // end drawing and end quasi block
    }

    CloseWindow();

    return 0;
}
