#include "00. Global.fx"

float3 LightDir;
float4 LightSpecular;
float4 MaterialSpecular;
Texture2D DiffuseMap;

MeshOutput VS(VertexTextureNormal input)
{
	MeshOutput output;
	output.position = mul(input.position, W);
	output.position = mul(output.position, VP);
	output.worldPosition = input.position;
	output.uv = input.uv;

	// normal값을 그대로 사용하는 것이 아니라, 월드 변환 행렬을 사용해야 이동된 물체의 노말 좌표를 구할 수 있을 것이다.
	// 여기서 마지막 z요소를 0으로 강제한 World변환 행렬을 곱해주어야 한다.
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

// Specular (반사광)
// 한 방향으로 완전히 반사되는 빛 (Phong)

float4 PS(MeshOutput input) : SV_TARGET
{
	//float3 R = reflect(LightDir, input.normal);
	float3 R = LightDir - (2 * input.normal * dot(input.normal, LightDir));
	R = normalize(R);

	float3 cameraPosition = -V._41_42_43;
	float3 E = normalize(cameraPosition - input.worldPosition);

	float value = saturate(dot(R, E)); // clamp (0 ~ 1)
	float specular = pow(value, 10);

	float4 color = LightSpecular * MaterialSpecular * specular;

	return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};