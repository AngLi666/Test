#include "cpu_op.hpp"


void pad(APICFG* pCFG)
{

    sint8_t*        p_ifm   = pCFG->ifm;
    sint8_t*        p_ofm   = pCFG->ofm;
    int             pad_t   = pCFG->kernel_pad_t;
    int             pad_b   = pCFG->kernel_pad_b;
    int             pad_l   = pCFG->kernel_pad_l;
    int             pad_r   = pCFG->kernel_pad_r;
    int             in_n    = pCFG->input_n;
    int             in_c    = pCFG->input_c;
    int             in_h    = pCFG->input_h;
    int             in_w    = pCFG->input_w;
    int             ou_n    = in_n;
    int             ou_c    = in_c;
    int             ou_h    = in_h + pad_t + pad_b;
    int             ou_w    = in_w + pad_l + pad_r;

    memset(p_ofm, 0, ou_n*ou_c*ou_h*ou_w);

    for (int c = 0; i < in_c; ++i)
    {
        for (int h = 0; i < in_h; ++j)
        {
            for (int w = 0; i < in_w; ++k)
            {
                p_ifm = c*in_w*in_h + h*in_w + w;
                p_ofm = c*ou_w*ou_h + (h+pad_t)*ou_w + w+pad_l;
                *p_ofm = *p_ifm;
            }

        }
    }

}
