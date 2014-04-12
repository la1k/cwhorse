#include <stdio.h>

//update kalman coefficients
//R: noise variance
//Q: variance of w(k) 
//z: noisy, received morse signal
void updateKalman(KalmanCoeff *coeff, float R, float Q, float z){
	//update gain
	coeff->G = V_kpp/(V_kpp + R);

	//update estimation variance
	coeff->V_k = (1 - coeff->G)*V_kpp;
	
	//update prediction variance
	coeff->V_kpp = coeff->V_k + Q;

	//update estimation
	coeff->xhat_k = coeff->xhat_kpp + coeff->G*(z - xhat_kpp);

	//update prediction
	coeff->xhat_kpp = coeff->xhat_k;
}


//probabiliy of w given x and the time spent in the current state
float P(TimingCoeff *timing, int stepsInCurrentState, int w, int x){
	//implement from page 30-36
	//FIXME
}


//update variance of on-off-keying function w(k) 
//assume xhat has been properly thresholded?, {0, 1}
void updateVarianceW(float *Q, TimingCoeff *timing, float xhat){
	if (xhat == 1){
		*Q = P(timing, -1, 1) * P(timing, 0, 1); 
	} else if (xhat == 0){
		*Q = P(timing, 0, 0) * P(timing, 1, 0);
	} else {
		printf("xhat has not been properly thresholded, quittin' from updateQ()\n");
		exit(1);
	}
}

//character distribution estimation
void updateTimingCoeff(TimingCoeff *timing, float T){
	//implement from page 37-38


	//FIXME

	if (T > ){
	}

}

//update noise variance
void updateNoiseVariance(float *R){
	//implement from page 38-39
	//FIXME
}

//aner faen ikke hva det er
void smooth(){
	//FIXME??
	//page 39 og utover
}
