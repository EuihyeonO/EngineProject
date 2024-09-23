Texture2D DiffuseTex : register(t0);
SamplerState EngineSampler : register(s0);

float4 main() : SV_TARGET
{
    float4 Color = DiffuseTex.Sample(EngineSampler, float2(0, 0));
    return Color;
}