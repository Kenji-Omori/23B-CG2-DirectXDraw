struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

PixelShaderOutput main() : SV_TARGET
{
    PixelShaderOutput output;
    output.color = float4(1.0, 1.0, 1.0, 1.0);
    return output;
}