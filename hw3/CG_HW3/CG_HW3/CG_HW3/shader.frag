varying vec4 vv4color;
varying vec4 vv4position;

uniform mat4 mvp; // P * V * M
uniform mat4 vmn; // V * M * N
uniform mat4 mn;  // MN = (T * S * R) * N
uniform mat4 v;
uniform vec3 eyeP;
uniform vec4 lightType;

struct LightSourceParameters {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
	vec4 halfVector;
	vec4 spotDirection;
	float spotExponent;
	float spotCutoff;		// (range: [0.0, 90.0], 180.0)
	float spotCosCutoff;	// (range: [1.0, 0.0 ],  -1.0)
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

struct MaterialParameters {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform MaterialParameters Material;
uniform LightSourceParameters LightSource[3];

vec4 pixelLighting(){
	vec4 resLight = vec4(0, 0, 0, 1); // since w = 1, it's a position
	vec4 vPos = vmn * vv4position; // change vertex's position to eye space (camera space)
	
	//Normal transformation
	vec3 norN = normalize(vv4color.xyz); // vertex normal (for 1 vertex)
	mat4 norMat = transpose(inverse(mn)); // normals' matrix for changing to world space
	norN = normalize((norMat*vec4(norN, 0)).xyz); // change vertex's normal to world space

	// traverse light source
	for (int i = 0; i<3; i++){
	// lightVector = light position
		vec3 lightVector = LightSource[i].position.xyz;

		// if the type of light source is on:
		// lightType[0] = directional light
		// lightType[1] = point light
		// lightType[2] = spot light

		// if light on
		if (lightType[i] > 0.5f){
			vec4 vv4specular_D = vec4(0, 0, 0, 1);  // since w = 1, it's a position
			vec3 norLightVector;
			float attenuation;

			// Directional light
			if (LightSource[i].position.w < 0.5){
				// since directional light's position is "direction",
				// the "light vector" euqals to "light position - origin" = light position
				// view vector: origin to light (vertex to light)
				norLightVector = normalize(lightVector.xyz);
				attenuation = LightSource[i].constantAttenuation;
			}

			// point light or spot light
			else{
				// mn * av4position: change vertex to world space
				// view vector: light position - vertex position (vertex to light)
				norLightVector = normalize(lightVector - (mn*vv4position).xyz);
				
				// calculate the distance between light and vertex
				float dist = length(lightVector - (mn*vv4position).xyz);
				
				// reference to ch4 p.19, Fatt = bla bla bla
				attenuation = 1.0 / (LightSource[i].constantAttenuation + 
									 LightSource[i].linearAttenuation * dist +
									 LightSource[i].quadraticAttenuation * dist * dist);

				// use this "if" to identify whether this light is spot light
				if (LightSource[i].spotCutoff != 180.0){ // angle
					vec3 rD = -norLightVector; // rD = vector: light position to vertex
					vec3 coneDir = normalize((transpose(inverse(v)) * LightSource[i].spotDirection).xyz);

					float angle = degrees(acos(dot(coneDir, rD)));
					if (angle > LightSource[i].spotCutoff)
						attenuation = 0.0;
					else
						attenuation *= pow(max(dot(coneDir, rD), 0.0), LightSource[i].spotExponent);
				}
			}

			// diffuse (reference to the ch4 p.46)
			float nxDir = max(0.0, dot(norN, norLightVector));  // cos (angle between light vector and vertex's normal)
			vec4 vv4diffuse_D = nxDir*Material.diffuse * LightSource[i].diffuse;
			
			// specular (reference to the ch4 p.21)
			if (nxDir != 0.0){
				// get view vector
				vec3 eyeVector = normalize(eyeP - vPos.xyz);

				// get reflection vector
				vec3 refVector = reflect(-norLightVector, norN);

				float nxSir = max(0.0, dot(refVector, eyeVector));
				float specularPow = pow(nxSir, 1.0);
				vv4specular_D = Material.specular * LightSource[i].specular * specularPow;
			}
			resLight += vec4(attenuation * (vv4diffuse_D.xyz + vv4specular_D.xyz), 0);
		}
	}
	vec4 vv4ambient_D = Material.ambient * LightSource[0].ambient;
	return resLight + vv4ambient_D;
}

void main() {
	if (lightType[3] < 0.5)
		gl_FragColor = vv4color;
	else
		gl_FragColor = pixelLighting();
}
