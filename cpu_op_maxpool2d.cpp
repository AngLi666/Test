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


    /* 
    int outw = (w - pool_w) / stride_w + 1;
    int outh = (h - pool_h) / stride_h + 1;

    index name 
    ofm : c     h   w
    wt  : c1    h1  w1
    ofm : c2    h2  w2
    */
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
                        h2              = (ou_h-1) * st_h + wt_h;
                        w2              = (ou_w-1) * st_w + wt_w;
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
}


