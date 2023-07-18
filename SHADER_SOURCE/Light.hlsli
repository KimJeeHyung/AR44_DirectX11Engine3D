#include "ConstantBuffer.hlsli"

struct LightColor
{
    float4 diffuse;
    float4 specular;
    float4 ambient;
};

struct LightAttribute
{
    LightColor color;
    float4 position;
    float4 direction;
    
    int type;
    float radius;
    float angle;
    int padding;
};

StructuredBuffer<LightAttribute> lightAttributes : register(t13);
//StructuredBuffer<LightAttribute> lightAttributes3D : register(t14);

// 2D
void CalculateLight(in out LightColor pLightColor, float3 position, int idx)
{
    if (0 == lightAttributes[idx].type)
    {
        pLightColor.diffuse += lightAttributes[idx].color.diffuse;
    }
    else if (1 == lightAttributes[idx].type)
    {
        float length = distance(lightAttributes[idx].position.xy, position.xy);
        
        if (length < lightAttributes[idx].radius)
        {
            float ratio = 1.f - (length / lightAttributes[idx].radius);
            pLightColor.diffuse += lightAttributes[idx].color.diffuse * ratio; // * cos(time);
        }
    }
    else
    {

    }
}

// 3D
static float3 globalLightPos = float3(0.0f, 0.0f, 0.0f);
static float3 globalLightDir = float3(1.0f, -1.0f, 1.0f);
static float3 globalLightColor = float3(1.0f, 1.0f, 1.0f);
static float3 globalLightAmb = float3(0.15f, 0.15f, 0.15f);

void CalculateLight3D(float3 viewPos, float3 viewNormal, int lightIdx, inout LightColor lightColor)
{
    LightAttribute lightInfo = lightAttributes[lightIdx];
    
    float3 viewLightDir = (float3) 0.f;
    
    float fDiffPow = 0.f;
    float fSpecPow = 0.f;
    
    // Directional
    if (0 == lightInfo.type)
    {
        viewLightDir = normalize(mul(float4(lightInfo.direction.xyz, 0.f), view));
        
        // view space 상에서 빛의 세기를 구함
        fDiffPow = saturate(dot(-viewLightDir, viewNormal));
        fSpecPow = 0.f;
        
        // 반사광 세기를 구함
        // 표면의 빛의 반사 벡터
        float3 viewReflect = normalize(viewLightDir + 2.f
                            * dot(-viewLightDir, viewNormal) * viewNormal);
        
        // 시점에서 표면을 향하는 벡터
        float3 vEye = normalize(viewPos);
        
        // 시선 벡터랑 반사 벡터를 내적해서 반사광의 세기를 구한다.
        fSpecPow = saturate(dot(-vEye, viewReflect));
        fSpecPow = pow(fSpecPow, 30);
    }
    // Point
    else if (1 == lightInfo.type)
    {
        // view space 상에서 광원의 위치를 알아낸다.
        float3 vLightViewPos = mul(float4(lightInfo.position.xyz, 1.f), view);
        
        // 광원의 위치에서 표면을 향하는 벡터
        viewLightDir = viewPos - vLightViewPos;
        
        // 광원에서 표면까지의 거리를 구한다.
        float dist = length(viewLightDir);
        
        // 광원에서 표면을 향하는 단위벡터를 구한다.
        viewLightDir = normalize(viewLightDir);
        
        // 반경대비 거리에 따른 빛의 세기 비율
        float ratio = cos(saturate(dist / lightInfo.radius) * 3.1415926535 * 0.5f);
        
        // view space 상에서 표면의 빛의 세기를 구함
        fDiffPow = saturate(dot(-viewLightDir, viewNormal)) * ratio;
        
        // 반사광의 세기를 구함
        // 표면의 빛의 반사 벡터
        float3 viewReflect = normalize(viewLightDir + 2.f
                            * dot(-viewLightDir, viewNormal) * viewNormal);
        
        // 시점에서 표면을 향하는 벡터
        float3 vEye = normalize(viewPos);
        
        // 시선 벡터랑 반사 벡터를 내적해서 반사광의 세기를 구한다.
        fSpecPow = saturate(dot(-vEye, viewReflect));
        fSpecPow = pow(fSpecPow, 30);
    }
    else
    {
    }
    
    // 최종 난반사광
    lightColor.diffuse += lightInfo.color.diffuse * fDiffPow;
    
    // 정반사광
    lightColor.specular += lightInfo.color.specular * fSpecPow;
    
    // 주변광
    lightColor.ambient = lightInfo.color.ambient;
}