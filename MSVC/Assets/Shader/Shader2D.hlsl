
struct VS_Input
{
	float2 position : POSITION;
	float2 uv       : TEXCOORD0;
	float4 color    : COLOR0;
};

struct VS_Output
{
	float4 position : SV_POSITION;
	float2 uv       : TEXCOORD0;
	float4 color    : COLOR0;
};

VS_Output VS_main(VS_Input input)
{
	VS_Output output;
	output.position = float4(input.position, 0.0, 1.0);
	output.uv       = input.uv;
	output.color    = input.color;

	return output;
}

float4 PS_main(VS_Output input): SV_Target
{
	return input.color;
}
