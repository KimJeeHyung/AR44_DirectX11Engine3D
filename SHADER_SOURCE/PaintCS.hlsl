float a = 12.9898f;
float b = 78.233f;
float c = 43758.5453f;
float rand(float2 co)
{
    return frac(sin(dot(co, float2(a, b))) * c);
}

uint Hash(uint s)
{
    s ^= 2747636419u;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    s ^= s >> 16;
    s *= 2654435769u;
    return s;
}

float Random(uint seed)
{
    return float(Hash(seed)) / 4294967295.0; // 2^32-1
}

RWTexture2D<float4> tex : register(u0);

// SV_GroupID : 스레드에 속한 그룹의 좌표(Z값)
// SV_GroupThreadID : 그룹 내에서 스레드의 좌표(XY값)
// SV_GroupIndex : 그룹 내에서 스레드의 인덱스 좌표(1차원)
// SV_DispatchThreadID : 전체 스레드 기준으로 호출된 좌표

[numthreads(32, 32, 1)] // 그룹 당 쓰레드 개수(최대 1024개까지 지정 가능)
void main( uint3 DTid : SV_DispatchThreadID )
{
    if (1024 <= DTid.x || 1024 <= DTid.y)
    {
        return;
    }
    
    float w, h;
    tex.GetDimensions(w, h);
    float r = Random(DTid.x + DTid.y * w);
    float g = Random(DTid.x + DTid.y * w);
    float b = Random(DTid.x + DTid.y * w);
    
    tex[DTid.xy] = float4(r, g, b, 1.f);
}