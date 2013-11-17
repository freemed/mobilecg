#include "notch.hpp"
#define GAIN   1.281701412e+00

float NotchIIR::filter(float newSample) {
	xv[0] = xv[1]; xv[1] = xv[2]; 
	xv[2] = newSample/GAIN;
	yv[0] = yv[1]; yv[1] = yv[2]; 

        yv[2] =   (xv[0] + xv[2]) -   1.6739566428 * xv[1]
                     + ( -0.5604258387 * yv[0]) + (  1.3060425992 * yv[1]);

	return yv[2];
}
