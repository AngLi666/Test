
typedef signed      char sint8_t;
typedef unsigned    char uint8_t;

#ifndef DEF_HPP
#define DEF_HPP


typedef struct conv_cfg_t{
    /*
    default pad zero only
    */
    int             input_n;
    int             input_c;
    int             input_h;
    int             input_w;
    int             output_n;
    int             output_c;
    int             output_h;
    int             output_w;
    int             kernel_n;
    int             kernel_c;
    int             kernel_h;
    int             kernel_w;
    int             kernel_pad_l;
    int             kernel_pad_r;
    int             kernel_pad_t;
    int             kernel_pad_b;
    int             kernel_stride_h;
    int             kernel_stride_w;
    int             kernel_dilation_h;
    int             kernel_dilation_w;
    bool            kernel_bias;
    // bool         kernel_scale;
    // bool         relu;
    sint8_t*        p_ifm;
    sint8_t*        p_wt;
    int*            p_bs;
    int*            p_ofm;
    // int*         pSL;
} ConvCFG;


typedef struct act_cfg_t{
    /*
    act_type
    0   = None
    1   = relu
    */
    int             input_n;
    int             input_c;
    int             input_h;
    int             input_w;
    int             type;
    int*            p_ifm;
    int*            p_ofm;


} ActCFG;


typedef struct clf_cfg_t{
    /*
    act_type
    0   = softmax
    1   = logsoftmax
    */
    int             input_n;
    int             input_c;
    int             input_h;
    int             input_w;
    int             type;
    sint8_t*        p_ifm;
    float*          p_ofm;
} ClfCFG;




typedef struct pool_cfg_t{
    /*
    pool_type
    0 = None
    1 = max_pool2d
    2 = avg_pool2d

    default pad zero only
    */
    int             input_n;
    int             input_c;
    int             input_h;
    int             input_w;
    int             output_n;
    int             output_c;
    int             output_h;
    int             output_w;
    int             type;
    int             pool_h;
    int             pool_w;
    int             pool_pad_t;
    int             pool_pad_b;
    int             pool_pad_l;
    int             pool_pad_r;
    int             pool_stride_h;
    int             pool_stride_w;
    int*            p_ifm;
    int*            p_ofm;
} PoolCFG;


typedef struct cvt_cfg_t{
    int             input_n;
    int             input_c;
    int             input_h;
    int             input_w;
    int             type;
    int             ofm_shift;
    int*            p_ifm;
    sint8_t*        p_ofm;
} CvtCFG;



typedef struct api_cfg_t{

    ConvCFG         conv_cfg;
    ActCFG          act_cfg;
    PoolCFG         pool_cfg;
    ClfCFG          clf_cfg;
    CvtCFG          cvt_cfg;
    int             input_n;
    int             input_c;
    int             input_h;
    int             input_w;
    int             output_n;
    int             output_c;
    int             output_h;
    int             output_w;
    int             ofm_shift;
    sint8_t*        p_ifm;
    sint8_t*        p_ofm;

} APICFG;


#endif

