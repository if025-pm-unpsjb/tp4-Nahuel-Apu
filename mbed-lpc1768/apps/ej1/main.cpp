#include "mbed.h"

DigitalOut leds[] = {LED1, LED2, LED3, LED4};
int numLeds = 4;

void mostrarNumeroBinario(int numero) {
    for(int i = 0; i < numLeds; i++) {
        leds[i] = (numero >> i) & 1;
    }
}

int main() {
    int contador = 0;

    while(1) {
        mostrarNumeroBinario(contador);

        contador = (contador + 1) % 16;

        wait(1.0);
    }
}
