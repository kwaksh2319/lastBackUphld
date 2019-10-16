cbuffer CB_PerFrame
{
    matrix View;
    matrix Projection;
};

matrix World;

float4 Color = float4(1, 1, 1, 1);


//---------------------------------------------------------
//Structure
//---------------------------------------------------------
struct VertexInput
{
    float4 Position : POSITION0;
    float3 Color : COLOR0;
    
};

struct VertexOutput
{
    float4 Position : SV_POSITION0;
    float3 Color : COLOR0;
 
};

//---------------------------------------------------------
//Vertex Shader
//---------------------------------------------------------
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.Color = input.Color;

    return output;
}

//---------------------------------------------------------
//Pixel Shader
//---------------------------------------------------------
//Texture2D Map;
//SamplerState Sampler;

float4 PS(VertexOutput input) : SV_TARGET0
{
   
   
    return Color;
}

//---------------------------------------------------------
//Techique Version
//---------------------------------------------------------
technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));

    }
   
  
}