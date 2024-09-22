struct VS_Input
{
    float4 Pos : POSITION;
    float4 NORMAL : NORMAL;
    float4 UV : TEXCOORD;
};

cbuffer Data : register (b0)
{
    float4 Test1;
    float4 Test2;
    float4 Test3;
    float4 Test4;
};

float4 main(float4 pos : POSITION) : SV_POSITION
{
    pos += Test1;
	return pos;
}