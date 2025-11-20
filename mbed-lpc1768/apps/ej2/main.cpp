#include "mbed.h"

PwmOut led1(LED1);
PwmOut led2(LED2);
PwmOut led3(LED3);
PwmOut led4(LED4);

// Función para brillo leds
void efecto(PwmOut &led, float duracion) {
    // Incrementar brillo (0% a 100%)
    for(float brillo = 0.0f; brillo <= 1.0f; brillo += 0.01f) {
        led.write(brillo);
        wait(duracion / 200.0f);
    }

    // Decrementar brillo (100% a 0%)
    for(float brillo = 1.0f; brillo >= 0.0f; brillo -= 0.01f) {
        led.write(brillo);
        wait(duracion / 200.0f);
    }
}

int main() {

    led1.period(0.01f);
    led2.period(0.01f);
    led3.period(0.01f);
    led4.period(0.01f);

    while(1) {

        efecto(led1, 3.0f);
        efecto(led2, 3.0f);
        efecto(led3, 3.0f);
        efecto(led4, 3.0f);
    }
}
