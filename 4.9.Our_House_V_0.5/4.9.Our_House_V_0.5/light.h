#pragma once


void set_light_position(int cameraIndex) {
	


	for (int i = 1; i < NUMBER_OF_LIGHT_SUPPORTED; i++) {
		glm::vec3 dir = glm::mat3(ViewMatrix[cameraIndex]) * glm::vec3(light[i].spot_direction[0], light[i].spot_direction[1],
			light[i].spot_direction[2]);
		glm::vec4 position_EC = ViewMatrix[cameraIndex] * glm::vec4(light[i].position[0], light[i].position[1],
			light[i].position[2], light[i].position[3]);
		glUniform4fv(loc_light[i].position, 1, &position_EC[0]);
		//glUniform4fv(loc_light[i].position, 1, light[i].position);
		glUniform3fv(loc_light[i].spot_direction, 1, &dir[0]);
	}
}

void initialize_lights_and_material(void) { // follow OpenGL conventions for initialization
	int i;

	glUseProgram(h_ShaderProgram_PS);

	glUniform4f(loc_global_ambient_color, 0.2f, 0.2f, 0.2f, 1.0f);
	for (i = 0; i < NUMBER_OF_LIGHT_SUPPORTED; i++) {
		glUniform1i(loc_light[i].light_on, 0); // turn off all lights initially
		glUniform4f(loc_light[i].position, 0.0f, 0.0f, 1.0f, 0.0f);
		glUniform4f(loc_light[i].ambient_color, 0.0f, 0.0f, 0.0f, 1.0f);
		if (i == 0) {
			glUniform4f(loc_light[i].diffuse_color, 1.0f, 1.0f, 1.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			glUniform4f(loc_light[i].diffuse_color, 0.0f, 0.0f, 0.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 0.0f, 0.0f, 0.0f, 1.0f);
		}
		glUniform3f(loc_light[i].spot_direction, 0.0f, 0.0f, -1.0f);
		glUniform1f(loc_light[i].spot_exponent, 0.0f); // [0.0, 128.0]
		glUniform1f(loc_light[i].spot_cutoff_angle, 180.0f); // [0.0, 90.0] or 180.0 (180.0 for no spot light effect)
		glUniform4f(loc_light[i].light_attenuation_factors, 1.0f, 0.0f, 0.0f, 0.0f); // .w != 0.0f for no ligth attenuation
	}

	glUniform4f(loc_material.ambient_color, 0.2f, 0.2f, 0.2f, 1.0f);
	glUniform4f(loc_material.diffuse_color, 0.8f, 0.8f, 0.8f, 1.0f);
	glUniform4f(loc_material.specular_color, 0.0f, 0.0f, 0.0f, 1.0f);
	glUniform4f(loc_material.emissive_color, 0.0f, 0.0f, 0.0f, 1.0f);
	glUniform1f(loc_material.specular_exponent, 0.0f); // [0.0, 128.0]

	glUseProgram(h_ShaderProgram_GS);

	glUniform4f(loc_global_ambient_color, 0.2f, 0.2f, 0.2f, 1.0f);
	for (i = 0; i < NUMBER_OF_LIGHT_SUPPORTED; i++) {
		glUniform1i(loc_light[i].light_on, 0); // turn off all lights initially
		glUniform4f(loc_light[i].position, 0.0f, 0.0f, 1.0f, 0.0f);
		glUniform4f(loc_light[i].ambient_color, 0.0f, 0.0f, 0.0f, 1.0f);
		if (i == 0) {
			glUniform4f(loc_light[i].diffuse_color, 1.0f, 1.0f, 1.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			glUniform4f(loc_light[i].diffuse_color, 0.0f, 0.0f, 0.0f, 1.0f);
			glUniform4f(loc_light[i].specular_color, 0.0f, 0.0f, 0.0f, 1.0f);
		}
		glUniform3f(loc_light[i].spot_direction, 0.0f, 0.0f, -1.0f);
		glUniform1f(loc_light[i].spot_exponent, 0.0f); // [0.0, 128.0]
		glUniform1f(loc_light[i].spot_cutoff_angle, 180.0f); // [0.0, 90.0] or 180.0 (180.0 for no spot light effect)
		glUniform4f(loc_light[i].light_attenuation_factors, 1.0f, 0.0f, 0.0f, 0.0f); // .w != 0.0f for no ligth attenuation
	}

	glUniform4f(loc_material.ambient_color, 0.2f, 0.2f, 0.2f, 1.0f);
	glUniform4f(loc_material.diffuse_color, 0.8f, 0.8f, 0.8f, 1.0f);
	glUniform4f(loc_material.specular_color, 0.0f, 0.0f, 0.0f, 1.0f);
	glUniform4f(loc_material.emissive_color, 0.0f, 0.0f, 0.0f, 1.0f);
	glUniform1f(loc_material.specular_exponent, 0.0f); // [0.0, 128.0]

	glUseProgram(0);
}

void set_up_scene_lights(ShaderType shadertype) {
	// point_light_WC: use light 0
	light[0].light_on = 1;
	light[0].position[0] = 0.0f; light[0].position[1] = 10.0f; 	// point light position in EC
	light[0].position[2] = 0.0f; light[0].position[3] = 1.0f;

	light[0].ambient_color[0] = 0.3f; light[0].ambient_color[1] = 0.3f;
	light[0].ambient_color[2] = 0.3f; light[0].ambient_color[3] = 1.0f;

	light[0].diffuse_color[0] = 0.7f; light[0].diffuse_color[1] = 0.7f;
	light[0].diffuse_color[2] = 0.7f; light[0].diffuse_color[3] = 1.0f;

	light[0].specular_color[0] = 0.9f; light[0].specular_color[1] = 0.9f;
	light[0].specular_color[2] = 0.9f; light[0].specular_color[3] = 1.0f;

	// spot_light_WC: use light 1
	light[1].light_on = 1;
	light[1].position[0] = 80.0f; light[1].position[1] = 47.5f; // spot light position in WC
	light[1].position[2] = 49.0f; light[1].position[3] = 1.0f;
		  
	light[1].ambient_color[0] = 0.2f; light[1].ambient_color[1] = 0.2f;
	light[1].ambient_color[2] = 0.2f; light[1].ambient_color[3] = 1.0f;
		  
	light[1].diffuse_color[0] = 0.82f; light[1].diffuse_color[1] = 0.82f;
	light[1].diffuse_color[2] = 0.82f; light[1].diffuse_color[3] = 1.0f;
		  
	light[1].specular_color[0] = 0.82f; light[1].specular_color[1] = 0.82f;
	light[1].specular_color[2] = 0.82f; light[1].specular_color[3] = 1.0f;
		  
	light[1].spot_direction[0] = 0.0f; light[1].spot_direction[1] = 0.0f; // spot light direction in WC
	light[1].spot_direction[2] = -1.0f;
	light[1].spot_cutoff_angle = 45.0f;
	light[1].spot_exponent = 27.0f;

	// spot_light_WC: use light 2
	light[2].light_on = 1;
	light[2].position[0] = 120.0f; light[2].position[1] = 100.0f; // spot light position in WC
	light[2].position[2] = 49.0f; light[2].position[3] = 1.0f;
		  
	light[2].ambient_color[0] = 0.2f; light[2].ambient_color[1] = 0.2f;
	light[2].ambient_color[2] = 0.2f; light[2].ambient_color[3] = 1.0f;
		  
	light[2].diffuse_color[0] = 0.82f; light[2].diffuse_color[1] = 0.82f;
	light[2].diffuse_color[2] = 0.82f; light[2].diffuse_color[3] = 1.0f;
		  
	light[2].specular_color[0] = 0.82f; light[2].specular_color[1] = 0.82f;
	light[2].specular_color[2] = 0.82f; light[2].specular_color[3] = 1.0f;
		  
	light[2].spot_direction[0] = 0.0f; light[2].spot_direction[1] = 0.0f; // spot light direction in WC
	light[2].spot_direction[2] = -1.0f;
	light[2].spot_cutoff_angle = 45.0f;
	light[2].spot_exponent = 15.0f;

	// spot_light_WC: use light 3
	light[3].light_on = 1; 
	light[3].position[0] = 40.0f; light[3].position[1] = 130.0f; // spot light position in WC
	light[3].position[2] = 49.0f; light[3].position[3] = 1.0f;
		  
	light[3].ambient_color[0] = 0.2f; light[3].ambient_color[1] = 0.2f;
	light[3].ambient_color[2] = 0.2f; light[3].ambient_color[3] = 1.0f;
		  
	light[3].diffuse_color[0] = 0.82f; light[3].diffuse_color[1] = 0.82f;
	light[3].diffuse_color[2] = 0.82f; light[3].diffuse_color[3] = 1.0f;
		  
	light[3].specular_color[0] = 0.82f; light[3].specular_color[1] = 0.82f;
	light[3].specular_color[2] = 0.82f; light[3].specular_color[3] = 1.0f;
		  
	light[3].spot_direction[0] = 0.0f; light[3].spot_direction[1] = 0.0f; // spot light direction in WC
	light[3].spot_direction[2] = -1.0f;
	light[3].spot_cutoff_angle = 45.0f;
	light[3].spot_exponent = 27.0f;

	// spot_light_WC: use light 4
	light[4].light_on = 1; 
	light[4].position[0] = 190.0f; light[4].position[1] = 30.0f; // spot light position in WC
	light[4].position[2] = 49.0f;  light[4].position[3] = 1.0f;
		  
	light[4].ambient_color[0] = 0.2f; light[4].ambient_color[1] = 0.2f;
	light[4].ambient_color[2] = 0.2f; light[4].ambient_color[3] = 1.0f;
		  
	light[4].diffuse_color[0] = 0.82f; light[4].diffuse_color[1] = 0.82f;
	light[4].diffuse_color[2] = 0.82f; light[4].diffuse_color[3] = 1.0f;
		  
	light[4].specular_color[0] = 0.82f; light[4].specular_color[1] = 0.82f;
	light[4].specular_color[2] = 0.82f; light[4].specular_color[3] = 1.0f;
		  
	light[4].spot_direction[0] = 0.0f; light[4].spot_direction[1] = 0.0f; // spot light direction in WC
	light[4].spot_direction[2] = -1.0f;
	light[4].spot_cutoff_angle = 45.0f;
	light[4].spot_exponent = 27.0f;

	// spot_light_WC: use light 5
	light[5].light_on = 1; 
	light[5].position[0] = 210.0f; light[5].position[1] = 112.5f; // spot light position in WC
	light[5].position[2] = 49.0f;  light[5].position[3] = 1.0f;
		  
	light[5].ambient_color[0] = 0.2f; light[5].ambient_color[1] = 0.2f;
	light[5].ambient_color[2] = 0.2f; light[5].ambient_color[3] = 1.0f;
		  
	light[5].diffuse_color[0] = 0.82f; light[5].diffuse_color[1] = 0.82f;
	light[5].diffuse_color[2] = 0.82f; light[5].diffuse_color[3] = 1.0f;
		  
	light[5].specular_color[0] = 0.82f; light[5].specular_color[1] = 0.82f;
	light[5].specular_color[2] = 0.82f; light[5].specular_color[3] = 1.0f;
		  
	light[5].spot_direction[0] = 0.0f; light[5].spot_direction[1] = 0.0f; // spot light direction in WC
	light[5].spot_direction[2] = -1.0f;
	light[5].spot_cutoff_angle = 45.0f;
	light[5].spot_exponent = 27.0f;

	// spot_light_WC: use light 6
	light[6].light_on = 1; 
	light[6].position[0] = 166.0f; light[6].position[1] = 133.0f; // spot light position in WC
	light[6].position[2] = 49.0f;  light[6].position[3] = 1.0f;
		  
	light[6].ambient_color[0] = 0.2f; light[6].ambient_color[1] = 0.2f;
	light[6].ambient_color[2] = 0.2f; light[6].ambient_color[3] = 1.0f;
		  
	light[6].diffuse_color[0] = 0.82f; light[6].diffuse_color[1] = 0.82f;
	light[6].diffuse_color[2] = 0.82f; light[6].diffuse_color[3] = 1.0f;
		  
	light[6].specular_color[0] = 0.82f; light[6].specular_color[1] = 0.82f;
	light[6].specular_color[2] = 0.82f; light[6].specular_color[3] = 1.0f;
		  
	light[6].spot_direction[0] = 0.0f; light[6].spot_direction[1] = 0.0f; // spot light direction in WC
	light[6].spot_direction[2] = -1.0f;
	light[6].spot_cutoff_angle = 45.0f;
	light[6].spot_exponent = 27.0f;

	// spot_light_WC: use light 7
	light[7].light_on = 1; 
	light[7].position[0] = 38.0f; light[7].position[1] = 154.0f; // spot light position in WC
	light[7].position[2] = 49.0f;  light[7].position[3] = 1.0f;
		  
	light[7].ambient_color[0] = 0.2f; light[7].ambient_color[1] = 0.2f;
	light[7].ambient_color[2] = 0.2f; light[7].ambient_color[3] = 1.0f;
		  
	light[7].diffuse_color[0] = 0.82f; light[7].diffuse_color[1] = 0.82f;
	light[7].diffuse_color[2] = 0.82f; light[7].diffuse_color[3] = 1.0f;
		  
	light[7].specular_color[0] = 0.82f; light[7].specular_color[1] = 0.82f;
	light[7].specular_color[2] = 0.82f; light[7].specular_color[3] = 1.0f;
		  
	light[7].spot_direction[0] = 0.0f; light[7].spot_direction[1] = -1.0f; // spot light direction in WC
	light[7].spot_direction[2] = 0.0f;
	light[7].spot_cutoff_angle = 45.0f;
	light[7].spot_exponent = 27.0f;

	if(shadertype == SHADER_PS)
		glUseProgram(h_ShaderProgram_PS);
	else
		glUseProgram(h_ShaderProgram_GS);

	for (int i = 0; i < 1; i++) {
		glUniform1i(loc_light[i].light_on, light[i].light_on);
		glUniform4fv(loc_light[i].position, 1, light[i].position);
		glUniform4fv(loc_light[i].ambient_color, 1, light[i].ambient_color);
		glUniform4fv(loc_light[i].diffuse_color, 1, light[i].diffuse_color);
		glUniform4fv(loc_light[i].specular_color, 1, light[i].specular_color);
	}

	for (int i = 1; i < NUMBER_OF_LIGHT_SUPPORTED; i++) {
		glUniform1i(loc_light[i].light_on, light[i].light_on);
		// need to supply position in EC for shading
		glm::vec4 position_EC = ViewMatrix[0] * glm::vec4(light[i].position[0], light[i].position[1],
			light[i].position[2], light[i].position[3]);
		glUniform4fv(loc_light[i].position, 1, &position_EC[0]);
		glUniform4fv(loc_light[i].ambient_color, 1, light[i].ambient_color);
		glUniform4fv(loc_light[i].diffuse_color, 1, light[i].diffuse_color);
		glUniform4fv(loc_light[i].specular_color, 1, light[i].specular_color);
		// need to supply direction in EC for shading in this example shader
		// note that the viewing transform is a rigid body transform
		// thus transpose(inverse(mat3(ViewMatrix)) = mat3(ViewMatrix)
		glm::vec3 direction_EC = glm::mat3(ViewMatrix[0]) * glm::vec3(light[i].spot_direction[0], light[i].spot_direction[1],
			light[i].spot_direction[2]);
		//glm::vec3 direction_EC = glm::vec3(light[1].spot_direction[0], light[1].spot_direction[1], light[1].spot_direction[2]);
		glUniform3fv(loc_light[i].spot_direction, 1, &direction_EC[0]);
		glUniform1f(loc_light[i].spot_cutoff_angle, light[i].spot_cutoff_angle);
		glUniform1f(loc_light[i].spot_exponent, light[i].spot_exponent);
	}
	glUseProgram(0);
}