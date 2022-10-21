
#include "global.hpp"


sint8_t* pFM = (sint8_t*) malloc(2924);
sint8_t* pWT = (sint8_t*) malloc(25350);
int* pBS     = (int*) malloc(440);
float* pOUT  = (float*) malloc(10 * sizeof(float));


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

