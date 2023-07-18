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

float4 main(VSOut In) : SV_TARGET
{
    float4 OutColor = float4(0.5f, 0.5f, 0.5f, 1.f);
    //float4 OutColor = float4(0.68f, 1.f, 0.18f, 1.f);
    
    LightColor lightColor = (LightColor) 0.f;
    
    for (int i = 0; i < numberOfLight; i++)
    {
        CalculateLight3D(In.ViewPos, In.ViewNormal, i, lightColor);
    }
    
    OutColor.rgb = (OutColor.rgb * lightColor.diffuse.rgb
                    + lightColor.specular.rgb
                    + (OutColor.xyz * lightColor.ambient.rgb));
    
    return OutColor;
}