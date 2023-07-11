#include "globals.hlsli"

struct GSOutput
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
    uint iInstance : SV_InstanceID;
};

struct VSOut
{
    float4 Pos : SV_Position;
};

float4 main(GSOutput In) : SV_TARGET
{
    float4 outColor = (float4) 0.f;
    
    outColor = defaultTexture.Sample(anisotropicSampler, In.UV);
    
    outColor *= startColor;
    
	return outColor;
}