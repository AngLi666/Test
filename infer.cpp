
        
#include "infer.hpp"


void infer()
{       

	run_0010_conv2d_relu_maxpool2d();

	run_0020_conv2d_relu_maxpool2d();

	run_0030_conv2d_relu();

	run_0040_flatten();

	run_0050_linear_relu();

	run_0060_linear();

	run_0070_logsoftmax();

}


InputDataInfoT* getInputDataInfo() 
{ 
    return &input_data_info; 
}
OutputDataInfoT* getOutputDataInfo() 
{ 
    return &output_data_info; 
}


void run_0010_conv2d_relu_maxpool2d()
{       
        
    ConvCFG conv_cfg;
    conv_cfg.input_n                = 1;
    conv_cfg.input_c                = 1;
    conv_cfg.input_h                = 28;
    conv_cfg.input_w                = 28;
    conv_cfg.output_n               = 1;
    conv_cfg.output_c               = 10;
    conv_cfg.output_h               = 24;
    conv_cfg.output_w               = 24;    
    conv_cfg.kernel_n               = 10;
    conv_cfg.kernel_c               = 1;
    conv_cfg.kernel_h               = 5;
    conv_cfg.kernel_w               = 5;
    conv_cfg.kernel_pad_l           = 0;
    conv_cfg.kernel_pad_r           = 0;
    conv_cfg.kernel_pad_t           = 0;
    conv_cfg.kernel_pad_b           = 0;
    conv_cfg.kernel_stride_h        = 1;
    conv_cfg.kernel_stride_w        = 1;
    conv_cfg.kernel_dilation_h      = 1;
    conv_cfg.kernel_dilation_w      = 1;
    conv_cfg.kernel_bias            = 1;
    conv_cfg.p_ifm                  = 0;
    conv_cfg.p_ofm                  = 0;
    conv_cfg.p_wt                   = pWT + 0;
    conv_cfg.p_bs                   = pBS + 0;
            
    ActCFG act_cfg;
    act_cfg.input_n                 = 1;
    act_cfg.input_c                 = 10;
    act_cfg.input_h                 = 24;
    act_cfg.input_w                 = 24;
    act_cfg.type                    = 1;
    act_cfg.p_ifm                   = 0;
    act_cfg.p_ofm                   = 0;
            
    /*
    pool_type
    0 = None
    1 = max_pool2d
    2 = avg_pool2d
    default pad zero only
    */
    PoolCFG pool_cfg;
    pool_cfg.input_n                = 1;
    pool_cfg.input_c                = 10;
    pool_cfg.input_h                = 24;
    pool_cfg.input_w                = 24;
    pool_cfg.output_n               = 1;
    pool_cfg.output_c               = 10;
    pool_cfg.output_h               = 12;
    pool_cfg.output_w               = 12; 
    pool_cfg.type                   = 1;
    pool_cfg.pool_h                 = 2;
    pool_cfg.pool_w                 = 2;
    pool_cfg.pool_pad_t             = 0;
    pool_cfg.pool_pad_b             = 0;
    pool_cfg.pool_pad_l             = 0;
    pool_cfg.pool_pad_r             = 0;
    pool_cfg.pool_stride_h          = 2;
    pool_cfg.pool_stride_w          = 2;
    pool_cfg.p_ifm                  = 0;
    pool_cfg.p_ofm                  = 0;
        
	APICFG api_cfg;
	api_cfg.conv_cfg                = conv_cfg;
	api_cfg.act_cfg                 = act_cfg;
	api_cfg.pool_cfg                = pool_cfg;
	api_cfg.input_n                 = 1;
    api_cfg.input_c                 = 1;
    api_cfg.input_h                 = 28;
    api_cfg.input_w                 = 28;
	api_cfg.output_n                = 1;
    api_cfg.output_c                = 10;
    api_cfg.output_h                = 12;
    api_cfg.output_w                = 12;
	api_cfg.ofm_shift               = -9;
    api_cfg.p_ifm                   = pFM + 0;
    api_cfg.p_ofm                   = pFM + 784;

	cpu_api_conv2d_relu_maxpool2d(&api_cfg);
}


