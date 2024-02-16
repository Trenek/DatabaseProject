#ifndef GRIDTILE_H
    #include <stdbool.h>
    
    #include "GetCivilizations.h"

    #define GRIDTILE_H
    #ifndef RAYLIB_H
        typedef struct Texture {
            unsigned int id;        // OpenGL texture id
            int width;              // Texture base width
            int height;             // Texture base height
            int mipmaps;            // Mipmap levels, 1 by default
            int format;             // Data format (PixelFormat type)
        } Texture;

        typedef Texture Texture2D;

        #ifndef COLOR_S
        #define COLOR_S
            typedef struct Color {
                unsigned char r;        // Color red value
                unsigned char g;        // Color green value
                unsigned char b;        // Color blue value
                unsigned char a;        // Color alpha value
            } Color;
        #endif

        // Vector2, 2 components
        typedef struct Vector2 {
            float x;                // Vector x component
            float y;                // Vector y component
        } Vector2;

        typedef struct Camera2D {
            Vector2 offset;         // Camera offset (displacement from target)
            Vector2 target;         // Camera target (rotation and zoom origin)
            float rotation;         // Camera rotation in degrees
            float zoom;             // Camera zoom (scaling), should be 1.0f by default
        } Camera2D;
    #endif

    struct GridTile {
        Vector2 screen_coordinates;
        Color color;
        Texture2D* texture;
        bool isClicked;
        int CityID;
        int regionID;
        int civilizationID;
        long long civilizationNumber;
        bool isCapital;
    };

    struct GridTile** allocMapGridTile(int width, int height, Texture2D* texture, int mapID);
    struct GridTile** allocSessionGridTile(int width, int height, Texture2D* texture, int sessionID);
    void checkClick(int height, int width, int radius, struct GridTile** grid, Vector2* clicked, Camera2D camera);
    void GenerateHexGrid(int radius, int width, int height, struct GridTile** grid);
    void DrawVisibleFields(int radius, int width, int height, struct GridTile** grid, Texture2D* house);
    void DEBUG_DrawCoordinatesOnHexGrid(int radius, int width, int height, struct GridTile** grid);
    void DrawHexGridOutline(int radius, int width, int height, struct GridTile** grid);
    void DrawPoliticalDivision(int radius, int width, int height, struct GridTile** grid, struct Civilization* civilizations);
    void DrawCity(int radius, int width, int height, struct GridTile** grid, Texture2D* house);
    void DrawChosenPoliticalGridOutline(int radius, int width, int height, struct GridTile** grid, int chosenID);
    void DrawNormalPoliticalGridOutline(int radius, int width, int height, struct GridTile** grid, int playerID, Color playerColor);
    void DrawClickedProvince(int radius, int width, int height, struct GridTile** grid);
    void DrawClickedCivilization(int radius, int width, int height, struct GridTile** grid);
#endif