#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform vec3 white = vec3(1,1,1);
uniform bool useComplimentary = false;

out vec4 Fragment;

void main()
{
	vec3 colorToUse = Color;
	
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0) {
		colorToUse = SolidColor;
	}
	
	if(useComplimentary == true) {
		colorToUse = white - colorToUse;
	}
	
	Fragment = vec4(colorToUse,1);

	return;
}