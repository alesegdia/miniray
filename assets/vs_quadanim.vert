#version 130

in  vec3 in_Position;
in  vec2 in_TexCoord;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

uniform vec2 frame;
uniform vec2 size;

out vec2 frag_TexCoord;


void main(void) {

    frag_TexCoord = in_TexCoord + frame * size;

	mat4 mv = view * model;
    gl_Position = proj * mv * vec4( in_Position, 1.0 );

}

