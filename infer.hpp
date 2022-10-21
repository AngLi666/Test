
#include "cpu_api.hpp"
#include "ultis.hpp"
#include <stdlib.h>

#ifndef infer_hpp
#define infer_hpp


typedef struct input_data_info_t{
    int             id;
    long            nSize;
    int             nChannel;
    int             nHeight;
    int             nWidth;
    float*          p_ifm_fp32;
    sint8_t*        p_ifm_int8;
} InputDataInfoT;


typedef struct output_data_info_t{
    int             id;
    long            nSize;
    int             nChannel;
    int             nHeight;
    int             nWidth;
    sint8_t*        p_ofm_int8;
    float*          p_ofm_fp32;
} OutputDataInfoT;


static sint8_t* pFM = (sint8_t*) malloc(2924);
static sint8_t* pWT = (sint8_t*) malloc(25350);
static int* pBS     = (int*) malloc(440);
static float* pOUT  = (float*) malloc(10 * sizeof(float));


InputDataInfoT input_data_info = {
    0,
    784,
    1,
    28,
    28,
    0,
    pFM
};

OutputDataInfoT output_data_info = {
    13,
    10,
    10,
    0,
    0,
    0,
    pOUT
};


InputDataInfoT getInputDataInfo();
OutputDataInfoT getOutputDataInfo();


void init();

void infer();
        

void run_0010_conv2d_relu_maxpool2d();

void run_0020_conv2d_relu_maxpool2d();

void run_0030_conv2d_relu();

void run_0040_flatten();

void run_0050_linear_relu();

void run_0060_linear();

void run_0070_logsoftmax();


#endif