void run_0020_conv2d_relu_maxpool2d()
{       
        
    ConvCFG conv_cfg;
    conv_cfg.input_n                = 1;
    conv_cfg.input_c                = 10;
    conv_cfg.input_h                = 12;
    conv_cfg.input_w                = 12;
    conv_cfg.output_n               = 1;
    conv_cfg.output_c               = 20;
    conv_cfg.output_h               = 8;
    conv_cfg.output_w               = 8;    
    conv_cfg.kernel_n               = 20;
    conv_cfg.kernel_c               = 10;
    conv_cfg.kernel_h               = 5;
    conv_cfg.kernel_w               = 5;
    conv_cfg.kernel_pad_l           = 0;
    conv_cfg.kernel_pad_r           = 0;
    conv_cfg.kernel_pad_t           = 0;
    conv_cfg.kernel_pad_b           = 0;
    conv_cfg.kernel_stride_h        = 1;
    conv_cfg.kernel_stride_w        = 1;
    conv_cfg.kernel_dilation_h      = 1;
    conv_cfg.kernel_dilation_w      = 1;
    conv_cfg.kernel_bias            = 1;
    conv_cfg.p_ifm                  = 0;
    conv_cfg.p_ofm                  = 0;
    conv_cfg.p_wt                   = pWT + 250;
    conv_cfg.p_bs                   = pBS + 40;
            
    ActCFG act_cfg;
    act_cfg.input_n                 = 1;
    act_cfg.input_c                 = 20;
    act_cfg.input_h                 = 8;
    act_cfg.input_w                 = 8;
    act_cfg.type                    = 1;
    act_cfg.p_ifm                   = 0;
    act_cfg.p_ofm                   = 0;
            
    /*
    pool_type
    0 = None
    1 = max_pool2d
    2 = avg_pool2d
    default pad zero only
    */
    PoolCFG pool_cfg;
    pool_cfg.input_n                = 1;
    pool_cfg.input_c                = 20;
    pool_cfg.input_h                = 8;
    pool_cfg.input_w                = 8;
    pool_cfg.output_n               = 1;
    pool_cfg.output_c               = 20;
    pool_cfg.output_h               = 4;
    pool_cfg.output_w               = 4; 
    pool_cfg.type                   = 1;
    pool_cfg.pool_h                 = 2;
    pool_cfg.pool_w                 = 2;
    pool_cfg.pool_pad_t             = 0;
    pool_cfg.pool_pad_b             = 0;
    pool_cfg.pool_pad_l             = 0;
    pool_cfg.pool_pad_r             = 0;
    pool_cfg.pool_stride_h          = 2;
    pool_cfg.pool_stride_w          = 2;
    pool_cfg.p_ifm                  = 0;
    pool_cfg.p_ofm                  = 0;
        
	APICFG api_cfg;
	api_cfg.conv_cfg                = conv_cfg;
	api_cfg.act_cfg                 = act_cfg;
	api_cfg.pool_cfg                = pool_cfg;
	api_cfg.input_n                 = 1;
    api_cfg.input_c                 = 10;
    api_cfg.input_h                 = 12;
    api_cfg.input_w                 = 12;
	api_cfg.output_n                = 1;
    api_cfg.output_c                = 20;
    api_cfg.output_h                = 4;
    api_cfg.output_w                = 4;
	api_cfg.ofm_shift               = -8;
    api_cfg.p_ifm                   = pFM + 784;
    api_cfg.p_ofm                   = pFM + 2224;

	cpu_api_conv2d_relu_maxpool2d(&api_cfg);
}


