#version 150

in vec3 vPos;
in vec3 vCol;
out vec4 fragmentColor;

uniform mat4 finalview;

void main() {
    
    vec4 finalVec= finalview*vec4(vPos, 1.0);
    gl_Position =  finalVec;   //gl_Position = vPos;
    fragmentColor = vec4(vCol, 1.0);
}
