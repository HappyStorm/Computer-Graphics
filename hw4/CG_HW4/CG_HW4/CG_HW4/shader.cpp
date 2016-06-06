#include "shader.h"
#include "utilize.h"

void showShaderCompileStatus(GLuint shader, GLint *shaderCompiled)
{
	glGetShaderiv(shader, GL_COMPILE_STATUS, shaderCompiled);
	if (GL_FALSE == (*shaderCompiled))
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character.
		GLchar *errorLog = (GLchar*)malloc(sizeof(GLchar)* maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
		fprintf(stderr, "%s", errorLog);

		glDeleteShader(shader);
		free(errorLog);
	}
}

void setShaders()
{
	GLuint v, f, p;
	char *vs = NULL;
	char *fs = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("shader.vert");
	fs = textFileRead("shader.frag");

	glShaderSource(v, 1, (const GLchar**)&vs, NULL);
	glShaderSource(f, 1, (const GLchar**)&fs, NULL);

	free(vs);
	free(fs);

	// compile vertex shader
	glCompileShader(v);
	GLint vShaderCompiled;
	showShaderCompileStatus(v, &vShaderCompiled);
	if(!vShaderCompiled) system("pause"), exit(123);

	// compile fragment shader
	glCompileShader(f);
	GLint fShaderCompiled;
	showShaderCompileStatus(f, &fShaderCompiled);
	if(!fShaderCompiled) system("pause"), exit(456);

	p = glCreateProgram();

	// bind shader
	glAttachShader(p, f);
	glAttachShader(p, v);

	// link program
	glLinkProgram(p);
	GLint linked = 0;
	glGetProgramiv(p, GL_LINK_STATUS, &linked);
	if (linked) {
		glUseProgram(p);
	}
	else {
		GLint length;
		GLchar* log;
		glGetProgramiv(p, GL_INFO_LOG_LENGTH, &length);
		log = (GLchar*)malloc(length);
		glGetProgramInfoLog(p, length, &length, log);
		fprintf(stderr, "link log = '%s'\n", log);
		free(log);
	}


	iLocPosition = glGetAttribLocation (p, "av4position");
	iLocNormal	 = glGetAttribLocation (p, "av3normal");
	iLocTexCoord = glGetAttribLocation (p, "av2texCoord");
	iLocMVP		 = glGetUniformLocation(p, "mvp");
	iLocVMN      = glGetUniformLocation(p, "vmn");
	iLocMN       = glGetUniformLocation(p, "mn");
	iLocV		 = glGetUniformLocation(p, "v");

	iLocMDiffuse   = glGetUniformLocation(p, "Material.diffuse");
	iLocMAmbient   = glGetUniformLocation(p, "Material.ambient");
	iLocMSpecular  = glGetUniformLocation(p, "Material.specular");
	iLocMShininess = glGetUniformLocation(p, "Material.shininess");

	iLocLDAmbient      = glGetUniformLocation(p, "LightSource[0].ambient");
	iLocLDDiffuse      = glGetUniformLocation(p, "LightSource[0].diffuse");
	iLocLDSpecular	   = glGetUniformLocation(p, "LightSource[0].specular");
	iLocLDPosition	   = glGetUniformLocation(p, "LightSource[0].position");
	iLocLDSpotcutoff   = glGetUniformLocation(p, "LightSource[0].spotCutoff");
	iLocLDCAttenuation = glGetUniformLocation(p, "LightSource[0].constantAttenuation");

	iLocLPAmbient	   = glGetUniformLocation(p, "LightSource[1].ambient");
	iLocLPDiffuse	   = glGetUniformLocation(p, "LightSource[1].diffuse");
	iLocLPSpecular	   = glGetUniformLocation(p, "LightSource[1].specular");
	iLocLPPosition	   = glGetUniformLocation(p, "LightSource[1].position");
	iLocLPSpotcutoff   = glGetUniformLocation(p, "LightSource[1].spotCutoff");
	iLocLPCAttenuation = glGetUniformLocation(p, "LightSource[1].constantAttenuation");
	iLocLPLAttenuation = glGetUniformLocation(p, "LightSource[1].linearAttenuation");
	iLocLPQAttenuation = glGetUniformLocation(p, "LightSource[1].quadraticAttenuation");

	iLocLSAmbient      = glGetUniformLocation(p, "LightSource[2].ambient");
	iLocLSDiffuse      = glGetUniformLocation(p, "LightSource[2].diffuse");
	iLocLSSpecular     = glGetUniformLocation(p, "LightSource[2].specular");
	iLocLSPosition     = glGetUniformLocation(p, "LightSource[2].position");
	iLocLSSpotcutoff   = glGetUniformLocation(p, "LightSource[2].spotCutoff");
	iLocLSCAttenuation = glGetUniformLocation(p, "LightSource[2].constantAttenuation");
	iLocSSpotDirection = glGetUniformLocation(p, "LightSource[2].spotDirection");
	iLocLSLAttenuation = glGetUniformLocation(p, "LightSource[2].linearAttenuation");
	iLocLSQAttenuation = glGetUniformLocation(p, "LightSource[2].quadraticAttenuation");
	iLocSSpotExponent  = glGetUniformLocation(p, "LightSource[2].spotExponent");

	iLocLType = glGetUniformLocation(p, "lightType");
	eyePos	  = glGetUniformLocation(p, "eyeP");
	iLocTexMapping = glGetUniformLocation(p, "texMapping");

	glUseProgram(p);

	glUniform4fv(iLocLDAmbient,  1,  mm.lightSource[0].ambient);
	glUniform4fv(iLocLDDiffuse,  1,  mm.lightSource[0].diffuse);
	glUniform4fv(iLocLDSpecular, 1,  mm.lightSource[0].specular);
	glUniform4fv(iLocLDPosition, 1,  mm.lightSource[0].position);
	glUniform1f (iLocLDSpotcutoff,   mm.lightSource[0].spotCutoff);
	glUniform1f (iLocLDCAttenuation, mm.lightSource[0].constantAttenuation);

	glUniform4fv(iLocLPAmbient,  1,  mm.lightSource[1].ambient);
	glUniform4fv(iLocLPDiffuse,  1,  mm.lightSource[1].diffuse);
	glUniform4fv(iLocLPSpecular, 1,  mm.lightSource[1].specular);
	glUniform4fv(iLocLPPosition, 1,  mm.lightSource[1].position);
	glUniform1f (iLocLPSpotcutoff,   mm.lightSource[1].spotCutoff);
	glUniform1f (iLocLPCAttenuation, mm.lightSource[1].constantAttenuation);
	glUniform1f (iLocLPLAttenuation, mm.lightSource[1].linearAttenuation);
	glUniform1f (iLocLPQAttenuation, mm.lightSource[1].quadraticAttenuation);

	glUniform4fv(iLocLSAmbient,  1,  mm.lightSource[2].ambient);
	glUniform4fv(iLocLSDiffuse,  1,  mm.lightSource[2].diffuse);
	glUniform4fv(iLocLSSpecular, 1,  mm.lightSource[2].specular);
	glUniform4fv(iLocLSPosition, 1,  mm.lightSource[2].position);
	glUniform1f (iLocLSSpotcutoff,   mm.lightSource[2].spotCutoff);
	glUniform1f (iLocLSCAttenuation, mm.lightSource[2].constantAttenuation);
	glUniform1f (iLocLSLAttenuation, mm.lightSource[2].linearAttenuation);
	glUniform1f (iLocLSQAttenuation, mm.lightSource[2].quadraticAttenuation);

	glUniform4fv(iLocSSpotDirection, 1, mm.lightSource[2].spotDirection);
	glUniform1f (iLocSSpotExponent,     mm.lightSource[2].spotExponent);
}