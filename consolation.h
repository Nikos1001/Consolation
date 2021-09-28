
#ifndef CONSOLATION_LIBRARY_H
#define CONSOLATION_LIBRARY_H

#include "vendor/glew/include/GL/glew.h"
#include "vendor/glfw/include/GLFW/glfw3.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

struct consolation_Cell {
    uint8_t character;
    uint32_t fgColor, bgColor;
    uint8_t weight;
};

struct consolation_Vertex {
    float x;
    float y;
    float u;
    float v;
    float fgR;
    float fgG;
    float fgB;
    float bgR;
    float bgG;
    float bgB;

    float left, bottom;
    float right, top;

    float weight;
};

struct consolation_Window {
    GLFWwindow* window;
    int rows, cols;

    struct consolation_Cell* cells;
    struct consolation_Vertex* vertices;

    bool initialized;
    GLuint vbo;
    GLuint vao;
    GLuint shader;
    GLuint font;
};

static bool consolation_initializedGlew = false;

void consolation_init(const char* resPath);
void consolation_updateFrame();
void consolation_free();

void consolation_initWindow(struct consolation_Window* window, int cols, int rows, const char* name);
void consolation_renderWindow(struct consolation_Window* window);
bool consolation_shouldWindowClose(struct consolation_Window* window);
void consolation_freeWindow(struct consolation_Window* window);

struct consolation_Cell* consolation_getCell(struct consolation_Window* window, int col, int row);
void consolation_clear(struct consolation_Window* window);
void consolation_setResolution(struct consolation_Window* window, int cols, int rows);

void consolation_writeString(struct consolation_Window* window, int col, int row, const char* text);

#define CONSOLATION_DEFINE_CELL_SETTER_H(property, propertyName, type) \
    void consolation_set ## propertyName (struct consolation_Window* window, int col, int row, type val);

#define CONSOLATION_DEFINE_CELL_SETTER(property, propertyName, type) \
    void consolation_set ## propertyName (struct consolation_Window* window, int col, int row, type val) { \
        struct consolation_Cell* cell = consolation_getCell(window, col, row);                                                \
        if(cell == NULL)                                 \
            return;                                      \
        cell->property = val;                            \
    }                                                    \

#define CONSOLATION_PROPERTY_SETTERS \
    SETTER(character, Char, uint8_t) \
    SETTER(fgColor, FG, uint32_t)    \
    SETTER(bgColor, BG, uint32_t)    \
    SETTER(weight, Weight, uint8_t)    \

#define SETTER(property, propertyName, type) CONSOLATION_DEFINE_CELL_SETTER_H(property, propertyName, type)
CONSOLATION_PROPERTY_SETTERS
#undef SETTER

#endif
