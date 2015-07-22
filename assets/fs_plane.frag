
#version 130

uniform sampler2D tex;
uniform float range;

in  vec2 frag_TexCoord;
out vec4 finalColor;

void main(void) {
	float depth = (gl_FragCoord.z / gl_FragCoord.w) / range;
	vec4 texcolor = texture(tex, frag_TexCoord);
	finalColor = depth * vec4(0.f,0.f,0.f,1.f) + (1-depth) * texture(tex, frag_TexCoord);
}

