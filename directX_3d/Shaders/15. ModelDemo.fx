#include "00. Global.fx"
#include "00. Light.fx"

MeshOutput VS(VertexTextureNormalTangent input)
{
	MeshOutput output;
	output.position = mul(input.position, W);
	output.position = mul(output.position, VP);
	output.worldPosition = output.position.xyz;
	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);
	output.tangent = mul(input.tangent, (float3x3)W);

	return output;
}

float4 PS(MeshOutput input) : SV_TARGET
{
	//ComputeNomalMapping(input.normal, input.tangent, input.uv);

	//float4 color = ComputeLight(input.normal, input.uv, input.worldPosition);

	float4 color = DiffuseMap.Sample(LinearSampler, input.uv);

	return color;
}

float4 RS_RED(MeshOutput input) : SV_TARGET
{
	return float4(1, 0, 0, 1);
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
	PASS_RS_VP(P1, FillModeWireFrame, VS, RS_RED)
};