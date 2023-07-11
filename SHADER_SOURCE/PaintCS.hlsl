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

// SV_GroupID : �����忡 ���� �׷��� ��ǥ(Z��)
// SV_GroupThreadID : �׷� ������ �������� ��ǥ(XY��)
// SV_GroupIndex : �׷� ������ �������� �ε��� ��ǥ(1����)
// SV_DispatchThreadID : ��ü ������ �������� ȣ��� ��ǥ

[numthreads(32, 32, 1)] // �׷� �� ������ ����(�ִ� 1024������ ���� ����)
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