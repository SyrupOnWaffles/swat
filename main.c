#include "raylib.h"
#include "stdio.h" 
#include "conversion.h"
#include "math.h"

#define tileSize 64
#define tileCenter tileSize * 6.015625
typedef struct coordinates
{
    float x; 
    float y; 
}coordinates;

typedef struct map
{
    Texture2D key[16];
    int floor[32][32];
    int props[32][32];
    
}map;

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Isometric World");

    map test = {{LoadTexture("resources/waterTile.png"),
     LoadTexture("resources/concreteTile.png"),
     LoadTexture("resources/tableTile.png"),
     LoadTexture("resources/tableEndTile1.png"),
     LoadTexture("resources/tableEndTile2.png")},{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},

                         {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    }};

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // printf("%i %i \n", GetMouseX(),GetMouseY());

        coordinates mouse = {(GetMouseX() * 1.0) / (tileSize / 2), GetMouseY() * 1.0 / (tileSize / 2)};
        itc(&mouse.x,&mouse.y);
        coordinates selectedcoord = {roundf(mouse.x / 2),roundf(mouse.y / 2)};
        printf("%f %f \n", selectedcoord.x,selectedcoord.y);
        
        cti(&selectedcoord.x,&selectedcoord.y);
        Vector2 selected = {selectedcoord.x*tileSize, selectedcoord.y*tileSize};
        // Vector2 selected = {selectedcoord.x*tileSize - tileSize / 2,selectedcoord.y*tileSize};

        BeginDrawing();

            ClearBackground(RAYWHITE);
            for (int fy = 0; fy < 8; fy++)
            {
                for (int fx = 8; fx > 0; fx--)
                {
                    coordinates tilecoord = {fx,fy}; 
                    cti(&tilecoord.x,&tilecoord.y);
                    // Vector2 tile = {tilecoord.x*tileSize + ((1280 / 2) - 4.5 * tileSize), tilecoord.y*tileSize+ (720/2 - tileSize)};
                    Vector2 tile = {(tilecoord.x*tileSize -tileSize + tileCenter), tilecoord.y*tileSize + 360};
                    // Vector2 tile = {(tilecoord.x*tileSize), tilecoord.y*tileSize};
                    DrawTextureEx(test.key[test.floor[fy][fx - 1] - 1], tile, 0, 2, WHITE);
                    tile.y -= tileSize / 2;
                    DrawTextureEx(test.key[test.props[fy][fx - 1] - 1], tile, 0, 2, WHITE);

                    // DrawTextureEx(concrete, tile, 0, 2, WHITE);

                }
                
            }
            DrawTextureEx(test.key[0], selected, 0, 2, WHITE);
            
            DrawFPS(0,0);
        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(test.key[0]);
    UnloadTexture(test.key[1]);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

