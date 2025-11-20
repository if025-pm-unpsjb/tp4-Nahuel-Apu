/*
 * main.c
 *
 *  Created on: 15 nov. 2025
 *  Author: na
 */

#include "app.h"         // <= Su propia cabecera (opcional)
#include "sapi.h"        // <= Biblioteca sAPI

// Array de LEDs - En la EDU-CIAA-NXP:
gpioMap_t leds[] = { CIAA_BOARD_LED, LED1, LED2, LED3 };

// Array de botones - En la EDU-CIAA-NXP:
gpioMap_t teclas[] = { TEC1, TEC2, TEC3, TEC4 };

int main(void) {
    // Inicializar la placa
    boardConfig();

    uartConfig(UART_USB, 9600);

    uartWriteString(UART_USB, "\r\n");
    uartWriteString(UART_USB, "=== Ejercicio 2 ===\r\n");

    // Macros de precompilador para fecha y hora
    uartWriteString(UART_USB, "=== Programa Compilado ");
    uartWriteString(UART_USB, __DATE__);
    uartWriteString(UART_USB, " ");
    uartWriteString(UART_USB, __TIME__);
    uartWriteString(UART_USB, " ===\r\n> ");

    // Configurar LEDs como salidas
    for (int i = 0; i < 4; i++) {
        gpioConfig(leds[i], GPIO_OUTPUT);
        gpioWrite(leds[i], OFF);
    }

    // Configurar botones como entradas con pull-up
    for (int i = 0; i < 4; i++) {
        gpioConfig(teclas[i], GPIO_INPUT_PULLUP);
    }

    // Variables para evitar repetición
    bool_t teclaPresionada[4] = { false, false, false, false };

    while (TRUE) {
        for (int i = 0; i < 4; i++) {
            if (gpioRead(teclas[i]) == LOW) {
                // Botón presionado
                if (!teclaPresionada[i]) {
                    // Toggle del LED - leer estado actual y cambiarlo
                    bool_t estadoActual = gpioRead(leds[i]);
                    gpioWrite(leds[i], !estadoActual);

                    // Imprimir ">BOTONX" donde X es el número
                    uartWriteString(UART_USB, "\r\n> BOTON");

                    // Convertir el número a carácter (1, 2, 3, 4)
                    char numChar = '1' + i;
                    uartWriteByte(UART_USB, numChar);

                    teclaPresionada[i] = true;
                }
            } else {
                // Botón liberado - resetear flag
                teclaPresionada[i] = false;
            }
        }
        delay(10);
    }

    return 0;
}