void run_0030_conv2d_relu()
{       
        
    ConvCFG conv_cfg;
    conv_cfg.input_n                = 1;
    conv_cfg.input_c                = 20;
    conv_cfg.input_h                = 4;
    conv_cfg.input_w                = 4;
    conv_cfg.output_n               = 1;
    conv_cfg.output_c               = 20;
    conv_cfg.output_h               = 4;
    conv_cfg.output_w               = 4;    
    conv_cfg.kernel_n               = 20;
    conv_cfg.kernel_c               = 20;
    conv_cfg.kernel_h               = 3;
    conv_cfg.kernel_w               = 3;
    conv_cfg.kernel_pad_l           = 1;
    conv_cfg.kernel_pad_r           = 1;
    conv_cfg.kernel_pad_t           = 1;
    conv_cfg.kernel_pad_b           = 1;
    conv_cfg.kernel_stride_h        = 1;
    conv_cfg.kernel_stride_w        = 1;
    conv_cfg.kernel_dilation_h      = 1;
    conv_cfg.kernel_dilation_w      = 1;
    conv_cfg.kernel_bias            = 1;
    conv_cfg.p_ifm                  = 0;
    conv_cfg.p_ofm                  = 0;
    conv_cfg.p_wt                   = pWT + 5250;
    conv_cfg.p_bs                   = pBS + 120;
            
    ActCFG act_cfg;
    act_cfg.input_n                 = 1;
    act_cfg.input_c                 = 20;
    act_cfg.input_h                 = 4;
    act_cfg.input_w                 = 4;
    act_cfg.type                    = 1;
    act_cfg.p_ifm                   = 0;
    act_cfg.p_ofm                   = 0;
            
	APICFG api_cfg;
	api_cfg.conv_cfg                = conv_cfg;
	api_cfg.act_cfg                 = act_cfg;
	api_cfg.input_n                 = 1;
    api_cfg.input_c                 = 20;
    api_cfg.input_h                 = 4;
    api_cfg.input_w                 = 4;
	api_cfg.output_n                = 1;
    api_cfg.output_c                = 20;
    api_cfg.output_h                = 4;
    api_cfg.output_w                = 4;
	api_cfg.ofm_shift               = -9;
    api_cfg.p_ifm                   = pFM + 2224;
    api_cfg.p_ofm                   = pFM + 2544;

	cpu_api_conv2d_relu(&api_cfg);
}


void run_0040_flatten()
{       
        
	APICFG api_cfg;
	api_cfg.input_n                 = 1;
    api_cfg.input_c                 = 20;
    api_cfg.input_h                 = 4;
    api_cfg.input_w                 = 4;
	api_cfg.output_n                = 1;
    api_cfg.output_c                = 320;
	api_cfg.ofm_shift               = 0;
    api_cfg.p_ifm                   = pFM + 2544;
    api_cfg.p_ofm                   = pFM + 2544;

	cpu_api_flatten(&api_cfg);
}


