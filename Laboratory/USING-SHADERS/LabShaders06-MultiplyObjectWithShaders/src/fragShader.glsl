#version 410
out vec4 color;
in vec3 oColor;

void main(void){
	//if(gl_FragCoord.x > 400)
		color = vec4(oColor, 1.0);
	//else
	//	color = vec4(1.0, 0.0, 0.0, 1.0);	
}
