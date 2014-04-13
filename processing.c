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
//assumes pr(dot) == pr(dash) = 1/2
float P(TimingCoeff *timing, int stepsInCurrentState, int w, int x){
	//implement from page 30-36
	float p00 = P00(timing, stepsInCurrentState);
	float p01 = P01(timing, stepsInCurrentState);

	float pval = 0;
	if ((w == 0) && (x == 0)){
		pval = p00;
	} else if ((w == 0) && (x == 1)){
		pval = p01;
	} else if ((w == -1) && (x == 1)){
		pval = 1 - p01;
	} else if ((w == 1) && (x == 0)){
		pval = 1 - p00;
	}
	return pval;
}

//probability of w = 0 given x = 0
//"time" is time in current state (x = 0)
float P00(TimingCoeff *timing, int time){
	float retProp = 0;
	if ((time >= 0) && (time < (timing->T - timing->l))){
		retProb = 1.0f
	} else if ((time >= (timing->T - timing->l)) && (time < (timing->T + timing->l))){
		retProb = ((timing->T - time)/(2.0f*timing->l) + 1.0f/2.0f)*12.0f/17.0f + 5.0f/17.0f;
	} else if ((time >= (timing->T + timing->l)) && (time < (timing->Td - timing->d))){
		retProb = 1.0f;
	} else if ((time >= (timing->Td - timing->d)) && (time < (timing->Td + timing->d))){
		retProb = ((timing->Td - time)/(2.0f*timing->d) + 1.0f/2.0f)*4.0f/5.0f + 1.0f/5.0f;
	} else if ((time >= (timing->Td + timing->d)) && (time < 5*timing->T)){
		retProb = 1.0f;
	} else if (time >= 5*timing->T){
		exp(-(time - 5*timing->T)/(2.0f*timing->T));
	}
	return retProb;
}

//probability of w = 0 given x = 1
float P01(TimingCoeff *timing, int time){
	float retProp = 0;
	if ((time >= 0) && (time < (timing->T - timing->l))){
		retProp = 1.0f;
	} else if ((time >= (timing->T - timing->l)) && (time < (timing->T + timing->l))){
		retProb = (timing->T - time)/(4.0f*timing->l) + 3.0f/4.0f;
	} else if ((time >= (timing->T + timing->l)) && (time < (timing->Td - timing->d))){
		retProb = 1.0f;
	} else if ((time >= (timing->Td - timing->d)) && (time < (timing->Td + timing->d))){
		retProb = (timing->Td - time)/(2.0f*timing->d) + 1.0f/2.0f;
	} else if (time >= (timing->Td + timing->d)){
		retProb = 0;
	}
	return retProb;
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
void updateTiming(TimingCoeff *timing, float T){
	//page 37-38
	if (T < (3*timing->t1 + timing->t2)/2.0f){
		updateDotDuration(timing, T);
	} else {
		updateDashDuration(timing, T);
	}
}
void updateDashDuration(TimingCoeff *timing, float T){
	timing->kT += 1;
	timing->T += meanIncrement(timing->kT, timing->T, T);
}
void updateDotDuration(TimingCoeff *timing, float T){
	timing->kTd += 1;
	timing->Td += meanIncrement(timing->kTd, timing->Td, T);
}

//function for calculating increment in a mean update. oldVal is current mean, newVal is added value, samples is current amount of samples (including new value) 
float meanIncrement(int samples, float oldVal, float newVal){
	return (1.0f/(1.0f*samples)*(newVal - oldVal));
}

//update noise statistics
void updateNoiseVariance(NoiseStats *noiseStats, float z){
	//page 38-39
	noiseStats->k += 1;

	//update signal mean
	noiseStats->mu += meanIncrement(noiseStats->k, noiseStats->mu, z);

	//update "a" parameters
	if (z >= noiseStats->mu){
		noiseStats->a1 += meanIncrement(noiseStats->k, noiseStats->a1, z);
	} else {
		noiseStats->a2 += meanIncrement(noiseStats->k, noiseStats->a2, z);
	}
	noiseStats->a = noiseStats->a1 - noiseStats->a2;

	//update V parameter
	noiseStats->V += meanIncrement(noiseStats->k, noiseStats->V, (z - noiseStats->mu)*(z - noiseStats-mu));

	//finally, update R parameter
	noiseStats->R = noiseStats->V - noiseStats->a*noiseStats->a/4.0f;
}

//aner faen ikke hva det er
void smooth(){
	//FIXME??
	//page 39 og utover
}
