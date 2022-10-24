#include "ultis.hpp"
#include "infer.hpp"
#include <cstring>



typedef struct prediction_t{
    int pred;
} PredictionT;



void runNetwork(PredictionT* prediction, float* inputFP32);

//void loadWeights();

void preprocess(float* inputFP32);

void postprocess();

void predict(PredictionT* prediction);

void init_infer();

void close_infer();


