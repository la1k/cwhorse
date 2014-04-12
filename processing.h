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
	//dot/element-space duration
	float T; //duration
	int kT; //number of samples in T estimate
	float l; //cut-off/deviation
	
	//dash/letter-space duration
	float Td; //duration
	int kTd; //number of samples in Td estimate
	float d; //cut-off/deviation
};

void updateKalman(KalmanCoeff *coeff, float R, float Q);
