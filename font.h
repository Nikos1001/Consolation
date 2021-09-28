
#ifndef CONSOLATIONTEST_FONT_H
#define CONSOLATIONTEST_FONT_H

// Generated using https://evanw.github.io/font-texture-generator/

typedef struct Character {
    int codePoint, x, y, width, height, originX, originY;
} consolation_Character;

typedef struct consolation_Font {
    const char *name;
    int size, bold, italic, width, height, characterCount;
    consolation_Character *characters;
} consolation_Font;

static consolation_Character characters_Courier[] = {
        {' ', 480, 141, 12, 12, 6, 6},
        {'!', 101, 78, 18, 32, -1, 26},
        {'"', 315, 141, 21, 20, 1, 28},
        {'#', 237, 0, 32, 36, 6, 28},
        {'$', 85, 0, 26, 38, 3, 28},
        {'%', 283, 45, 25, 33, 3, 26},
        {'&', 215, 110, 26, 30, 3, 24},
        {'\'', 336, 141, 16, 20, -2, 28},
        {'(', 111, 0, 19, 38, 0, 25},
        {')', 130, 0, 19, 38, 0, 25},
        {'*', 218, 141, 25, 25, 3, 25},
        {'+', 241, 110, 29, 29, 5, 24},
        {',', 243, 141, 19, 23, 0, 11},
        {'-', 421, 141, 27, 16, 4, 15},
        {'.', 374, 141, 19, 18, 0, 12},
        {'/', 149, 0, 25, 37, 3, 29},
        {'0', 308, 45, 25, 33, 3, 27},
        {'1', 27, 78, 25, 32, 2, 26},
        {'2', 231, 45, 26, 33, 4, 27},
        {'3', 349, 0, 26, 34, 3, 27},
        {'4', 52, 78, 25, 32, 3, 26},
        {'5', 257, 45, 26, 33, 3, 26},
        {'6', 401, 0, 25, 34, 3, 27},
        {'7', 333, 45, 25, 33, 3, 26},
        {'8', 426, 0, 25, 34, 3, 27},
        {'9', 375, 0, 26, 34, 3, 27},
        {':', 199, 141, 19, 27, 0, 20},
        {';', 196, 110, 19, 31, 0, 20},
        {'<', 333, 110, 29, 28, 5, 24},
        {'=', 262, 141, 29, 20, 5, 20},
        {'>', 362, 110, 29, 28, 5, 24},
        {'?', 77, 78, 24, 32, 2, 26},
        {'@', 298, 0, 24, 36, 3, 28},
        {'A', 119, 78, 32, 31, 6, 25},
        {'B', 335, 78, 29, 31, 5, 25},
        {'C', 476, 45, 28, 32, 5, 25},
        {'D', 364, 78, 29, 31, 5, 25},
        {'E', 393, 78, 29, 31, 5, 25},
        {'F', 422, 78, 29, 31, 5, 25},
        {'G', 358, 45, 30, 32, 5, 25},
        {'H', 451, 78, 29, 31, 5, 25},
        {'I', 145, 110, 26, 31, 3, 25},
        {'J', 480, 78, 29, 31, 4, 25},
        {'K', 245, 78, 30, 31, 5, 25},
        {'L', 0, 110, 29, 31, 5, 25},
        {'M', 183, 78, 31, 31, 6, 25},
        {'N', 275, 78, 30, 31, 6, 25},
        {'O', 418, 45, 29, 32, 5, 25},
        {'P', 29, 110, 29, 31, 5, 25},
        {'Q', 269, 0, 29, 36, 5, 25},
        {'R', 305, 78, 30, 31, 5, 25},
        {'S', 0, 78, 27, 32, 4, 25},
        {'T', 58, 110, 29, 31, 5, 25},
        {'U', 388, 45, 30, 32, 5, 25},
        {'V', 214, 78, 31, 31, 6, 25},
        {'W', 151, 78, 32, 31, 6, 25},
        {'X', 87, 110, 29, 31, 5, 25},
        {'Y', 116, 110, 29, 31, 5, 25},
        {'Z', 171, 110, 25, 31, 3, 25},
        {'[', 199, 0, 19, 37, 0, 25},
        {'\\', 174, 0, 25, 37, 3, 29},
        {']', 218, 0, 19, 37, 0, 25},
        {'^', 291, 141, 24, 20, 2, 28},
        {'_', 448, 141, 32, 15, 6, 1},
        {'`', 352, 141, 22, 18, 2, 28},
        {'a', 391, 110, 29, 28, 4, 21},
        {'b', 451, 0, 30, 33, 5, 27},
        {'c', 478, 110, 28, 28, 5, 21},
        {'d', 481, 0, 30, 33, 5, 27},
        {'e', 420, 110, 29, 28, 5, 21},
        {'f', 177, 45, 27, 33, 3, 27},
        {'g', 90, 45, 29, 33, 4, 21},
        {'h', 119, 45, 29, 33, 5, 27},
        {'i', 322, 0, 27, 34, 4, 28},
        {'j', 15, 0, 24, 40, 3, 28},
        {'k', 0, 45, 30, 33, 5, 27},
        {'l', 204, 45, 27, 33, 3, 27},
        {'m', 26, 141, 32, 27, 6, 21},
        {'n', 58, 141, 29, 27, 5, 21},
        {'o', 449, 110, 29, 28, 5, 21},
        {'p', 30, 45, 30, 33, 5, 21},
        {'q', 148, 45, 29, 33, 5, 21},
        {'r', 145, 141, 28, 27, 4, 21},
        {'s', 0, 141, 26, 28, 3, 21},
        {'t', 447, 45, 29, 32, 5, 25},
        {'u', 87, 141, 29, 27, 5, 21},
        {'v', 302, 110, 31, 28, 6, 21},
        {'w', 270, 110, 32, 28, 6, 21},
        {'x', 116, 141, 29, 27, 5, 21},
        {'y', 60, 45, 30, 33, 5, 21},
        {'z', 173, 141, 26, 27, 3, 21},
        {'{', 39, 0, 23, 39, 2, 27},
        {'|', 0, 0, 15, 45, -2, 31},
        {'}', 62, 0, 23, 39, 2, 27},
        {'~', 393, 141, 28, 16, 4, 18},
};

static consolation_Font consolation_font_Courier = {"Courier", 32, 0, 0, 511, 169, 95, characters_Courier};

#endif