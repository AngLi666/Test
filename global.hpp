
#include "def.hpp"
#include <stdlib.h>


#ifndef GLOBAL_HPP
#define GLOBAL_HPP


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


extern sint8_t* pFM;
extern sint8_t* pWT;
extern int* pBS;
extern float* pOUT;

extern InputDataInfoT input_data_info;
extern OutputDataInfoT output_data_info;


#endif