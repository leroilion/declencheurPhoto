#include <fft.h>
#include <DueTimer.h>
#include <sin_table.h>

volatile static FFTRingBuffer FFTbuffer;

void fft_init() {
	FFTbuffer.head = 0;
	Timer3.attachInterrupt(handlerTimerAnalogRead).setFrequency(FREQ_SAMPLE_RATE).start();
}

void fft_stop() {
	Timer3.stop();
}

void fft_start() {
	Timer3.start();
}

double fft_compute(uint8_t coef) {
	uint16_t buffer[SAMPLE_SIZE];
	unsigned long i;
	fft_stop();
	for (i = 0; i < SAMPLE_SIZE; ++i)
	{
		buffer[i] = FFTbuffer.buffer[(FFTbuffer.head+i) % SAMPLE_SIZE];
	}
	fft_start();

	double real = 0, img = 0;

	for (i = 0; i < SAMPLE_SIZE; ++i)
	{
		real += buffer[i] * cos_table(coef, i);
		img += buffer[i] * sin_table(coef, i);
	}

	return real * real + img * img;
}

void static handlerTimerAnalogRead()
{
	FFTbuffer.buffer[FFTbuffer.head] = analogRead(A0);
	FFTbuffer.head = (FFTbuffer. head + 1 ) % SAMPLE_SIZE;
}