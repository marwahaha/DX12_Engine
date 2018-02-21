// GBuffer rendering pixel shader
// this takes data from a mesh and materials and push results into GBuffer
// GBuffers are : 
// - Normals	(float4)
// - Colors		(float4)
// - Specular	(float4)
// - Depth		(int64)

// include render light lib
#include "../lib/Material.hlsli"
#include "../lib/GlobalBuffer.hlsli"

struct VS_OUTPUT
{
	// data for pipeline
	float4 position :		SV_POSITION;
	// GBuffer needed data
	float4 view_position :	POSITION;
	float3 normal :			NORMAL;
	float depth :			DEPTH_VIEW_SPACE;
};

struct PS_OUTPUT
{
	float4 normal :			SV_Target0;
	float4 diffuse :		SV_Target1;
	float4 specular :		SV_Target2;
	float4 position :		SV_Target3;
};

PS_OUTPUT main(const VS_OUTPUT input)
{
	PS_OUTPUT output;

	/////////////////////////////////////////////
	// update the normal buffer
	output.normal = float4(input.normal.xyz, 1.f);
	
	/////////////////////////////////////////////
	// update the diffuse buffer
	output.diffuse = float4(0.f, 1.f, 0.f, 1.f);

	/////////////////////////////////////////////
	// update the specular buffer
	output.specular = float4(0.f, 0.f, 1.f, 1.f);

	/////////////////////////////////////////////
	// update the position buffer
	output.position = input.view_position;

	/////////////////////////////////////////////
	// update the depth buffer
	// To do ...

	return output;
}