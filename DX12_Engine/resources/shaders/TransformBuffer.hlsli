// default constant buffer in include file

// b0 buffer
cbuffer TransformBuffer : register(b0)
{
	// basics matrix for compute space position
	matrix	model;
	matrix	view;
	matrix	projection;
};
