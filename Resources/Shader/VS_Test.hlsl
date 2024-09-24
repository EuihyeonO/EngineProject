struct VS_Input
{
    float4 Pos : POSITION;
    float4 NORMAL : NORMAL;
    float4 UV : TEXCOORD;
};

cbuffer Data : register (b0)
{
    float4x4 WorldMatrix;
    float4x4 ViewMatrix;
    float4x4 ProjMatrix;
};

float4 main(float4 pos : POSITION) : SV_POSITION
{
    pos += Test1;
	return pos;
}