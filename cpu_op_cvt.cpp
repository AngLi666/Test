#include "cpu_op.hpp"


void cpu_op_out_cvt(APICFG* pCFG)
{
    
    CvtCFG          cvt_cfg = pCFG->cvt_cfg;
    int*            p_ifm   = cvt_cfg.p_ifm;
    sint8_t*        p_ofm   = cvt_cfg.p_ofm;
    int             in_n    = cvt_cfg.input_n;
    int             in_c    = cvt_cfg.input_c;
    int             in_h    = cvt_cfg.input_h;
    int             in_w    = cvt_cfg.input_w;

    int nSize = in_n * in_c * in_h * in_w;
    if (nSize == 0)
    {
        nSize = in_n * in_c;
    }

    int shift = pCFG->ofm_shift;\
    if (shift > 0)
    {
        for (int i = 0; i < nSize; ++i)
        {
            int val = *(p_ifm + i);
            val = val << shift;
            if (val > 127)
            {
                val = 127;
            }
            else if (val < -128)
            {
                val = -128;
            }
            *(p_ofm+i) = (sint8_t)val;
        }
    }

    else if (shift < 0){
        for (int i = 0; i < nSize; ++i)
        {
            int val = *(p_ifm + i);
            val = val >> shift;

            if (val > 127)
            {
                val = 127;
            }
            else if (val < -128)
            {
                val = -128;
            }
            *(p_ofm+i) = (sint8_t)val;
        }
    }

}