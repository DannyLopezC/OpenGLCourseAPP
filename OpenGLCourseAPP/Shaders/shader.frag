#version 330
out vec4 color;

in vec4 vCol;
in vec2 TexCoord;

struct DirectionalLight {
	vec3 color;
	float ambientIntensity;
};

uniform sampler2D tex;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;

	color = texture(tex, TexCoord) * ambientColor;
}