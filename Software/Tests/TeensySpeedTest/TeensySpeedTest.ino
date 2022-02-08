#ifndef TRUE
#define TRUE 1
#endif // !TRUE

#ifndef FALSE
#define FALSE 0
#endif // !FALSE

#ifndef NULL
#define NULL 0
#endif // !NULL

#ifdef VSCODE
#include <WProgram.h>
#endif

#include <TimeLib.h>

#include <avr/pgmspace.h>
#include <math.h>
#include <stdint.h>
#include <usb_serial.h>

#define TEST_PIN 14
#define PANEL_COUNT 6
#define NUM_CHAINS 3
#define CHAIN_PANEL_COUNT (PANEL_COUNT / NUM_CHAINS)
#define PANEL_WDITH 32
#define PANEL_HEIGHT 24
#define CHAIN_WIDTH (CHAIN_PANEL_COUNT * PANEL_WDITH * 3)
#define REPEATS 512

uint32_t lastTime = 0;
uint32_t value = 0;

void setup ()
{
	Serial.begin (115200);
	while (!Serial) {}

	pinMode (TEST_PIN, OUTPUT);
}

void loop ()
{
	uint32_t startTime = micros ();
	uint32_t tmp;

	for (uint32_t k = 0; k < REPEATS; k++)
	{
		for (uint32_t j = 0; j < PANEL_HEIGHT; j++)
		{
			for (uint32_t i = 0; i < CHAIN_WIDTH; i++)
			{
				tmp = value + i + j;
				digitalWriteFast (2, ((tmp + 0) & 0x01) != 0 ? HIGH : LOW);
				digitalWriteFast (3, ((tmp + 1) & 0x02) != 0 ? HIGH : LOW);
				digitalWriteFast (4, ((tmp + 2) & 0x04) != 0 ? HIGH : LOW);
#if NUM_CHAINS >= 2
				digitalWriteFast (5, ((tmp + 3) & 0x08) != 0 ? HIGH : LOW);
				digitalWriteFast (6, ((tmp + 4) & 0x10) != 0 ? HIGH : LOW);
				digitalWriteFast (7, ((tmp + 5) & 0x20) != 0 ? HIGH : LOW);
#endif
#if NUM_CHAINS >= 3
				digitalWriteFast (21, ((tmp + 3) & 0x08) != 0 ? HIGH : LOW);
				digitalWriteFast (22, ((tmp + 4) & 0x10) != 0 ? HIGH : LOW);
				digitalWriteFast (23, ((tmp + 5) & 0x20) != 0 ? HIGH : LOW);
#endif

				if (i >= CHAIN_WIDTH - PANEL_HEIGHT)
					digitalWriteFast (8, LOW);
				else
					digitalWriteFast (8, ((j >> (i - (CHAIN_WIDTH - PANEL_HEIGHT))) & 0x01) != 0 ? HIGH : LOW);

				digitalWriteFast (TEST_PIN, HIGH);
				delayNanoseconds (15); // Delay needs to be more than 15ns. Not sure how accurate this is for such a short delay, so this delay may actually be more
				digitalWriteFast (TEST_PIN, LOW);
				// Don't need to delay, as there will be enough other code before we set the pixel clock high again
			}
		}
	}

	uint32_t endTime = micros ();

	Serial.print ("Pixel clock: ");
	Serial.print ((1.0 / ((endTime - startTime) / (float)REPEATS)) * CHAIN_WIDTH * PANEL_HEIGHT);
	Serial.println ("MHz");
	Serial.print ("Update rate: ");
	Serial.print (1000000.0 / ((endTime - startTime) / (float)REPEATS));
	Serial.println ("Hz");

	Serial.print ("Single update time: ");
	Serial.print (1000 * ((endTime - startTime) / (float)REPEATS) / CHAIN_WIDTH / PANEL_HEIGHT);
	Serial.println ("ns");

	value++;
}
