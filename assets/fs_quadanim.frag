
#version 150

uniform sampler2D tex;
uniform float range;

in  vec2 frag_TexCoord;
out vec4 finalColor;

void main(void) {
	if( texture( tex, frag_TexCoord ).a < 1.f ) discard;
	float dist = (gl_FragCoord.z / gl_FragCoord.w) / range;
    finalColor = (dist) * vec4(0.f, 0.f, 0.f, texture(tex, frag_TexCoord).a) + (1-dist) * texture(tex, frag_TexCoord);
}

