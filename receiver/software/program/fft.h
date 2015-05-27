#ifndef __FFT_H__
#define __FFT_H__
#include <inttypes.h>


#define SAMPLE_SIZE 256
#define FREQ_SAMPLE_RATE 100000

#define FFT_K_4 0 // F = 1562
#define FFT_K_8 1 // F = 3125
#define FFT_K_10 2 // F = 3906
#define FFT_K_13 3 // F = 5078
#define FFT_K_15 4 // F = 5859
#define FFT_K_18 5 // F = 7031

typedef struct FFTRingBuffer {
	uint16_t buffer[SAMPLE_SIZE];
	uint8_t head;
} FFTRingBuffer;

void fft_init();
void fft_stop();
void fft_start();
double fft_compute(uint8_t coef);
void static handlerTimerAnalogRead();

#endif