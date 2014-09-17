#version 150

uniform sampler2D tex;
//uniform vec3 camPos;
uniform float range;

in  vec2 frag_TexCoord;
out vec4 finalColor;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void) {
	float dist = (gl_FragCoord.z / gl_FragCoord.w) / range;
    vec4 mycolor = (dist) * vec4(0.f, 0.f, 0.f, texture(tex, frag_TexCoord).a) + (1-dist) * texture(tex, frag_TexCoord);
    float u = 1; //rand( gl_FragCoord.xy );
    finalColor = u * mycolor + (1-u) * vec4(1,1,1,1);

}

