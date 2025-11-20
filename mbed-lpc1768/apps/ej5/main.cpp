#include "mbed.h"

Serial pc(USBTX, USBRX);
DigitalOut leds[] = {LED1, LED2, LED3, LED4};

void mostrarNumeroBinario(int numero) {
    for(int i = 0; i < 4; i++) {
        leds[i] = (numero >> i) & 1;
    }
}

int main() {
    int contador = 0;
    int velocidad_ms = 250;  // 250 ms inicial
    char buffer[10];
    int bufIndex = 0;
    Timer temp;
    temp.start();

    pc.printf("Contador binario - Velocidad actual: %d ms\r\n", velocidad_ms);

    while(1) {
        if(pc.readable()) {
            char c = pc.getc();

            if(c == '\r' || c == '\n') {
                if(bufIndex > 0) {
                	// Convertir a entero
                    buffer[bufIndex] = '\0';
                    int nuevaVel = atoi(buffer);

                    if(nuevaVel >= 100 && nuevaVel <= 5000) {
                        velocidad_ms = nuevaVel;
                        pc.printf("\r\nNueva velocidad: %d ms\r\n", velocidad_ms);
                    } else {
                        pc.printf("\r\nError: Debe ser entre 100 y 5000 ms\r\n");
                    }
                    bufIndex = 0;
                }
            } else if(bufIndex < 9 && (c >= '0' && c <= '9')) {
                buffer[bufIndex++] = c;
                pc.putc(c);
            }
        }

        // Actualizar contador
        if(temp.read_ms() >= velocidad_ms) {
            mostrarNumeroBinario(contador);
            contador = (contador + 1) % 16;
            temp.reset();
        }
    }
}
