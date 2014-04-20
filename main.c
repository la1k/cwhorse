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
#include <bmorse.h>

#define N_FFT 256



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
	//fprintf(stderr, "frames=%d\n",f);
	fprintf(stderr, "samplerate=%d\n",sr);
	//fprintf(stderr, "channels=%d\n",c);
	num_items = f*c;
	//fprintf(stderr, "num_items=%d\n",num_items);
	/* Allocate space for the data to be read, then read it. */
	buf = (float *) malloc(num_items*sizeof(float));
	num = sf_read_float(sf,buf,num_items);
	sf_close(sf);
	//fprintf(stderr, "Read %d items\n",num);
	/* Write the data to filedata.out. */
	out = fopen("filedata.out","w");


	//divide sound signal into slots, each of size N (corresponding to number of bins in the fft)
	int slots = num/N_FFT;
	if (c != 1){
		printf("Too many channels\n");
		return 1;
	
	}

	//do fft on sound signal, pick a frequency
	initialize_fft(N_FFT);
	int follfreq = 32;
	float *cwsignal = new float[slots];

	bool printChars = false;
	morse *mp = new morse(); //bmorse decoder object
	static int init = 0;

	//parameters for bmorse
	float rn;
	long int retstat, imax, xhat, elmhat;
	float pmax, zout, spdhat, px;

	FILE *file;
	file = fopen("fftkis.dat", "w");

	for (i = 0; i < slots; i++)
	{
		//run FFT
		float *arr = (float*)malloc(N_FFT*sizeof(float));
		memcpy(arr, buf + i*N_FFT, sizeof(float)*N_FFT);
		run_fft(arr);

		for (int j = 0; j < N_FFT; j++){
			fprintf(file, "%f ", arr[j]);
		}
		fprintf(file, "\n");


		float x = arr[follfreq];
		mp->noise_(x, &rn, &zout);
		retstat = mp->proces_(&zout, &rn, &xhat, &px, &elmhat, &spdhat, &imax, &pmax);
		if (!printChars){
			printf("%f %d %d %d %d %f %f %f %f %f\n", x, (int)retstat, (int)imax, (int)elmhat, (int)xhat, px, pmax, spdhat, rn, zout);
		}	
	}
	fclose(file);
	
	//FIXME: do test processing on the cw signal array as if it was in real-time


	fclose(out);
	return 0;
}

