/*
 * main.c
 *
 *  Created on: 16 nov. 2025
 *  Author: na
 */

#include "app.h"         // <= Su propia cabecera (opcional)
#include "sapi.h"        // <= Biblioteca sAPI

// Array de botones - En la EDU-CIAA-NXP:
gpioMap_t teclas[] = { TEC1, TEC2, TEC3, TEC4 };

// Estados globales - INICIALMENTE NINGUN COMPONENTE ACTIVO
bool_t componenteR = false;   // Todos eliminados inicialmente
bool_t componenteG = false;
bool_t componenteB = false;
bool_t ledEncendido = true;   // Pero LED encendido (mostrará blanco)

// Función para actualizar el LED basado en los estados
void actualizarLED() {
    if (ledEncendido) {
        // Si NO hay ningún componente activo, mostrar BLANCO
        if (!componenteR && !componenteG && !componenteB) {
            gpioWrite(LEDR, ON);
            gpioWrite(LEDG, ON);
            gpioWrite(LEDB, ON);
        } else {
            // Mostrar solo los componentes activos
            gpioWrite(LEDR, componenteR ? ON : OFF);
            gpioWrite(LEDG, componenteG ? ON : OFF);
            gpioWrite(LEDB, componenteB ? ON : OFF);
        }
    } else {
        // Apagar completamente el LED
        gpioWrite(LEDR, OFF);
        gpioWrite(LEDG, OFF);
        gpioWrite(LEDB, OFF);
    }
}

int main(void) {
    // Inicializar la placa
    boardConfig();

    uartConfig(UART_USB, 9600);

    uartWriteString(UART_USB, "\r\n");
    uartWriteString(UART_USB, "=== Ejercicio 3 ===\r\n");

    // Macros de precompilador para fecha y hora
    uartWriteString(UART_USB, "=== Programa Compilado ");
    uartWriteString(UART_USB, __DATE__);
    uartWriteString(UART_USB, " ");
    uartWriteString(UART_USB, __TIME__);
    uartWriteString(UART_USB, " ===\r\n> ");

    uartWriteString(UART_USB, "Estado inicial: LED RGB ENCENDIDO (BLANCO)\r\n");
    uartWriteString(UART_USB, "Use TEC1 = R, TEC 2 = G, TEC 3 = B\r\n");
    uartWriteString(UART_USB, "Use TEC4 para encender o apagar el LED RGB\r\n");

    // Configurar LED RGB como salidas - ACTIVE HIGH
    gpioConfig(LEDR, GPIO_OUTPUT);
    gpioConfig(LEDG, GPIO_OUTPUT);
    gpioConfig(LEDB, GPIO_OUTPUT);

    // Estado inicial: BLANCO (porque no hay componentes activos)
    actualizarLED();

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

                    uartWriteString(UART_USB, "\r\n> BOTON");
                    char numChar = '1' + i;
                    uartWriteByte(UART_USB, numChar);

                    switch(i) {
                        case 0: // TEC1 - Controlar componente ROJO
                            componenteR = !componenteR;
                            uartWriteString(UART_USB, " - ROJO ");
                            uartWriteString(UART_USB, componenteR ? "AGREGADO" : "ELIMINADO");
                            break;

                        case 1: // TEC2 - Controlar componente VERDE
                            componenteG = !componenteG;
                            uartWriteString(UART_USB, " - VERDE ");
                            uartWriteString(UART_USB, componenteG ? "AGREGADO" : "ELIMINADO");
                            break;

                        case 2: // TEC3 - Controlar componente AZUL
                            componenteB = !componenteB;
                            uartWriteString(UART_USB, " - AZUL ");
                            uartWriteString(UART_USB, componenteB ? "AGREGADO" : "ELIMINADO");
                            break;

                        case 3: // TEC4 - Prender/apagar LED RGB
                            ledEncendido = !ledEncendido;
                            uartWriteString(UART_USB, " - RGB ");
                            uartWriteString(UART_USB, ledEncendido ? "ENCENDIDO" : "APAGADO");
                            break;
                    }

                    // Mostrar estado actual de componentes
                    uartWriteString(UART_USB, " | Estado: R=");
                    uartWriteString(UART_USB, componenteR ? "1" : "0");
                    uartWriteString(UART_USB, " G=");
                    uartWriteString(UART_USB, componenteG ? "1" : "0");
                    uartWriteString(UART_USB, " B=");
                    uartWriteString(UART_USB, componenteB ? "1" : "0");

                    // Informar comportamiento especial
                    if (!componenteR && !componenteG && !componenteB) {
                        if (ledEncendido) {
                            uartWriteString(UART_USB, " [BLANCO - ningun componente activo]");
                        }
                    }

                    // Actualizar el LED físico
                    actualizarLED();

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
