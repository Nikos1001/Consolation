#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aFg;
layout (location = 3) in vec3 aBg;
layout (location = 4) in vec2 aBottomLeft;
layout (location = 5) in vec2 aTopRight;
layout (location = 6) in float aWeight;

out vec2 pUv;
out vec3 pFg;
out vec3 pBg;
out vec2 pBottomLeft;
out vec2 pTopRight;
out float pWeight;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    pUv = aUv;
    pFg = aFg;
    pBg = aBg;

    pBottomLeft = aBottomLeft;
    pTopRight = aTopRight;

    pWeight = aWeight;
}