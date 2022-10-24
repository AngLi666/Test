#include "cpu_op.hpp"


void maxpool_pad_int32(int* ofm, int* ifm, PoolCFG* pool_cfg)
{

    int             ou_n    = pool_cfg->output_n;
    int             ou_c    = pool_cfg->output_c;
    int             ou_h    = pool_cfg->output_h;
    int             ou_w    = pool_cfg->output_w;
    int             in_n    = pool_cfg->input_n;
    int             in_c    = pool_cfg->input_c;
    int             in_h    = pool_cfg->input_h;
    int             in_w    = pool_cfg->input_w;
    int             pad_t   = pool_cfg->pool_pad_t;
    int             pad_b   = pool_cfg->pool_pad_b;
    int             pad_l   = pool_cfg->pool_pad_l;
    int             pad_r   = pool_cfg->pool_pad_r;
    int             wt_h    = pool_cfg->pool_h;
    int             wt_w    = pool_cfg->pool_w;
    int             st_h    = pool_cfg->pool_stride_h;
    int             st_w    = pool_cfg->pool_stride_w;
    int*            p_ifm   = ifm;
    int*            p_ofm   = ofm;

    memset(ofm, 0, ou_n*ou_c*ou_h*ou_w*sizeof(int));

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


int calc_max_i32(const int* input, int c, int h, int w, int cur_ch, int start_h,
    int start_w, int end_h, int end_w)
{
    int max = 0;
    max = input[cur_ch * h * w + start_h * w + start_w];
    int tmp = 0;
    for (int i = start_h; i < end_h; i++)
    {
        for (int j = start_w; j < end_w; j++)
        {
            tmp = input[cur_ch * h * w + i * w + j];
            max = max > tmp ? max : tmp;
        }
    }

    return max;
}




void cpu_op_maxpool2d(APICFG* pCFG)
{
    PoolCFG pool_cfg        = pCFG->pool_cfg;
    int*            p_ifm   = pool_cfg.p_ifm;
    int*            p_ofm   = pool_cfg.p_ofm;
    int             ou_n    = pool_cfg.output_n;
    int             ou_c    = pool_cfg.output_c;
    int             ou_h    = pool_cfg.output_h;
    int             ou_w    = pool_cfg.output_w;
    int             in_n    = pool_cfg.input_n;
    int             in_c    = pool_cfg.input_c;
    int             in_h    = pool_cfg.input_h;
    int             in_w    = pool_cfg.input_w;
    int             pad_t   = pool_cfg.pool_pad_t;
    int             pad_b   = pool_cfg.pool_pad_b;
    int             pad_l   = pool_cfg.pool_pad_l;
    int             pad_r   = pool_cfg.pool_pad_r;
    int             wt_h    = pool_cfg.pool_h;
    int             wt_w    = pool_cfg.pool_w;
    int             st_h    = pool_cfg.pool_stride_h;
    int             st_w    = pool_cfg.pool_stride_w;



    int batch = in_n;
    int channel = in_c;
    int out_h = ou_h;
    int out_w = ou_w;
    int input_chw = channel * in_h * in_w;
    int output_chw = channel * out_h * out_w;

    int stride_h = st_h;
    int stride_w = st_w;

    int pad_h = pad_t;
    int pad_w = pad_l;

    int kernel_h = wt_h;
    int kernel_w = wt_w;

    int* input = p_ifm;
    int* output = p_ofm;

    for (int n = 0; n < batch; n++)
    {
        const int* input_cur = input + n * input_chw;
        for (int c = 0; c < channel; c++)
        {
            for (int ph = 0; ph < out_h; ph++)
            {
                for (int pw = 0; pw < out_w; pw++)
                {
                    int offset = 0;
                    int h_start = ph * stride_h - pad_h;
                    int h_end = h_start + kernel_h;

                    if (h_end > in_h + pad_h)
                        h_end = in_h + pad_h;
                    int w_start = pw * stride_w - pad_w;
                    int w_end = w_start + kernel_w;

                    if (w_end > in_w + pad_w)
                        w_end = in_w + pad_w;

                    h_start = h_start > 0 ? h_start : 0;
                    w_start = w_start > 0 ? w_start : 0;
                    h_end = h_end < in_h ? h_end : in_h;
                    w_end = w_end < in_w ? w_end : in_w;

                    offset = n * output_chw + c * out_h * out_w + ph * out_w + pw;

                    int max = calc_max_i32(input_cur, channel, in_h, in_w, c, h_start, w_start,
                        h_end, w_end);
                    output[offset] = max;

                }
            }
        }
    }



    /*
    int outw = (w - pool_w) / stride_w + 1;
    int outh = (h - pool_h) / stride_h + 1;

    index name
    ofm : c     h   w
    wt  : c1    h1  w1
    ofm : c2    h2  w2
    */


    /*

    const int pad_fm_nbyte = ou_n*ou_c*ou_h*ou_w;
    
    int* pad_ifm = nullptr;
    bool flag_pad = false;
    if (pad_t==0 && pad_b==0 && pad_l==0 && pad_r==0)
    {
        pad_ifm = p_ifm;
    }
    else
    {
        flag_pad = true;
        pad_ifm = new int[pad_fm_nbyte];
        maxpool_pad_int32(pad_ifm, p_ifm, &pool_cfg);

        in_h = in_h + pad_t + pad_b;
        in_w = in_w + pad_l + pad_r;
    }

    int c2, h2, w2;
    for (int c = 0; c < ou_c; ++c)
    {
        for (int h = 0; h < ou_h; ++h)
        {
            for (int w = 0; w < ou_w; ++w)
            {
                // wt_n = ou_c;
                int max_piont = 0;
                for (int h1 = 0; h1 < wt_h; ++h1)
                {
                    for (int w1 = 0; w1 < wt_w; ++w1)
                    {
                        c2              = c;
                        h2              = ou_h * st_h + h1;
                        w2              = ou_w * st_w + w1;
                        int ifm         = *(pad_ifm + c2*in_h*in_w + h2*in_w + w2);
                        if(ifm > max_piont){
                            max_piont = ifm;
                        }
                    }

                }
                p_ofm   = pool_cfg.p_ofm + c*ou_w*ou_h + h*ou_w + w;
                *p_ofm  = max_piont;

            }

        }
    }

    if (flag_pad)
    {
        delete[] pad_ifm;
    }

    */
}


