#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>
#include "fft.h"

FILE *fp; //containing arecord process for sampling data from copy device
fftw_complex *in, *out; //fftw3 arrays: in contains data input to fourier transform, out is the forward fourier transform
fftw_plan p;
int fft_size;


void initialize_fft(int size){
	//initialize arrays
	fft_size = size;
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
	p = fftw_plan_dft_1d(size, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
}

	

void run_fft(float *output){
	int i;
	
	//copy intensity values to complex fftw array and perform windowing
	for (i=0;i<fft_size;i++) {
		float nOverNm1 = i/(1.0f*(fft_size - 1));

		float windowVal = 0.54 - (0.46*cos(2*M_PI*(i/((fft_size - 1)*1.0f)))); //hamming window
		//float windowVal = 0.5*(1 - cos(2*M_PI*(i/((fft_size - 1)*1.0f)))); //hanning window
		//float windowVal = 1 - 1.93*cos(2*M_PI*nOverNm1) + 1.29*cos(4*M_PI*nOverNm1) - 0.388*cos(6*M_PI*nOverNm1) + 0.028*cos(8*M_PI*nOverNm1);
		//float windowVal = 1;
		in[i][0] = output[i]*windowVal;
		in[i][1] = 0.0;
	}
		
	//Fast Fourier Transform:
	fftw_execute(p);

	//copy results to output array
	//up till number/2 due to nyquist tjafs
	for (i=0;i<fft_size/2;i++){
		output[i] = sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1]);
	}
	
}
