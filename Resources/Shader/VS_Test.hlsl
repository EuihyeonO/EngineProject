struct VS_Input
{
    float3 Pos : POSITION;
    float3 NORMAL : NORMAL;
    float2 UV : TEXCOORD;
};

struct VS_OutPut
{
    float4 Pos : SV_POSITION;
    float4 NORMAL : NORMAL;
    float2 UV : TEXCOORD;
};

cbuffer Data : register (b0)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

	//SRP 다 곱한 것
    matrix LocalMatrix;
	
    matrix LocalScaleMatrix;
    matrix LocalRotationMatrix;
    matrix LocalPositionMatrix;
	
	//SRP 다 곱한 것
    matrix WorldMatrix;

    matrix WorldScaleMatrix;
    matrix WorldRotationMatrix;
    matrix WorldPositionMatrix;

	//카메라의 뷰행렬
    matrix ViewMatrix;
	
	//프로젝션 행렬
    matrix ProjMatrix;
};

VS_OutPut main(VS_Input _Input)
{
    VS_OutPut OutPut;
    OutPut.Pos = float4(_Input.Pos, 1.0f);
    OutPut.NORMAL = float4(_Input.NORMAL, 1.0f);
    
    OutPut.Pos = mul(OutPut.Pos, WorldMatrix);
    OutPut.Pos = mul(OutPut.Pos, ViewMatrix);
    OutPut.Pos = mul(OutPut.Pos, ProjMatrix);
    
    OutPut.NORMAL = mul(OutPut.NORMAL, WorldMatrix);
    OutPut.NORMAL = mul(OutPut.NORMAL, ViewMatrix);
    OutPut.NORMAL = mul(OutPut.NORMAL, ProjMatrix);
    
    OutPut.UV = _Input.UV.xy;
    
    return OutPut;
}