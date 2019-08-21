matrix World;
matrix View;
matrix Projection;

float4 Color = float4(1, 1, 1, 1);
//-----------------------------------------------------------------------------
//Strucutres
//-----------------------------------------------------------------------------
struct VertexInput
{
    float4 Position : POSITION0;
    float3 color : COLOR0;
};
struct VertexOutput
{
    float4 Position : SV_POSITION0;
    float3 Color : COLOR0;

};
//-----------------------------------------------------------------------------
//VerTex shader
//-----------------------------------------------------------------------------

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);//mul 곱하기 정점->월드 공간으로 바꿔주는것
    output.Position = mul(output.Position, View); //mul 곱하기 정점->월드 공간으로 바꿔주는것
    output.Position = mul(output.Position, Projection); //mul 곱하기 정점->월드 공간으로 바꿔주는것
    output.Color = input.color;

    return output;


} 
//-----------------------------------------------------------------------------
//Pixel shader
//-----------------------------------------------------------------------------
float4 PS(VertexOutput input) :SV_TARGET0
{
    return Color;

}
//-----------------------------------------------------------------------------
//Technique
//-----------------------------------------------------------------------------
technique11 T0{
    pass P0{

        SetVertexShader(CompileShader(vs_5_0, VS()));

        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}