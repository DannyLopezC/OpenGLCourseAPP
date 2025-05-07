#version 330
out vec4 color;

in vec4 vCol;
in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
	color = texture(tex, TexCoord);

}