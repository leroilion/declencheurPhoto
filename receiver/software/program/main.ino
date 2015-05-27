#include <fft.h>

void setup() {
	Serial.begin(9600);
	Serial.println(F("START"));

	pinMode(13, OUTPUT);

	fft_init();
}

void loop() {
	if(fft_compute(FFT_K_4) > 700000000)
		digitalWrite(13, HIGH);
	else
		digitalWrite(13, LOW);
}