#include "cpu_op.hpp"
#include <stdlib.h>
#include <math.h>


void cpu_op_logsoftmax(APICFG* pCFG)
{
    ClfCFG          clf_cfg = pCFG->clf_cfg;
    sint8_t*        p_ifm   = clf_cfg.p_ifm;
    float*          p_ofm   = clf_cfg.p_ofm;
    int             type    = clf_cfg.type;
    int             in_n    = clf_cfg.input_n;
    int             in_c    = clf_cfg.input_c;
    // int             in_h    = clf_cfg.input_h;
    // int             in_w    = clf_cfg.input_w;

    int num = in_n * in_c;

    double softmax_denominator = 0;

    for (int i = 0; i < num; i++)  {
        int inp = int(*(p_ifm + i));
        softmax_denominator += exp(inp);
    }  

    for (int i = 0; i < num; i++) {
        int inp = int(*(p_ifm + i));
        double computed_value = exp(inp) / softmax_denominator;
        *p_ofm = float(log2(computed_value));
        p_ofm ++;
    }
}

