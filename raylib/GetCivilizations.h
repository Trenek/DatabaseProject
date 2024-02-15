#ifndef CIVILIZATION_H
#define CIVILIZATION_H

#ifndef RAYLIB_H
#ifndef COLOR_S
#define COLOR_S
typedef struct Color {
    unsigned char r;        // Color red value
    unsigned char g;        // Color green value
    unsigned char b;        // Color blue value
    unsigned char a;        // Color alpha value
} Color;
#endif
#endif

struct Civilization {
	int CivilizationID;
    char name[255];
    Color color;
};

struct Civilization* GetCivilizations(int mapID);
struct Civilization* GetSessionCivilizations(int sessionID);

#endif