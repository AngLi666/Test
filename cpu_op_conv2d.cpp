#include "cpu_op.hpp"
#include <iostream>


void conv_pad_int8(sint8_t* ofm, sint8_t* ifm, ConvCFG* pConvCFG)
{

    sint8_t*        p_ifm   = ifm;
    sint8_t*        p_ofm   = ofm;
    int             pad_t   = pConvCFG->kernel_pad_t;
    int             pad_b   = pConvCFG->kernel_pad_b;
    int             pad_l   = pConvCFG->kernel_pad_l;
    int             pad_r   = pConvCFG->kernel_pad_r;
    int             in_n    = pConvCFG->input_n;
    int             in_c    = pConvCFG->input_c;
    int             in_h    = pConvCFG->input_h;
    int             in_w    = pConvCFG->input_w;
    int             ou_n    = in_n;
    int             ou_c    = in_c;
    int             ou_h    = in_h + pad_t + pad_b;
    int             ou_w    = in_w + pad_l + pad_r;
    
    memset(ofm, 0, ou_n*ou_c*ou_h*ou_w);

    for (int c = 0; c < in_c; ++c)
    {
        for (int h = 0; h < in_h; ++h)
        {
            for (int w = 0; w < in_w; ++w)
            {
                p_ifm = ifm + c*in_w*in_h + h*in_w + w;
                p_ofm = ofm + c*ou_w*ou_h + (h+pad_t)*ou_w + w+pad_l;
                *p_ofm = *p_ifm;
            }

        }
    }

}


