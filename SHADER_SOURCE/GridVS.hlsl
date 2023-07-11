#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    
    float2 WorldPos : POSITION;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.f;
    
    float2 worldPos = float2(0.f, 0.f);
    worldPos.x = In.Pos.x * gCameraScale.x * gResolution.x + gCameraPosition.x;
    worldPos.y = In.Pos.y * gCameraScale.y * gResolution.y + gCameraPosition.y;
    
    const float meshScale = 2.f;
    Out.Pos = float4(In.Pos.xy * meshScale, 0.999f, 1.f);
    Out.UV = In.UV;
    Out.WorldPos = worldPos;
    
	return Out;
}