cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

cbuffer Grid : register(b2)
{
    float4 gCameraPosition;
    float2 gCameraScale;
    float2 gResolution;
}

cbuffer Fade : register(b3)
{
    float4 fCameraPosition;
    float2 fCameraScale;
    float2 fResolution;
    float fadeDeltaTime;
    float3 fPadding;
}

cbuffer Animation : register(b4)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}

cbuffer NumberOfLight : register(b5)
{
    uint numberOfLight;
}

cbuffer ParticleSystem : register(b6)
{
    float4 worldPosition;
    float4 startColor;
    float4 startSize;
    
    uint maxParticles;
    uint simulationSpace;
    float radius;
    float startSpeed;
    
    float startLifeTime;
    float deltaTime;
    float elapsedTime;  // 누적시간
    int pPadding;
}

//cbuffer Noise : register(b7)
//{
//    float4 NoiseSize;
//}