void cpu_op_conv2d(APICFG* pCFG)
{
    ConvCFG conv_cfg        = pCFG->conv_cfg;
    sint8_t*        p_ifm   = conv_cfg.p_ifm;
    sint8_t*        p_wt    = conv_cfg.p_wt;
    int*            p_bs    = conv_cfg.p_bs;
    int*            p_ofm   = conv_cfg.p_ofm;
    int             ou_n    = conv_cfg.output_n;
    int             ou_c    = conv_cfg.output_c;
    int             ou_h    = conv_cfg.output_h;
    int             ou_w    = conv_cfg.output_w;
    int             in_n    = conv_cfg.input_n;
    int             in_c    = conv_cfg.input_c;
    int             in_h    = conv_cfg.input_h;
    int             in_w    = conv_cfg.input_w;
    int             pad_t   = conv_cfg.kernel_pad_t;
    int             pad_b   = conv_cfg.kernel_pad_b;
    int             pad_l   = conv_cfg.kernel_pad_l;
    int             pad_r   = conv_cfg.kernel_pad_r;
    int             wt_n    = conv_cfg.kernel_n;
    int             wt_c    = conv_cfg.kernel_c;
    int             wt_h    = conv_cfg.kernel_h;
    int             wt_w    = conv_cfg.kernel_w;
    int             st_h    = conv_cfg.kernel_stride_h;
    int             st_w    = conv_cfg.kernel_stride_w;


    int batch = in_n;
    // TODO: add group to conv_cfg
    int group = 1;
    int dilation_h = conv_cfg.kernel_dilation_h;
    int dilation_w = conv_cfg.kernel_dilation_w;

    int input_c = in_c / group;
    int input_h = in_h;
    int input_w = in_w;
    int output_c = ou_c / group;
    int output_h = ou_h;
    int output_w = ou_w;

    int kernel_size = input_c * wt_h * wt_w;
    int n, g, c, h, w, kc, kh, kw;
    int input_offset = 0;
    int kernel_offset = 0;
    int output_offset = 0;


    for (n = 0; n < batch; ++n)
    {
        for (g = 0; g < group; ++g)
        {
            for (c = 0; c < output_c; ++c)
            {
                for (h = 0; h < output_h; ++h)
                {
                    for (w = 0; w < output_w; ++w)
                    {
                        const int h_start = (h * st_h) - pad_t;
                        const int w_start = (w *st_w) - pad_l;
                        int total = 0;

                        output_offset = n * group * output_c * output_h * output_w + g * output_c * output_h * output_w + c * output_h * output_w + h * output_w + w;

                        for (kc = 0; kc < input_c; ++kc)
                        {
                            for (kh = 0; kh < wt_h; ++kh)
                            {
                                for (kw = 0; kw < wt_w; ++kw)
                                {
                                    const int cur_y = h_start + dilation_h * kh;
                                    const int cur_x = w_start + dilation_w * kw;
                                    // If the location is outside the bounds of the input image,
                                    // use zero as a default value.
                                    if ((cur_x >= 0) && (cur_x < input_w) && (cur_y >= 0) && (cur_y < input_h))
                                    {
                                        input_offset = n * group * input_c * input_h * input_w + g * input_c * input_h * input_w + kc * input_h * input_w + cur_y * input_w + cur_x;
                                        kernel_offset = g * output_c * kernel_size + c * kernel_size + kc * wt_h * wt_w + kh * wt_w + kw;

                                        total += sint8_t(p_ifm[input_offset]) * sint8_t(p_wt[kernel_offset]);
                                    }
                                }
                            }
                        }

                        if (conv_cfg.kernel_bias)
                            total += p_bs[output_c * g + c];

                        p_ofm[output_offset] = total;
                    }
                }
            }
        }
    }



    /*

    const int pad_fm_nbyte = ou_n*ou_c*ou_h*ou_w;
    sint8_t* pad_ifm = nullptr;
    bool flag_pad = false;
    if (pad_t==0 && pad_b==0 && pad_l==0 && pad_r==0)
    {
        pad_ifm = p_ifm;
    }
    else
    {
        flag_pad = true;
        pad_ifm = new sint8_t[pad_fm_nbyte];
        conv_pad_int8(pad_ifm, p_ifm, &conv_cfg);
        in_h = in_h + pad_t + pad_b;
        in_w = in_w + pad_l + pad_r;
    }

    const int wt_extent_w = dia_w * (wt_w - 1) + 1;
    const int wt_extent_h = dia_h * (wt_h - 1) + 1;
    int outw = (w - wt_w) / stride_w + 1;
    int outh = (h - wt_h) / stride_h + 1;

    index name
    ofm : c     h   w
    wt  : c1    h1  w1
    ofm : c2    h2  w2
    */


    /*

    int c2, h2, w2;

    for (int c = 0; c < ou_c; ++c)
    {
        // for ofm[ci]
        for (int h = 0; h < ou_h; ++h)
        {
            for (int w = 0; w < ou_w; ++w)
            {
                
                // wt_n = ou_c;
                int piont = 0;
                for (int c1 = 0; c1 < wt_c; ++c1)
                {
                    for (int h1 = 0; h1 < wt_h; ++h1)
                    {
                        for (int w1 = 0; w1 < wt_w; ++w1)
                        {
                            c2              = c1; 
                            h2              = (h-1) * st_h + h1;
                            w2              = (w-1) * st_w + w1;
                            sint8_t iwt     = *(p_wt + c1*wt_h*wt_w + h1*wt_w + w1);
                            sint8_t ifm     = *(pad_ifm + c2*in_h*in_w + h2*in_w + w2);
                            piont           = piont + iwt * ifm;
                        }

                    }
                }
                
                p_ofm   = conv_cfg.p_ofm + c*ou_w*ou_h + h*ou_w + w;
                *p_ofm  = piont;

            }

        }
    }

    if (conv_cfg.kernel_bias)
    {
        for (int c = 0; c < ou_c; ++c)
        {
            // for ofm[ci]
            int bias = *(p_bs + c);
            for (int h = 0; h < ou_h; ++h)
            {
                for (int w = 0; w < ou_w; ++w)
                {
                    p_ofm = conv_cfg.p_ofm + c*ou_w*ou_h + h*ou_w + w;
                    *p_ofm = (*p_ofm) + bias;
                }
            }
        }

    }

    if (flag_pad)
    {
        delete[] pad_ifm;
    }

    */

}


