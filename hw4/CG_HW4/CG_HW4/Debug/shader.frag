varying vec4 vv4color;
varying vec4 vv4position;

uniform mat4 mvp;
uniform mat4 vmn;
uniform mat4 mn;
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
	float spotCutoff;		// (range: [0.0,90.0], 180.0)
	float spotCosCutoff;	// (range: [1.0,0.0],-1.0)
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

vec4 fragLighting(){
	vec4 resLight = vec4(0, 0, 0, 1);
	vec4 vPos = vmn * vv4position;
	vec3 norN = normalize(vv4color.xyz);
	mat4 norMat = transpose(inverse(mn));

	norN = normalize((norMat*vec4(norN, 0)).xyz);

	for (int i = 0; i<3; i++){
		vec3 lightVector = LightSource[i].position.xyz;
		if (lightType[i] > 0.5f){
			vec4 vv4specular_D = vec4(0, 0, 0, 1);
			vec3 lightV;
			float attenuation;
			if (LightSource[i].position.w < 0.5){
				lightV = normalize(lightVector.xyz);
				attenuation = LightSource[i].constantAttenuation;
			}
			else{
				lightV = normalize(lightVector - (mn*vv4position).xyz);
				float dist = length(lightVector - (mn*vv4position).xyz);
				attenuation = 1.0 / (0.0 + 0.02* dist + 0.001 * dist * dist);

				if (LightSource[i].spotCutoff != 180.0){
					vec3 rD = -lightV;
					vec3 coneDir = normalize((transpose(inverse(v)) * LightSource[i].spotDirection).xyz);

					float angle = degrees(acos(dot(coneDir, rD)));
					if (angle > LightSource[i].spotCutoff){
						attenuation = 0.0;
					}
					else{
						attenuation *= pow(max(dot(coneDir, rD), 0.0), LightSource[i].spotExponent);
					}
				}
			}
			float nxDir = max(0.0, dot(norN, lightV));
			vec4 vv4diffuse_D = nxDir*Material.diffuse * LightSource[i].diffuse;
			if (nxDir != 0.0){
				vec3 cameraVector = normalize(eyeP - vPos.xyz);
				vec3 refV = reflect(-lightV, norN);
				float nxSir = max(0.0, dot(refV, cameraVector));
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
		gl_FragColor = fragLighting();
}
