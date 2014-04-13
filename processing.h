//kalman filter coefficients
struct KalmanCoeff{
	float G; //gain
	float V_k; //estimation variance
	float V_kpp; //prediction variance
	float xhat_k; //estimation
	float xhat_kpp; //prediction
};

//timing coeffients, assume uniform probability density function
struct TimingCoeff{
	float t1; //shortest dot-duration expected
	float t2; //longest dot-duration expected


	//dot/element-space duration
	float T; //duration
	int kT; //number of samples in T estimate
	float l; //cut-off/deviation
	
	//dash/letter-space duration
	float Td; //duration
	int kTd; //number of samples in Td estimate
	float d; //cut-off/deviation
};


//noise statistics and associated values
struct NoiseStats{
	float R; //noise variance
	float V; 
	float mu; //mean value of received signal
	float a; //demodulated signal amplitude

	float a1;
	float a2;
	int k; //number of samples in means
};

//update kalman filter coefficients
void updateKalman(KalmanCoeff *coeff, float R, float Q, float z);

//find probability of state w given state x for steps
float P(TimingCoeff *timing, int stepsInCurrentState, int w, int x);

//probability of w = 0 given x = 0 for given time 
float P00(TimingCoeff *timing, int time);

//probability of w = 0 given x = 1 for a given time
float P01(TimingCoeff *timing, int time);

//update variance of w(k) using thresholded predicted x
void updateVarianceW(float *Q, TimingCoeff *timing, float xhat);

//update timing given a measured time of a state (either mark or space), will update either dash or dot duration based on the duration
void updateTiming(TimingCoeff *timing, float T);

//update durations of dash and dots with a new value
void updateDashDuration(TimingCoeff *timing, float T);
void updateDotDuration(TimingCoeff *timing, float T);

//convenience function for updating means incrementally 
float meanIncrement(int samples, float oldVal, float newVal);

//estimate variance of noise (and other intermediary values)
void updateNoiseVariance(NoiseStats *noiseStats, float z);