void run_0050_linear_relu()
{       
        
    ConvCFG conv_cfg;
    conv_cfg.input_n                = 1;
    conv_cfg.input_c                = 320;
    conv_cfg.input_h                = 1;
    conv_cfg.input_w                = 1;
    conv_cfg.output_n               = 1;
    conv_cfg.output_c               = 50;
    conv_cfg.output_h               = 1;
    conv_cfg.output_w               = 1;    
    conv_cfg.kernel_n               = 50;
    conv_cfg.kernel_c               = 320;
    conv_cfg.kernel_h               = 1;
    conv_cfg.kernel_w               = 1;
    conv_cfg.kernel_pad_l           = 0;
    conv_cfg.kernel_pad_r           = 0;
    conv_cfg.kernel_pad_t           = 0;
    conv_cfg.kernel_pad_b           = 0;
    conv_cfg.kernel_stride_h        = 1;
    conv_cfg.kernel_stride_w        = 1;
    conv_cfg.kernel_dilation_h      = 1;
    conv_cfg.kernel_dilation_w      = 1;
    conv_cfg.kernel_bias            = 1;
    conv_cfg.p_ifm                  = 0;
    conv_cfg.p_ofm                  = 0;
    conv_cfg.p_wt                   = pWT + 8850;
    conv_cfg.p_bs                   = pBS + 200;
        
    ActCFG act_cfg;
    act_cfg.input_n                 = 1;
    act_cfg.input_c                 = 50;
    act_cfg.input_h                 = 1;
    act_cfg.input_w                 = 1;
    act_cfg.type                    = 1;
    act_cfg.p_ifm                   = 0;
    act_cfg.p_ofm                   = 0;
            
	APICFG api_cfg;
	api_cfg.conv_cfg                = conv_cfg;
	api_cfg.act_cfg                 = act_cfg;
	api_cfg.input_n                 = 1;
    api_cfg.input_c                 = 320;
	api_cfg.output_n                = 1;
    api_cfg.output_c                = 50;
	api_cfg.ofm_shift               = -8;
    api_cfg.p_ifm                   = pFM + 2544;
    api_cfg.p_ofm                   = pFM + 2864;

	cpu_api_linear_relu(&api_cfg);
}


void run_0060_linear()
{       
        
    ConvCFG conv_cfg;
    conv_cfg.input_n                = 1;
    conv_cfg.input_c                = 50;
    conv_cfg.input_h                = 1;
    conv_cfg.input_w                = 1;
    conv_cfg.output_n               = 1;
    conv_cfg.output_c               = 10;
    conv_cfg.output_h               = 1;
    conv_cfg.output_w               = 1;    
    conv_cfg.kernel_n               = 10;
    conv_cfg.kernel_c               = 50;
    conv_cfg.kernel_h               = 1;
    conv_cfg.kernel_w               = 1;
    conv_cfg.kernel_pad_l           = 0;
    conv_cfg.kernel_pad_r           = 0;
    conv_cfg.kernel_pad_t           = 0;
    conv_cfg.kernel_pad_b           = 0;
    conv_cfg.kernel_stride_h        = 1;
    conv_cfg.kernel_stride_w        = 1;
    conv_cfg.kernel_dilation_h      = 1;
    conv_cfg.kernel_dilation_w      = 1;
    conv_cfg.kernel_bias            = 1;
    conv_cfg.p_ifm                  = 0;
    conv_cfg.p_ofm                  = 0;
    conv_cfg.p_wt                   = pWT + 24850;
    conv_cfg.p_bs                   = pBS + 400;
        
	APICFG api_cfg;
	api_cfg.conv_cfg                = conv_cfg;
	api_cfg.input_n                 = 1;
    api_cfg.input_c                 = 50;
	api_cfg.output_n                = 1;
    api_cfg.output_c                = 10;
	api_cfg.ofm_shift               = -10;
    api_cfg.p_ifm                   = pFM + 2864;
    api_cfg.p_ofm                   = pFM + 2914;

	cpu_api_linear(&api_cfg);
}


void run_0070_logsoftmax()
{       
        
    /*
    clf_type
    0   = None
    2   = logsoftmax
    */
    ClfCFG  clf_cfg;
    clf_cfg.input_n                 = 1;
    clf_cfg.input_c                 = 10;
    clf_cfg.type                    = 2;
    clf_cfg.p_ifm                   = pFM + 2914;
    clf_cfg.p_ofm                   = pOUT;
        
	APICFG api_cfg;
	api_cfg.clf_cfg                 = clf_cfg;
	api_cfg.input_n                 = 1;
    api_cfg.input_c                 = 10;
	api_cfg.output_n                = 1;
    api_cfg.output_c                = 10;
	api_cfg.ofm_shift               = 0;
    api_cfg.p_ifm                   = pFM + 2914;
    api_cfg.p_ofm                   = pFM + 2924;

	cpu_api_logsoftmax(&api_cfg);
}