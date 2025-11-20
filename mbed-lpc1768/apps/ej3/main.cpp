#include "mbed.h"

Serial pc(USBTX, USBRX);

int main() {

    char buffer[100];
    int index = 0;

    while(1) {
        if(pc.readable()) {
            char caracter = pc.getc();

            if (caracter == '\r' || caracter == '\n') {
                if (index > 0) {
                    buffer[index] = '\0';
                    pc.printf("\r\nEco: %s\r\n", buffer);
                    index = 0;
                }
                pc.printf("> ");
            }

            else if (index < 99) {
                buffer[index++] = caracter;
                pc.putc(caracter);
            }
        }
    }
}
