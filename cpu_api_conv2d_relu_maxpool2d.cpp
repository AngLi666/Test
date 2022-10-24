#include "cpu_api.hpp"


void cpu_api_conv2d_relu_maxpool2d(APICFG* pCFG){

    ConvCFG conv_cfg        = pCFG->conv_cfg;
    sint8_t*        p_ifm   = conv_cfg.p_ifm;
    sint8_t*        p_wt    = conv_cfg.p_wt;
    int*            p_bs    = conv_cfg.p_bs;
    int*            p_ofm   = conv_cfg.p_ofm;
    int             ou_n    = conv_cfg.output_n;
    int             ou_c    = conv_cfg.output_c;
    int             ou_h    = conv_cfg.output_h;
    int             ou_w    = conv_cfg.output_w;
    
    const int nConvOFM = ou_n * ou_c * ou_h * ou_w;
    int* pConvOFM = new int[nConvOFM * sizeof(int)];
    pCFG->conv_cfg.p_ifm = pCFG->p_ifm;
    pCFG->conv_cfg.p_ofm = pConvOFM;
    
    
    pCFG->act_cfg.p_ifm = pConvOFM;
    pCFG->act_cfg.p_ofm = pConvOFM;


    PoolCFG pool_cfg        = pCFG->pool_cfg;
    int             po_n    = pool_cfg.output_n;
    int             po_c    = pool_cfg.output_c;
    int             po_h    = pool_cfg.output_h;
    int             po_w    = pool_cfg.output_w;
    const int nPoolOFM = po_n * po_c * po_h * po_w;
    int* pPoolOFM = new int[nPoolOFM * sizeof(int)];

    pCFG->pool_cfg.p_ifm = pConvOFM;
    pCFG->pool_cfg.p_ofm = pPoolOFM;


    CvtCFG cvt_cfg;
    cvt_cfg.ofm_shift       = pCFG->ofm_shift;
    cvt_cfg.input_n         = pool_cfg.output_n;
    cvt_cfg.input_c         = pool_cfg.output_c;
    cvt_cfg.input_h         = pool_cfg.output_h;
    cvt_cfg.input_w         = pool_cfg.output_w;
    cvt_cfg.p_ifm           = pPoolOFM;
    cvt_cfg.p_ofm           = pCFG->p_ofm;
    pCFG->cvt_cfg = cvt_cfg;

    cpu_op_conv2d(pCFG);
    cpu_op_relu(pCFG);
    cpu_op_maxpool2d(pCFG);
    cpu_op_out_cvt(pCFG);
    
    delete[] pConvOFM;
    delete[] pPoolOFM;
}


