
program:
	g++ -g -w -DT_LINUX -fpermissive main.c fft.c -lm -lfftw3 -lrt -lpthread -lsndfile -o cwhorse
