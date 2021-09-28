
#include "consolation.h"
#include "file.h"
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define CONSOLATION_GET_RED(color) ((float)((color & 0xFF0000) >> 16) / 255.0f)
#define CONSOLATION_GET_GREEN(color) ((float)((color & 0x00FF00) >> 8) / 255.0f)
#define CONSOLATION_GET_BLUE(color) ((float)((color & 0x0000FF) >> 0) / 255.0f)

static const char* consolation_resPath;

static void* reallocate(void* data, size_t size) {
    if(size == 0) {
        free(data);
        return NULL;
    }
    return realloc(data, size);
}

void consolation_init(const char* resPath) {
    consolation_resPath = resPath;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
}

void consolation_updateFrame() {
    if(!consolation_initializedGlew) {
        glewInit();
        glEnable(GL_MULTISAMPLE);
        consolation_initializedGlew = true;
    }
    glfwPollEvents();
}

void consolation_free() {
    glfwTerminate();
}


void consolation_initWindow(struct consolation_Window* window, int cols, int rows, const char* name) {
    window->window = glfwCreateWindow(cols * 12, rows * 18, name, NULL, NULL);
    glfwMakeContextCurrent(window->window);

    window->cells = NULL;
    window->vertices = NULL;
    consolation_setResolution(window, cols, rows);

    window->initialized = false;
}

