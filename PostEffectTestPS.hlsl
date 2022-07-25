#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);
Texture2D<float4> tex1 : register(t1); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp1 : register(s1);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

//float4 main(VSOutput input) : SV_TARGET
//{
//	float4 texcolor = tex0.Sample(smp,input.uv);
//	return float4(1-texcolor.rgb, 1);
//}
//
//    float offsetU = 3.5f / 1280.0f;
//    float offsetV = 3.5f / 720.0f;
//
//    // ��e�N�Z������E�̃e�N�Z���̃J���[���T���v�����O����
//    texcolor += tex.Sample(smp, input.uv + float2(offsetU, 0.0f));
//
//    // ��e�N�Z�����獶�̃e�N�Z���̃J���[���T���v�����O����
//    texcolor += tex.Sample(smp, input.uv + float2(-offsetU, 0.0f));
//
//    // ��e�N�Z�����牺�̃e�N�Z���̃J���[���T���v�����O����
//    texcolor += tex.Sample(smp, input.uv + float2(0.0f, offsetV));
//
//    // ��e�N�Z�������̃e�N�Z���̃J���[���T���v�����O����
//    texcolor += tex.Sample(smp, input.uv + float2(0.0f, -offsetV));
//
//    // ��e�N�Z������E���̃e�N�Z���̃J���[���T���v�����O����
//    texcolor += tex.Sample(smp, input.uv + float2(offsetU, offsetV));
//
//    // ��e�N�Z������E��̃e�N�Z���̃J���[���T���v�����O����
//    texcolor += tex.Sample(smp, input.uv + float2(offsetU, -offsetV));
//
//    // ��e�N�Z�����獶���̃e�N�Z���̃J���[���T���v�����O����
//    texcolor += tex.Sample(smp, input.uv + float2(-offsetU, offsetV));
//
//    // ��e�N�Z�����獶��̃e�N�Z���̃J���[���T���v�����O����
//    texcolor += tex.Sample(smp, input.uv + float2(-offsetU, -offsetV));
//
//    // ��e�N�Z���ƋߖT8�e�N�Z���̕��ςȂ̂�9�ŏ��Z����
//    texcolor /= 9.0f;
//    //return float4(texcolor.rgb, 1);
//	//���x�̕ύX
//	//return float4(texcolor.rgb*2.0f,1);
//	//�F���]
//	return float4(1-texcolor.rgb, 1);
//
//}
//

float4 main(VSOutput input) :SV_TARGET
{
     float4 movePixel = 1.0f / 5;

    float offsetU = 3.5f / 1280.0f;
    float offsetV = 3.5f / 720.0f;

    float4 colortex0 = tex0.Sample(smp,input.uv);
    float4 colortex1 = tex1.Sample(smp,input.uv);
    movePixel *= colortex0;
    float4 color = colortex0;
    //float4 color1 = color;
    if (fmod(input.uv.y, 0.1f) < 0.05f) {
        // //��e�N�Z������E�̃e�N�Z���̃J���[���T���v�����O����
        color += tex0.Sample(smp, input.uv + float2(offsetU, 0.0f));
        // ��e�N�Z�����獶�̃e�N�Z���̃J���[���T���v�����O����
        color += tex0.Sample(smp, input.uv + float2(-offsetU, 0.0f));
        // ��e�N�Z�����牺�̃e�N�Z���̃J���[���T���v�����O����
        color += tex0.Sample(smp, input.uv + float2(0.0f, offsetV));

        // ��e�N�Z�������̃e�N�Z���̃J���[���T���v�����O����
        color += tex0.Sample(smp, input.uv + float2(0.0f, -offsetV));

        // ��e�N�Z������E���̃e�N�Z���̃J���[���T���v�����O����
        color += tex0.Sample(smp, input.uv + float2(offsetU, offsetV));

        // ��e�N�Z������E��̃e�N�Z���̃J���[���T���v�����O����
        color += tex0.Sample(smp, input.uv + float2(offsetU, -offsetV));
        // ��e�N�Z�����獶���̃e�N�Z���̃J���[���T���v�����O����
        color += tex0.Sample(smp, input.uv + float2(-offsetU, offsetV));

        // ��e�N�Z�����獶��̃e�N�Z���̃J���[���T���v�����O����
        color += tex0.Sample(smp, input.uv + float2(-offsetU, -offsetV));
        // ��e�N�Z���ƋߖT8�e�N�Z���̕��ςȂ̂�9�ŏ��Z����
        color /= 9.0f;
    }
    if (fmod(input.uv.y, 0.1f) < 0.05f) {
        color += -tex1.Sample(smp, input.uv);
        //color += -tex0.Sample(smp, input.uv);
       /* color = colortex1;*/
        }
    // 
    //
        return float4(color.rgb, 1);
        //
        //    //return float4(color.rgb, 1);
        //    //return float4(1 - color.rgb, 1);
}