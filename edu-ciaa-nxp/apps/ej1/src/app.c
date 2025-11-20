/*
 * main.c
 * Created on: 15 nov. 2025
 * Author: na
 */
#include "sapi.h"

#define mainMAX_MSG_LEN 25

int main(void) {
	boardConfig();
	uartConfig(UART_USB, 9600);

	uartWriteString(UART_USB, "\r\n");
	uartWriteString(UART_USB, "=== Ejercicio 1 ===\r\n");

	// Macros de precompilador para fecha y hora
	uartWriteString(UART_USB, "=== Programa Compilado ");
	uartWriteString(UART_USB, __DATE__);
	uartWriteString(UART_USB, " ");
	uartWriteString(UART_USB, __TIME__);
	uartWriteString(UART_USB, " ===\r\n> ");

	uartWriteString(UART_USB, "Escribe algo (Backspace para borrar):\r\n> ");

	char cMessage[mainMAX_MSG_LEN];
	int messageIndex = 0;
	uint8_t receivedByte;

	while (true) {
		if (uartReadByte(UART_USB, &receivedByte)) {

			// Manejo de Borrado (0x08 o 0x7F)
			if (receivedByte == 0x08 || receivedByte == 0x7F) {
				if (messageIndex > 0) {
					messageIndex--;
					cMessage[messageIndex] = 0;

					uartWriteString(UART_USB, "\b \b");
				}
			}
			// Manejo de ENTER
			else if (receivedByte == '\r' || receivedByte == '\n') {
				if (messageIndex > 0) {
					cMessage[messageIndex] = '\0';
					uartWriteString(UART_USB, "\r\nEcho > ");
					uartWriteString(UART_USB, cMessage);
					messageIndex = 0;

					// Limpiar buffer
					for (int i = 0; i < mainMAX_MSG_LEN; i++) {
						cMessage[i] = 0;
					}
				}
			}
			// Caracteres ingresados
			else if (messageIndex < mainMAX_MSG_LEN - 1) {
				cMessage[messageIndex++] = receivedByte;
				uartWriteByte(UART_USB, receivedByte);
			}
			// Buffer lleno
			else {
				uartWriteString(UART_USB, "\r\nBuffer lleno! Enter para limpiar.\r\n> ");
				messageIndex = 0;
			}
		}
	}
}
