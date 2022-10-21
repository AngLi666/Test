#include "cpu_api.hpp"


void cpu_api_logsoftmax(APICFG* pCFG){

    // ClfCFG clf_cfg = pCFG->clf_cfg;
    // pCFG->clf_cfg.p_ifm = pCFG->p_ifm;
    // pCFG->clf_cfg.p_ofm = pOUT;
    cpu_op_logsoftmax(APICFG* pCFG);
}



