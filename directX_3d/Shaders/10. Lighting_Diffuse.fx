#include "00. Global.fx"

float3 LightDir;
float4 LightDiffuse; // 빛의 색상.
float4 MaterialDiffuse;
Texture2D DiffuseMap;

VertexOutput VS(VertexTextureNormal input)
{
	VertexOutput output;
	output.position = mul(input.position, W);
	output.position = mul(output.position, VP);
	output.uv = input.uv;

	// normal값을 그대로 사용하는 것이 아니라, 월드 변환 행렬을 사용해야 이동된 물체의 노말 좌표를 구할 수 있을 것이다.
	// 여기서 마지막 z요소를 0으로 강제한 World변환 행렬을 곱해주어야 한다.
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

// Diffuse (분산광)
// 물체의 표면에서 분산되어 눈으로 바로 들어오는 빛
// 각도에 따라 밝기가 다르다 (Lambert 공식)

float4 PS(VertexOutput input) : SV_TARGET
{
	float4 color = DiffuseMap.Sample(LinearSampler, input.uv);

	// LightDir과 normal값이 거의 평행한 방향이었다면 value는 1에 가까워지고,
	// 수직인 방향이었다면 value는 0에 가까워진다.
	float value = dot(-LightDir, normalize(input.normal));
	color = color * value * (LightDiffuse * MaterialDiffuse);  

	return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};