#version 130

in  vec3 in_Position;
in  vec2 in_TexCoord;
in  mat4 in_ModelMatrix;

uniform mat4 view;
uniform mat4 proj;

out vec2 frag_TexCoord;


void main(void) {

    frag_TexCoord = in_TexCoord;

	mat4 mv = view * in_ModelMatrix;
    gl_Position = proj * mv * vec4( in_Position, 1.0 );

}





