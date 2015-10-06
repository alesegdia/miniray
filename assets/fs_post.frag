
#version 130
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texFramebuffer;
uniform float time;
uniform float scanarray[256];

const float blurSizeH = 1.0 / 300.0;
const float blurSizeV = 1.0 / 200.0;

vec3 blur()
{
    vec4 sum = vec4(0.0);
    for (int x = -4; x <= 4; x++)
        for (int y = -4; y <= 4; y++)
            sum += texture(
                texFramebuffer,
                vec2(Texcoord.x + x * blurSizeH, Texcoord.y + y * blurSizeV)
            ) / 81.0;
    return sum.xyz;
}

vec3 sobel()
{
	vec4 s1 = texture(texFramebuffer, Texcoord - 1.0 / 300.0 - 1.0 / 200.0);
	vec4 s2 = texture(texFramebuffer, Texcoord + 1.0 / 300.0 - 1.0 / 200.0);
	vec4 s3 = texture(texFramebuffer, Texcoord - 1.0 / 300.0 + 1.0 / 200.0);
	vec4 s4 = texture(texFramebuffer, Texcoord + 1.0 / 300.0 + 1.0 / 200.0);
	vec4 sx = 4.0 * ((s4 + s3) - (s2 + s1));
	vec4 sy = 4.0 * ((s2 + s4) - (s1 + s3));
	vec4 sobel = sqrt(sx * sx + sy * sy);
	return sobel.xyz;
}

vec3 inverse()
{
    return vec3(1.0, 1.0, 1.0) - texture(texFramebuffer, Texcoord).xyz;
}

void main() {
	vec3 original = texture(texFramebuffer, Texcoord).xyz;
	vec3 bl = blur();
	vec3 inv = inverse();
	vec3 sob = sobel();

	float dx = 3.05*(1./512.);
	float dy = 3.05*(1./512.);
	vec2 coord = vec2(dx*floor(Texcoord.x/dx),
						dy*floor(Texcoord.y/dy));
	original = texture2D(texFramebuffer, coord).xyz;

	//outColor = vec4((inv+bl)/3, 1.0);

	vec3 final = (original * 2 + bl)/3.0;
	float s = (sob.r+sob.g+sob.b) / 50;
	//outColor = vec4(mix( final/0.3, original, 1-s ),1.0) ;
	outColor = vec4(mix( final/0.3, original, 0.5 ),1.0) ;

	//outColor = vec4( final/0.3, 1 );
	//outColor = vec4( mix( vec3(1,1,1)-final/0.3, original, 1.5 * sin(time/500))-0.5, 1 );
	//outColor = vec4( mix( vec3(1,1,1)-final/0.3, original, sin(time/500)), 1 );
	//outColor = vec4( mix( vec3(1,1,1)-final/0.3, original, 0.2 * sin(time/500) + 0.8), 1 );
	//outColor = vec4( mix( vec3(1,1,1)-final/0.3, original, sin(time/100)), 1 );
	float tmp = (original.r+original.g+original.b)*1.5;
	//outColor = vec4( mix( vec3(tmp,0,0)-final/0.3, original, sin(time/100)), 1 );
	//outColor = vec4( mix( vec3(tmp,0,0)-final/0.3, original, 0.9 * sin(time/100)), 1 );
	//outColor = vec4( mix( vec3(tmp,0,0)-final/0.3, original, 0.0), 1 );


	// scanlines
	//float division = (Texcoord.y * 256);
	//if( mod( Texcoord.y, 0.005 ) < 0.0025 ) outColor = mix( outColor, vec4(0,0,0,1), scanarray[int(division)] );
	if( mod( Texcoord.y, 0.005 ) < 0.0025 ) outColor = mix( outColor, vec4(0,0,0,1), 0.2 );


}
