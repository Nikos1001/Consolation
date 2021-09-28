
#version 330 core
out vec3 FragColor;

uniform sampler2D uFont;

in vec2 pUv;
in vec3 pFg;
in vec3 pBg;
in vec2 pBottomLeft;
in vec2 pTopRight;
in float pWeight;

void main() {
    float xCoord = 1 - pUv.x;
    float yCoord = 1 - pUv.y;

    float uvX = pBottomLeft.x * xCoord + pTopRight.x * (1 - xCoord);
    float uvY = pBottomLeft.y * yCoord + pTopRight.y * (1 - yCoord);

    float sample = texture(uFont, vec2(uvX, uvY)).r;
    float scale = 1.0 / fwidth(sample);
    float signedDistance = (sample - 0.5) * scale;
    float color = clamp(signedDistance + 0.9 + 2 * scale * clamp(pWeight, 0.01, 1.0), 0.0, 1.0);
    FragColor = mix(pBg, pFg, color);
//    FragColor = vec3(pWeight, pWeight, pWeight);
}