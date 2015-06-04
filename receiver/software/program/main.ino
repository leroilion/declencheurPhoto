#include <fft.h>

#define SIZE_TABLE 5
#define TIME_TO_WAIT 3000

// Table to compute average
double table[SIZE_TABLE];

void setup() {
	// Init serial link to debug
	// Serial.begin(9600);
	// Serial.println(F("START"));

	// Init IO
	pinMode(13, OUTPUT); // Debug LED
	pinMode(8, OUTPUT); // Control camera relay

	// Init table
	int i;
	for (i = 0; i < SIZE_TABLE; ++i)
	{
		table[i] = 1000000;
	}

	// Init TFD
	fft_init();
}

void loop() {
	static unsigned long time = 0;
	static unsigned int i = 0;

	// Save data in table to compute average
	table[i] = fft_compute(FFT_K_18);
	i++;
	i = i % SIZE_TABLE;

	// Compute sum of value
	double sum = 0;
	int j;
	for (j = 0; j < SIZE_TABLE; ++j)
	{
		sum += table[j];
	}

	// Whereas compare average, I compare SUM with more big value
	if (sum < 100000 * SIZE_TABLE)
	{
		digitalWrite(13, HIGH); // Switch on DEBUG LED
		digitalWrite(8, HIGH); // Switch on Relay to control camera
		time = millis();
	} else {
		digitalWrite(13, LOW);
	}

	if (millis() - time > TIME_TO_WAIT) {
		digitalWrite(8, LOW); // Stop the camera
	}
}
