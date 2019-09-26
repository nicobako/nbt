#version 130

attribute vec2 vPos;
attribute vec3 vCol;

out vec3 vs_color;
void main(void)
{
	gl_Position = vec4(vPos, 1.0, 1.0);
   vs_color = vCol;
}
