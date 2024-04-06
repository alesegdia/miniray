
#version 130
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texFramebuffer;

void main() {
	vec3 original = texture(texFramebuffer, Texcoord).xyz;
	outColor = vec4(original, 1);


}
