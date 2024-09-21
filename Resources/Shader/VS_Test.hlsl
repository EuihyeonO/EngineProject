struct VS_Input
{
    float4 Pos : POSITION;
    float4 NORMAL : NORMAL;
    float4 UV : TEXCOORD;
};

float4 main(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}