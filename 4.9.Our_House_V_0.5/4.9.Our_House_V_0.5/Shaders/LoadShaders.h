#ifndef __LOAD_SHADERS_H__
#define __LOAD_SHADERS_H__

#include <GL/gl.h>
#define NUMBER_OF_LIGHT_SUPPORTED 8

typedef struct {
	GLenum       type;
	const char*  filename;
	GLuint       shader;
} ShaderInfo;

typedef struct _loc_LIGHT_Parameters {
	GLint light_on;
	GLint position;
	GLint ambient_color, diffuse_color, specular_color;
	GLint spot_direction;
	GLint spot_exponent;
	GLint spot_cutoff_angle;
	GLint light_attenuation_factors;
} loc_light_Parameters;

typedef struct _loc_Material_Parameters {
	GLint ambient_color, diffuse_color, specular_color, emissive_color;
	GLint specular_exponent;
} loc_Material_Parameters;


typedef struct _Light_Parameters {
	int light_on;
	float position[4];
	float ambient_color[4], diffuse_color[4], specular_color[4];
	float spot_direction[3];
	float spot_exponent;
	float spot_cutoff_angle;
	float light_attenuation_factors[4]; // produce this effect only if .w != 0.0f
} Light_Parameters;


GLuint LoadShaders(ShaderInfo*);

#endif // __LOAD_SHADERS_H__
