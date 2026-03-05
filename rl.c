#include <stdio.h>
#include <math.h>
#include "raylib.h"

// direction enum
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

// calculate the line end via the player position and direction
Vector2 calcLineEnd (Vector2 pPos, float r, Direction d);

int main () {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib Learning Environment");
    SetExitKey(KEY_CAPS_LOCK); // must be after the init window

    SetTargetFPS(240);

    // Player starts in middle of screen
    const float circleRadius = 16.0f;
    Vector2 playerPosition = {(float)screenWidth / 2.0f, (float)screenHeight / 2.0f};
    // Player starts facing right
    Direction playerDirection = RIGHT;
    // Player x and y speed start at 0
    Vector2 playerSpeed = { 0.0f, 0.0f };
    bool playerMoving = false;

    // player direction line init
    Vector2 lineStart = playerPosition;//{playerPosition.x, playerPosition.y};
    Vector2 lineEnd = {playerPosition.x + circleRadius, playerPosition.y};

    const float speedTarget = 200.0f;
    float currentSpeed = 0;
    float deltaMoveSpeed = 0;

    while (!WindowShouldClose()) {
        // Update
        // --------------------------------------------------
        // move speed via delta
        deltaMoveSpeed = GetFrameTime() * speedTarget;

        // player direction logic
        //lineStart.x = playerPosition.x; lineStart.y = playerPosition.y;
        lineStart = playerPosition;
        lineEnd = calcLineEnd(playerPosition, circleRadius, playerDirection);

        const char* directionText = "Right";
        switch (playerDirection) {
            case UP: directionText = "Up"; break;
            case DOWN: directionText = "Down"; break;
            case LEFT: directionText = "Left"; break;
            case RIGHT: directionText = "Right"; break;
            case UPLEFT: directionText = "Up Left"; break;
            case UPRIGHT: directionText = "Up Right"; break;
            case DOWNLEFT: directionText = "Down Left"; break;
            case DOWNRIGHT: directionText = "Down Right"; break;
            default: directionText = "Invalid Direction"; break;
        }
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
        else playerMoving = false; currentSpeed = 0;


        //printf("speed x:\t%f\nspeed y:\t%f\n", playerSpeed.x, playerSpeed.y);

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

            // TODO: fix this so that there is a line pointing to the player's direction
            if (false) {
                printf("%.2f\t%.2f\t%.2f\t", playerPosition.x, circleRadius, cos(DEG2RAD*(float)playerDirection));
                printf("%.2f\t%.2f\t%.2f\n", playerPosition.y, circleRadius, sin(DEG2RAD*(float)playerDirection));
            }

            lineStart.x = playerPosition.x; lineStart.y = playerPosition.y;
            DrawLineEx(lineStart, lineEnd, 3.0f, GREEN);

            //if (playerMoving) {
            //    printf("direction: %d\n", playerDirection);
            //    printf("start x: %f\tstart y: %f\n", lineStart.x, lineStart.y);
            //    printf("end x: %f\tend y: %f\n", endPointX, endPointY);
            //}

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
            DrawText(TextFormat("Player Direction: %s\t(%d deg)", directionText, playerDirection), 10, 40, 20, BLUE);

        EndDrawing(); // end drawing and end quasi block
    }

    CloseWindow();

    return 0;
}

Vector2 calcLineEnd (Vector2 pPos, float r, Direction d) {
    Vector2 total = {};
    printf("pos: %f, %f\tr: %f\td: %d\n", pPos.x, pPos.y, r, d);
    printf("r * cos(d): %f\tr * sin(d): %f\n", (r*cos(d)), (r*sin(d)));
    switch (d) {
        case UP: total.x = pPos.x; total.y = pPos.y - r; break;
        case DOWN: total.x = pPos.x; total.y = pPos.y + r; break;
        case LEFT: total.x = pPos.x - r; total.y = pPos.y; break;
        case RIGHT: total.x = pPos.x + r; total.y = pPos.y; break;
        case UPRIGHT: total.x = pPos.x + (r * cos(d)); total.y = pPos.y + (r * sin(d)); break;
        case UPLEFT: total.x = pPos.x + (r * cos(d)); total.y = pPos.y + (r * sin(d)); break;
        default: total.x = pPos.x + r; total.y = pPos.y; break;
    }
    return total;
}
//playerPosition.x + circleRadius + cos((float)playerDirection)
//playerPosition.y + circleRadius + sin((float)playerDirection)};
