#include "globals.hlsli"

struct VSIn
{
    float4 Position : POSITION;
    float2 UV : TEXCOORD;
    float3 Normal : NORMAL;
};

struct VSOut
{
    float4 Position : SV_Position;
    float2 UV : TEXCOORD;
    
    float3 ViewPos : POSITION;
    float3 ViewNormal : NORMAL;
    float Intensity : FOG;
};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.f;
    
    float4 worldPosition = mul(In.Position, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 projPosition = mul(viewPosition, projection);
    
    Out.Position = projPosition;
    Out.UV = In.UV;
    
    float3 vViewNormal = normalize(mul(float4(In.Normal.xyz, 0.f), world).xyz);
    vViewNormal = normalize(mul(float4(vViewNormal, 0.f), view).xyz);
    
    Out.ViewPos = viewPosition.xyz;
    Out.ViewNormal = vViewNormal.xyz;
    
    return Out;
}