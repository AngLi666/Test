// #pragma once
#include "network.hpp"
#include <cmath>

void runNetwork(PredictionT* prediction, float* inputFP32)
{

    preprocess(inputFP32);

    // tinyRaptorV2::load_data(destAddr, srcAddr, size);
    // std:: memcpy(ifm.int8_data, input->int8_data, inByte);
    infer();
    // tinyRaptorV2::dump_data(destAddr, srcAddr, size);
    // std:: memcpy(output->int8_data, ofm.int8_data, ouByte);

    postprocess();


    predict(prediction);

}


void preprocess(float* inputFP32)
{
    float*      p_fp32d = inputFP32;
    sint8_t*    p_int8d = input_data_info.p_ifm_int8;
    float       mean    = 0;
    float       rstd    = 128;
    float       temp    = 0;
    for (int i = 0; i < input_data_info.nSize; ++i)
    {
        temp = (*p_fp32d) * rstd;
        if (temp >127)
        {
            *p_int8d = 127;
        }
        else if (temp < -128)
        {
            *p_int8d = -128;
        }
        else{
            *p_int8d = std::round(temp);
        }
        p_fp32d++;
        p_int8d++;
    }

}


void postprocess()
{
    // ignore 2f, since using argmax
}


void predict(PredictionT* prediction)
{
    float*      p_val   = output_data_info.p_ofm_fp32;
    int         maxIDX  = 0;
    float       maxVal  = *p_val;

    for (int i = 0; i < output_data_info.nSize; ++i)
    {
        if (*p_val > maxVal){
            maxVal = *p_val;
            maxIDX = i;
        }
        p_val++;
    }
    prediction->pred = maxIDX;
}


void init_infer()
{
    const char wt_path[] = "E:\\Testv0\\wt.bin";
    const char bs_path[] = "E:\\Testv0\\bs.bin";

    load_bin(pWT, 25350, (char*)wt_path);
    load_bin(pBS, 440, (char*)bs_path);
}


void close_infer()
{
    // free memory
    free(pFM);
    free(pWT);
    free(pBS);
    free(pOUT);

    // others
}
