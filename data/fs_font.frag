
#version 120

varying vec2 texcoord;
uniform sampler2D tex;
uniform vec4 color;

void main(void) {

	//vec4 coordcolor = vec4(texcoord.x, texcoord.y, 0, 1);
	//gl_FragColor = vec4(0,1,0,1);
	//gl_FragColor = texture2D( tex, texcoord );
	//vec4 color = vec4(0,1,0,1);
  	//gl_FragColor = vec4( color.rgb, texture2D(tex, texcoord).a);
  	//gl_FragColor = coordcolor;
  	gl_FragColor = texture2D(tex, texcoord).rrrr * color;
	//if( texture2D( tex, texcoord ).r < 0.1 ) gl_FragColor = vec4(0,0,1,1);
	//gl_FragColor = vec4(1,1,1,1);
	//gl_FragColor = coordcolor;
}

