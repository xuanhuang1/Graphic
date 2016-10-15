#version 150

in vec3 vPos;
in vec3 vCol;
out vec4 fragmentColor;

uniform mat4 modelview;
uniform mat4 cameraview;

void main() {
    mat4 finalmat = cameraview*modelview;
    gl_Position = finalmat*vec4(vPos, 1.0);
    //gl_Position = vPos;
    fragmentColor = vec4(vCol, 1.0);
}
