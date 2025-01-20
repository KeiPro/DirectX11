#include "00. Global.fx"

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

Texture2D Texture0;

float4 PS(VertexOutput input) : SV_TARGET
{
	return Texture0.Sample(LinearSampler, input.uv);
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};