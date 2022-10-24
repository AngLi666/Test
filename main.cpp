
// #pragma once
#include "ultis.hpp"
#include "network.hpp"
#include <iostream>


bool gFlagInfer     = true;
bool gKeepRunning   = false;

const int InputNSize = 784;
uint8_t inputData[InputNSize] = {0,};

void getInputDataFP32(float* inputDataFP32)
{
    // 1. read image

    // 2. norm
    uint8_t* pU8 = inputData;
    float* pF32 = inputDataFP32;
    for (int i = 0; i < InputNSize; ++i)
    {
        float t = (float) *pU8;
        t = t / 255.0;
        *pF32 = t;
        pU8 ++;
        pF32 ++;
    }
}

int main()
{

    init_infer();

    do {
        float inputDataFP32[InputNSize] = {0,};
        getInputDataFP32(inputDataFP32);
        PredictionT prediction;
        if (gFlagInfer){
            runNetwork(&prediction, inputDataFP32);
            gFlagInfer = false;
            std::cout << std::endl;
            std::cout << "Prediction = " << prediction.pred << std::endl;
            
            std::cout << "Input any key to finish:" << std::endl;
            std::system("pause");
        }
        stl_sleep(10);
    } while(gKeepRunning);

    close_infer();
}




// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ��������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б����ڲ鿴����
//   5. ת������Ŀ��>����������Դ����µĴ����ļ�����ת������Ŀ��>������������Խ����д����ļ����ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
