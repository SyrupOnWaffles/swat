#include "raylib.h"
#include "stdio.h" 
#include "conversion.h"
#include "math.h"

#define tileSize 64
typedef struct coordinates
{
    float x; 
    float y; 
}coordinates;

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Isometric World");
    Texture2D texture = LoadTexture("resources/waterTile.png");      
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        coordinates mouse = {GetMouseX() * 1.0 / (tileSize / 2), GetMouseY() * 1.0 / (tileSize / 2)};
        itc(&mouse.x,&mouse.y);
        coordinates selectedcoord = {roundf(mouse.x / 2),roundf(mouse.y / 2)};
        cti(&selectedcoord.x,&selectedcoord.y);
        Vector2 selected = {selectedcoord.x*tileSize - tileSize / 2,selectedcoord.y*tileSize - tileSize / 1.5};

        BeginDrawing();

            ClearBackground(RAYWHITE);
            for (int fy = 0; fy < 8; fy++)
            {
                for (int fx = 8; fx > 0; fx--)
                {
                    coordinates tilecoord = {fx,fy}; 
                    cti(&tilecoord.x,&tilecoord.y);
                    // Vector2 tile = {tilecoord.x*tileSize + ((1280 / 2) - 4.5 * tileSize), tilecoord.y*tileSize+ (720/2 - tileSize)};
                    Vector2 tile = {tilecoord.x*tileSize , tilecoord.y*tileSize};
                    DrawTextureEx(texture, tile, 0, 2, WHITE);
                }
                
            }
            DrawTextureEx(texture, selected, 0, 2, WHITE);
            
            DrawFPS(0,0);
            DrawText("this IS a texture!", 360, 370, 10, GRAY);
        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

