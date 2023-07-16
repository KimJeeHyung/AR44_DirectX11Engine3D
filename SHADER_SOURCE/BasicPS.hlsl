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
    float3 WorldPos : POSITION;
    float3 Normal : NORMAL;
    float Intensity : FOG;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 OutColor = float4(0.68f, 1.f, 0.18f, 1.f);
    
    float4 Out = float4(1.f, 0.f, 1.f, 1.f);
    
    float3 LightDir = normalize(globalLightDir);
    // saturate() �Լ��� 0 ������ ���� 0����, 1 �̻��� ���� 1�� �ٲ��ݴϴ�.
    float intensity = saturate(dot(-LightDir, In.Normal));
    
    Out.xyz = (intensity * OutColor.xyz * globalLightColor) + (OutColor.xyz * globalLightAmb);
    
    return Out;
}