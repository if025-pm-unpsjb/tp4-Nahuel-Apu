#include "mbed.h"

Serial pc(USBTX, USBRX);
DigitalOut leds[] = {LED1, LED2, LED3, LED4};
int numLeds = 4;
int ledActivo = 0;

void parpadeo(int ledActivo) {
	// Ciclo de intermitencia de 250 ms
	leds[ledActivo] = 1;
	wait(0.25);
	leds[ledActivo] = 0;
	wait(0.25);
}

int main()
{

    while(1)
    {

        if(pc.readable()) {
            char input = pc.getc();
            pc.putc(input);
            pc.printf("\r\n");

            if(input >= '1' && input <= '4') {
                ledActivo = input - '1';
                pc.printf("Cambio a LED %d\r\n", ledActivo + 1);
            }
        }

        parpadeo(ledActivo);
    }
}
