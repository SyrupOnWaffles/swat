#include "raylib.h"
#include "stdio.h" 
#include "conversion.h"
#include "math.h"

#define tileSize 64
#define halfTile tileSize / 2
#define tileCenter tileSize * 6.015625
/**
 * @brief simple coordinate system with two floats
 * 
 */
typedef struct coordinates
{
    float x; 
    float y; 
}coordinates;

/**
 * @brief map data class. contains a textures list floor map, prop map and collision map
 * 
 */
typedef struct map
{
    Texture2D key[16];
    int floor[32][32];
    int props[32][32];
    int collision[32][32];

    
}map;
/**
 * @brief draw map data type with several parameters
 * 
 * @param level map data type
 * @param sizex how many tiles to render on the x axis
 * @param sizey how many tiles to render on the y axis
 * @param offset coordinate x and y offset
 */
void drawMap(map level, int sizex, int sizey, coordinates offset){
    for (int fy = 0; fy < sizey; fy++)
            {
                for (int fx = sizex; fx > 0; fx--)
                {
                    coordinates tilecoord = {fx,fy}; 
                    cti(&tilecoord.x,&tilecoord.y);
                    // Vector2 tile = {tilecoord.x*tileSize + ((1280 / 2) - 4.5 * tileSize), tilecoord.y*tileSize+ (720/2 - tileSize)};
                    Vector2 tile = {(tilecoord.x*tileSize -tileSize + tileCenter), tilecoord.y*tileSize + 360};
                    // Vector2 tile = {(tilecoord.x*tileSize), tilecoord.y*tileSize};
                    DrawTextureEx(level.key[level.floor[fy + (int)offset.y][fx - 1 + (int)offset.x] - 1], tile, 0, 2, WHITE);
                    tile.y -= halfTile;
                    DrawTextureEx(level.key[level.props[fy][fx - 1] - 1], tile, 0, 2, WHITE);
                    // DrawTextureEx(concrete, tile, 0, 2, WHITE);

                }
                
            }
}
int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    coordinates mapOffset = {0,0};

    InitWindow(screenWidth, screenHeight, "Isometric World");

    map test = {{LoadTexture("resources/waterTile.png"),
     LoadTexture("resources/concreteTile.png"),
     LoadTexture("resources/tableTile.png"),
     LoadTexture("resources/tableEndTile1.png"),
     LoadTexture("resources/tableEndTile2.png"),
     LoadTexture("resources/swatCharacter.png")},{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                          {1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    }};

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // printf("%i %i \n", GetMouseX(),GetMouseY());

        coordinates mouse = {((GetMouseX() + tileSize - tileCenter) * 1.0) / (halfTile), (GetMouseY() * 1.0 - 360) / (halfTile)};
        itc(&mouse.x,&mouse.y);
        coordinates selectedcoord = {roundf(mouse.x / 2),roundf(mouse.y / 2) - 1};
        printf("%i %i \n", (int)selectedcoord.x,(int)selectedcoord.y);
        
        cti(&selectedcoord.x,&selectedcoord.y);
        Vector2 selected = {(selectedcoord.x*tileSize -tileSize + tileCenter), selectedcoord.y*tileSize + 360};
        selected.y -= halfTile;

        // Vector2 selected = {selectedcoord.x*tileSize - halfTile,selectedcoord.y*tileSize};

        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            drawMap(test,8,8, mapOffset);
            DrawTextureEx(test.key[5], selected, 0, 2, WHITE);
            
            DrawFPS(0,0);
        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    for (int i = 0; i < 4; i++)
    {
       UnloadTexture(test.key[i]);
    }
           // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

