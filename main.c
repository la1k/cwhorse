#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "fft.h"
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>




#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include "fft.h"

//number of samples in fft
#define N 256 




int main(int argc, char *argv[]){
	//TEMPORARY LIBSNDFILE TJAFS 
	SNDFILE *sf;
	SF_INFO info;
	int num_channels;
	int num, num_items;
	float *buf;
	int f,sr,c;
	int i,j;
	FILE *out;

	/* Open the WAV file. */
	info.format = 0;
	sf = sf_open(argv[1],SFM_READ,&info);
	if (sf == NULL)
	{
		printf("Failed to open the file.\n");
		exit(-1);
	}
	/* Print some of the info, and figure out how much data to read. */
	f = info.frames;
	sr = info.samplerate;
	c = info.channels;
	printf("frames=%d\n",f);
	printf("samplerate=%d\n",sr);
	printf("channels=%d\n",c);
	num_items = f*c;
	printf("num_items=%d\n",num_items);
	/* Allocate space for the data to be read, then read it. */
	buf = (float *) malloc(num_items*sizeof(float));
	num = sf_read_float(sf,buf,num_items);
	sf_close(sf);
	printf("Read %d items\n",num);
	/* Write the data to filedata.out. */
	out = fopen("filedata.out","w");


	//divide sound signal into slots, each of size N (corresponding to number of bins in the fft)
	int slots = num/N;
	if (c != 1){
		printf("Too many channels\n");
		return 1;
	
	}

	//do fft on sound signal, pick a frequency
	initialize_fft(N);
	int follfreq = 34;
	float *cwsignal = new float[slots];
	for (i = 0; i < slots; i++)
	{
		//run FFT
		float *arr = (float*)malloc(N*sizeof(float));
		memcpy(arr, buf + i*N, sizeof(float)*N);
		run_fft(arr, N);

		cwsignal[i] = arr[follfreq];
	}
	
	//FIXME: do test processing on the cw signal array as if it was in real-time


	fclose(out);
	return 0;
}

