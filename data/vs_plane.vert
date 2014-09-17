#version 150

in  vec2 in_Position;
in  vec2 in_TexCoord;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out vec2 frag_TexCoord;

void main(void) {

    frag_TexCoord = in_TexCoord;

	mat4 mv = view * model;
    gl_Position = proj * mv * vec4( in_Position * 0.5f, 1.0, 1.0 );

}

