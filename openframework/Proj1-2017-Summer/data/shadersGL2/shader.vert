#version 120

varying vec4 globalColor;

void main()
{
	gl_Position = ftransform();
    globalColor = gl_Color;
}