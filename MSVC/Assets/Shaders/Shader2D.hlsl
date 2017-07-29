
struct VS_Input
{
	float2 position : POSITION;
	float4 color    : COLOR0;
	float2 uv       : TEXCOORD0;
};

struct VS_Output
{
	float4 position : SV_POSITION;
	float4 color    : COLOR0;
	float2 uv       : TEXCOORD0;
};

VS_Output VS_shape(VS_Input input)
{
	VS_Output output;
	output.position = float4(input.position, 0.0, 1.0);
	output.color    = input.color;
	output.uv       = input.uv;

	return output;
}

float4 PS_shape(VS_Output input): SV_Target
{
	return input.color;
}