static void initRendering(struct consolation_Window* window) {
    glGenVertexArrays(1, &window->vao);
    glBindVertexArray(window->vao);

    glGenBuffers(1, &window->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, window->vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct consolation_Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(struct consolation_Vertex), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(struct consolation_Vertex), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(struct consolation_Vertex), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(struct consolation_Vertex), (void*)(10 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(struct consolation_Vertex), (void*)(12 * sizeof(float)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(struct consolation_Vertex), (void*)(14 * sizeof(float)));
    glEnableVertexAttribArray(6);

    int success;
    char infoLog[512];

    size_t pathLen = strlen(consolation_resPath);
    char* path = reallocate(NULL, pathLen + 10);
    memcpy(path, consolation_resPath, pathLen);
    char* filename = path + pathLen;
    memcpy(filename, "vert.glsl", 10);

    const char* vertSource = consolation_readFile(path);
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSource, NULL);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
#ifdef CONSOLATION_DEBUG
    if(!success) {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        printf("Vert shader compilation error: %s\n", infoLog);
    } else {
        printf("Vert shader compiled...\n");
    }
#endif

    memcpy(filename, "frag.glsl", 10);

    const char* fragSource = consolation_readFile(path);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
#ifdef CONSOLATION_DEBUG
    if(!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        printf("Frag shader compilation error: %s\n", infoLog);
    } else {
        printf("Frag shader compiled...\n");
    }
#endif

    window->shader = glCreateProgram();
    glAttachShader(window->shader, vertShader);
    glAttachShader(window->shader, fragShader);
    glLinkProgram(window->shader);
    glGetProgramiv(window->shader, GL_LINK_STATUS, &success);
#ifdef CONSOLATION_DEBUG
    if(!success) {
        glGetProgramInfoLog(window->shader, 512, NULL, infoLog);
        printf("Shader linking error: %s\n", infoLog);
    } else {
        printf("Shader linked.\n");
    }
#endif

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    memcpy(filename, "atlas.png", 10);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    glGenTextures(1, &window->font);
    glBindTexture(GL_TEXTURE_2D, window->font);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    glUniform1i(glGetUniformLocation(window->shader, "uFont"), 0);

    reallocate(path, 0);
}

void consolation_renderWindow(struct consolation_Window* window) {
    glfwMakeContextCurrent(window->window);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    int windowW, windowH;
    glfwGetWindowSize(window->window, &windowW, &windowH);
    float aspect = (float)windowW / (float)windowH;
    float charHeight = 2.0f / (float)window->rows;
    float charWidth = (2.0f / 3.0f) * charHeight / aspect;
    float totalCharWidth = charWidth * (float)window->cols;
    float leftBound = -totalCharWidth / 2;
    float topBound = 1;
    if(totalCharWidth > 2) {
        charWidth = 2.0f / (float)window->cols;
        charHeight = (3.0f / 2.0f) * charWidth * aspect;
        leftBound = -1;
        float totalCharHeight = charHeight * (float)window->rows;
        topBound = totalCharHeight / 2;
    }
    for(int row = 0; row < window->rows; row++) {
        for(int col = 0; col < window->cols; col++) {
            struct consolation_Cell* cell = consolation_getCell(window, col, row);
            struct consolation_Vertex* vertices = window->vertices + 6 * (col + row * window->cols);

            char c = cell->character;

            int charI = c / 9;
            int charJ = c % 9;

            float left = (float)(charI) * (60.0f / 1000.0f) - 0.003f;
            float top = (float)(charJ) * (70.0f / 800.0f) + 0.02f;
            float right = left + (60.0f / 1000.0f);
            float bottom = top + (70.0f / 800.0f);

            vertices[0].x = leftBound + (float)col * charWidth;
            vertices[0].y = topBound - (float)row * charHeight - charHeight;
            vertices[0].u = 0;
            vertices[0].v = 0;
            vertices[1].x = leftBound + (float)col * charWidth + charWidth;
            vertices[1].y = topBound - (float)row * charHeight - charHeight;
            vertices[1].u = 1;
            vertices[1].v = 0;
            vertices[2].x = leftBound + (float)col * charWidth + charWidth;
            vertices[2].y = topBound - (float)row * charHeight;
            vertices[2].u = 1;
            vertices[2].v = 1;

            vertices[3].x = leftBound + (float)col * charWidth;
            vertices[3].y = topBound - (float)row * charHeight - charHeight;
            vertices[3].u = 0;
            vertices[3].v = 0;
            vertices[4].x = leftBound + (float)col * charWidth;
            vertices[4].y = topBound - (float)row * charHeight;
            vertices[4].u = 0;
            vertices[4].v = 1;
            vertices[5].x = leftBound + (float)col * charWidth + charWidth;
            vertices[5].y = topBound - (float)row * charHeight;
            vertices[5].u = 1;
            vertices[5].v = 1;

            for(int i = 0; i < 6; i++) {
                vertices[i].fgR = CONSOLATION_GET_RED(cell->fgColor);
                vertices[i].fgG = CONSOLATION_GET_GREEN(cell->fgColor);
                vertices[i].fgB = CONSOLATION_GET_BLUE(cell->fgColor);

                vertices[i].bgR = CONSOLATION_GET_RED(cell->bgColor);
                vertices[i].bgG = CONSOLATION_GET_GREEN(cell->bgColor);
                vertices[i].bgB = CONSOLATION_GET_BLUE(cell->bgColor);

                vertices[i].left = left;
                vertices[i].bottom = bottom;
                vertices[i].top = top;
                vertices[i].right = right;
                vertices[i].weight = 0.2f * (float)cell->weight / 255.0f;
            }
        }
    }

    if(!window->initialized) {
        initRendering(window);

        window->initialized = true;
    }
    glBindBuffer(GL_ARRAY_BUFFER, window->vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(struct consolation_Vertex) * (window->cols) * (window->rows) * 6,
                 window->vertices,
                 GL_STATIC_DRAW);
    glUseProgram(window->shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, window->font);
    glBindVertexArray(window->vao);
    glDrawArrays(GL_TRIANGLES, 0, 6 * window->rows * window->cols);

    glfwSwapBuffers(window->window);
}

bool consolation_shouldWindowClose(struct consolation_Window* window) {
    return glfwWindowShouldClose(window->window);
}

void consolation_freeWindow(struct consolation_Window* window) {
    reallocate(window->cells, 0);
}


struct consolation_Cell* consolation_getCell(struct consolation_Window* window, int col, int row) {
    if(col < 0 || col >= window->cols)
        return NULL;
    if(row < 0 || row >= window->rows)
        return NULL;
    return window->cells + col + row * window->cols;
}

void consolation_clear(struct consolation_Window* window) {
    for(int col = 0; col < window->cols; col++) {
        for(int row = 0; row < window->rows; row++) {
            struct consolation_Cell* cell = consolation_getCell(window, col, row);
            cell->character = ' ';
            cell->fgColor = 0xFFFFFF;
            cell->bgColor = 0;
            cell->weight = 0;
        }
    }
}

void consolation_setResolution(struct consolation_Window* window, int cols, int rows) {
    window->cols = cols;
    window->rows = rows;
    window->cells = reallocate(window->cells, cols * rows * sizeof(struct consolation_Cell));
    window->vertices = reallocate(window->vertices, 6 * cols * rows * sizeof(struct consolation_Vertex));
}

void consolation_writeString(struct consolation_Window* window, int col, int row, const char* text) {
    const char* curr = text;
    int currCol = col;
    while(*curr != '\0') {
        consolation_setChar(window, currCol++, row, *(curr++));
    }
}

#define SETTER(property, propertyName, type) CONSOLATION_DEFINE_CELL_SETTER(property, propertyName, type)
CONSOLATION_PROPERTY_SETTERS
#undef SETTER