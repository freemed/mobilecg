/*
    This is an IIR base filter with an inappropriate cut frequency!
    Use this for testing purposes only!
*/


/**************************************************************
WinFilter version 0.8
http://www.winfilter.20m.com
akundert@hotmail.com

Filter type: High Pass
Filter model: Butterworth
Filter order: 2
Sampling Frequency: 5 KHz
Cut Frequency: 0.005000 KHz
Coefficents Quantization: float

Z domain Zeros
z = 1.000000 + j 0.000000
z = 1.000000 + j 0.000000

Z domain Poles
z = 0.995905 + j -0.004078
z = 0.995905 + j 0.004078
***************************************************************/

#include "baseline.hpp"

float BaselineIIR::filter(float NewSample) {
    float ACoef[NCoef+1] = {
        0.99616473386815951000,
        -1.99232946773631900000,
        0.99616473386815951000
    };

    float BCoef[NCoef+1] = {
        1.00000000000000000000,
        -1.99181039952515480000,
        0.99184379782263055000
    };

    int n;

    //shift the old samples
    for(n=NCoef; n>0; n--) {
       x[n] = x[n-1];
       y[n] = y[n-1];
    }

    //Calculate the new output
    x[0] = NewSample;
    y[0] = ACoef[0] * x[0];
    for(n=1; n<=NCoef; n++)
        y[0] += ACoef[n] * x[n] - BCoef[n] * y[n];
    
    return y[0];
}
