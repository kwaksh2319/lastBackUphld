cbuffer CB_PerFrame
{
    matrix View;
    matrix Projection;
};

matrix World;


//---------------------------------------------------------
//Structure
//---------------------------------------------------------
struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
};

struct VertexOutput
{
    float4 Position : SV_POSITION0;
    float2 Uv : UV0;
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
    output.Uv = input.Uv;

    return output;
}

//---------------------------------------------------------
//Pixel Shader
//---------------------------------------------------------
//Texture2D Map;
//SamplerState Sampler;

float4 PS(VertexOutput input, uniform float4 color) : SV_TARGET0
{
   
    //return float4(0, 1, 0, 1);
    return color;
}

//---------------------------------------------------------
//Techique Version
//---------------------------------------------------------
technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS(float4(0, 1, 0, 1))));

    }
    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS(float4(1, 0, 0, 1))));

    }
  
}