#ifndef CIVILIZATION_H
#define CIVILIZATION_H

#ifndef RAYLIB_H
typedef struct Color {
    unsigned char r;        // Color red value
    unsigned char g;        // Color green value
    unsigned char b;        // Color blue value
    unsigned char a;        // Color alpha value
} Color;
#endif

struct Civilization {
	int CivilizationID;
    Color color;
};

struct Civilization* GetCivilizations(int* count, int mapID);

#endif