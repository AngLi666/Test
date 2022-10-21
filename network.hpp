#include "./api/def.h"
#include "./api/ultis.hpp"
#include "infer.hpp"
#include <cstring>




InputDataInfoT* p_input_data_info = getInputDataInfo();
OutputDataInfoT* p_output_data_info = getOutputDataInfo();


typedef struct prediction{
    int pred;
} PredictionT;



void runNetwork(PredictionT* prediction, float* inputFP32);

void loadWeights();

void preprocess(float* inputFP32);

void postprocess();

void predict(PredictionT* prediction);

void init_infer();

void close_infer();