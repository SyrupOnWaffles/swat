#include "raylib.h"
#include "stdio.h"
#include "conversion.h"
#include "math.h"

#define tileSize 64

#define halfTile tileSize / 2
#define tileCenter tileSize * 6.015625

const int screenWidth = 1280;
const int screenHeight = 720;

/**
 * @brief simple coordinate system with two floats
 *
 */
typedef struct coordinates
{
    float x;
    float y;
} coordinates;

/**
 * @brief map data class. contains a textures list floor map, prop map and collision map
 *
 */
typedef struct map
{
    Texture2D key[16];
    char floor[32][32];
    char props[32][32];
    char collision[32][32];

} map;
/**
 * @brief draw map data type with several parameters
 *
 * @param level map data type
 * @param sizex how many tiles to render on the x axis
 * @param sizey how many tiles to render on the y axis
 * @param offset coordinate x and y offset
 * @param layer 1: floor, 2: props, 4:collision
 */
void drawMap(map level, int sizex, int sizey, coordinates offset, char layer)
{
    for (int fy = 0; fy < sizey; fy++)
    {
        for (int fx = sizex; fx > 0; fx--)
        {
            coordinates tilecoord = {fx, fy};
            cti(&tilecoord.x, &tilecoord.y);
            // Vector2 tile = {tilecoord.x*tileSize + ((1280 / 2) - 4.5 * tileSize), tilecoord.y*tileSize+ (720/2 - tileSize)};
            Vector2 tile = {(tilecoord.x * tileSize - tileSize + tileCenter), tilecoord.y * tileSize + 360};
            // Vector2 tile = {(tilecoord.x*tileSize), tilecoord.y*tileSize};
            switch (layer)
            {
            case 1:
                DrawTextureEx(level.key[level.floor[fy + (int)offset.y][fx - 1 + (int)offset.x] - 1], tile, 0, 2, WHITE);
                break;

            case 2:
                tile.y -= halfTile;
                DrawTextureEx(level.key[level.props[fy + (int)offset.y][fx - 1 + (int)offset.x] - 1], tile, 0, 2, WHITE);
                break;
            default:
                break;
            }
            // DrawTextureEx(concrete, tile, 0, 2, WHITE);
        }
    }
}
/**
 * @brief Get the tile number you are hovering over
 *
 * @return vector2
 */

int main(void)
{
    coordinates mapOffset = {0, 0};

    InitWindow(screenWidth, screenHeight, "Isometric World");

    map test = {{
                    LoadTexture("resources/swatCharacter.png"),
                    // LoadTexture("resources/swatCharacter.png"),
                    LoadTexture("resources/highlight.png"),
                    // LoadTexture("resources/swatCharacter.png"),
                    LoadTexture("resources/doorTile.png"),
                    LoadTexture("resources/waterTile.png"),
                    LoadTexture("resources/concreteTile.png"),
                    LoadTexture("resources/tableTile.png"),
                    LoadTexture("resources/tableEndTile1.png"),
                    LoadTexture("resources/tableEndTile2.png"),
                },
                {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
                 {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}},

                {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
                 
                {{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}}};

    coordinates selectedcoord;
    Vector2 selected;
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // printf("%i %i \n", GetMouseX(),GetMouseY());
        Vector2 playerDrawPosition = {570, 420};

        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawMap(test, 8, 8, mapOffset, 1);
        DrawTextureEx(test.key[0], playerDrawPosition, 0, 2, WHITE);
        drawMap(test, 8, 8, mapOffset, 2);

        // DrawFPS(0, 0);
        EndDrawing();

    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    for (int i = 0; i < sizeof(test.key) / sizeof(test.key[0]); i++)
    {
        UnloadTexture(test.key[i]);
    }
    // Texture unloading

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
