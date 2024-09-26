struct PS_Input
{
    float4 Pos : SV_POSITION;
    float4 NORMAL : NORMAL;
    float2 UV : TEXCOORD;
};

Texture2D DiffuseTex : register(t0);
SamplerState LinearSampler : register(s0);

float4 main(PS_Input _Input) : SV_TARGET
{
    float4 Color = DiffuseTex.Sample(LinearSampler, _Input.UV);
    return Color;
}