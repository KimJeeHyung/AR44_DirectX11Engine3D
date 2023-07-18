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
    float4 OutColor = float4(0.68f, 1.f, 0.18f, 1.f);
    
    LightAttribute lightAttribute = lightAttributes[0];
    
    // 광원의 방향을 월드 좌표계에서 뷰 좌표계로 변환
    float3 ViewLightDir = normalize(mul(float4(lightAttribute.direction.xyz, 0.f), view));
    
    float intensity = saturate(dot(-ViewLightDir, In.ViewNormal));
    float fSpecPow = 0.f;
    
    // 뷰 스페이스 상에서 표면의 빛의 세기를 구해야 함
    float3 vViewReflect = 
        normalize(ViewLightDir + 2.f * dot(-ViewLightDir, In.ViewNormal) * In.ViewNormal);
    
    // 시점에서 표면을 향하는 벡터
    float3 vEye = normalize(In.ViewPos);
    
    // 시선 벡터랑 반사 벡터를 내적해서 반사광의 세기를 구한다.
    fSpecPow = saturate(dot(-vEye, vViewReflect));
    fSpecPow = pow(fSpecPow, 30);
    
    OutColor.rgb = (OutColor.rgb * lightAttribute.color.diffuse.rgb * intensity
                    + lightAttribute.color.specular.rgb * fSpecPow * 1.f
                    + (OutColor.xyz * lightAttribute.color.ambient.rgb));
    
    //float4 Out = float4(1.f, 0.f, 1.f, 1.f);
    
    //float3 LightDir = normalize(globalLightDir);
    //// saturate() 함수는 0 이하의 값을 0으로, 1 이상의 값을 1로 바꿔줍니다.
    //float intensity = saturate(dot(-LightDir, In.Normal));
    
    //Out.xyz = (intensity * OutColor.xyz * globalLightColor) + (OutColor.xyz * globalLightAmb);
    
    return OutColor;
}