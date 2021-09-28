
#include "consolation.h"

int main() {
    consolation_init("../res/");
    struct consolation_Window window;
    consolation_initWindow(&window, 60, 30, "Hey");
    uint8_t weight = 0;
    int x = 15, y = 15;
    int dirX = 1, dirY = 1;
    int timer = 0;
    while(!consolation_shouldWindowClose(&window) ) {
        consolation_updateFrame(); // Call this at the start of the frame

        consolation_clear(&window);
        consolation_writeString(&window, 2, 2, "The quick brown fox jumps over the lazy dog!!!");
        consolation_writeString(&window, 2, 3, "Hello world!!!");
        consolation_writeString(&window, 2, 4, "+----------+");
        consolation_writeString(&window, 2, 5, "|          |");
        consolation_writeString(&window, 2, 6, "|          |");
        consolation_writeString(&window, 2, 7, "+----------+");

        consolation_setWeight(&window, 2, 4, weight);
        for(int col = 6; col <= 10; col++)
            consolation_setWeight(&window, col, 2, 200);
        weight += 5;

        consolation_setChar(&window, x, y, '@');
        consolation_setFG(&window, x, y, 0xFFA000);
        consolation_setChar(&window, x - dirX, y - dirY, '@');
        consolation_setFG(&window, x - dirX, y - dirY, 0x600000);
        if(timer == 0) {
            x += dirX;
            y += dirY;
            if (x == 0 || x == window.cols - 1)
                dirX *= -1;
            if (y == 0 || y == window.rows - 1)
                dirY *= -1;
        }
        timer++;
        timer %= 2;

        uint32_t color = 0x555555;
        if(glfwGetKey(window.window, GLFW_KEY_A))
            color = 0xFFA000;
        consolation_writeString(&window, 30, 20, "Press A");
        for(int i = 30; i <= 36; i++)
            consolation_setFG(&window, i, 20, color);

        for(int i = 3; i < 7; i++)
            for(int j = 15; j < 20; j++)
                consolation_setChar(&window, i, j, '#');

        consolation_renderWindow(&window);

    }
    consolation_freeWindow(&window);
    consolation_free();
    return 0;
}