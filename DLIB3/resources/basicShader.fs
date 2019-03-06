#version 120

varying  vec2    texCoord0;
uniform sampler2D   diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0);

	if (gl_FragColor.a <= 0.2) {
            discard;
        }
}