
// #pragma once
#include "ultis.hpp"
#include "network.hpp"
#include <iostream>


bool gFlagInfer     = true;
bool gKeepRunning   = false;

const int InputNSize = 784;
uint8_t inputData[InputNSize] = {0,};
void getInputDataFP32(float* inputFP32)
{
    // 1. read image

    // 2. norm
    for (int i = 0; i < InputNSize; ++i)
    {
        *(inputFP32+i) = *(inputData+i) / 255.0;
    }
}


int main()
{
    
    init_infer();
    do {
        float inputFP32[InputNSize] = {0,};
        getInputDataFP32(inputFP32);
        PredictionT prediction;
        if (gFlagInfer){
            runNetwork(&prediction, inputFP32);
            gFlagInfer = false;
            std::cout << std::endl;
            std::cout << "Prediction = " << prediction.pred << std::endl;

            char key;
            std::cin >> key;
        }
        stl_sleep(10);
    } while(gKeepRunning);

    close_infer();
}





