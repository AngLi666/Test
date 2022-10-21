#include "cpu_op.hpp"


void cpu_op_relu(APICFG* pCFG)
{
    ActCFG          act_cfg = pCFG->act_cfg;
    int*            p_ifm   = act_cfg.p_ifm;
    int*            p_ofm   = act_cfg.p_ofm;
    int             type    = act_cfg.type;
    int             in_n    = act_cfg.input_n;
    int             in_c    = act_cfg.input_c;
    int             in_h    = act_cfg.input_h;
    int             in_w    = act_cfg.input_w;

    int num = in_n * in_c * in_h * in_w;
    p_ofm = p_ifm;
    for (int i = 0; i < num; ++i)
    {
        if ((*p_ofm) < 0){
            *p_ofm = 0;
        }
        p_ofm ++;
    }
}
