#include <avr/io.h>
#include <avr/interrupt.h> 
#include <avr/wdt.h>


/*
 * ATmega328P Microcontroller
 * This code initializes the serial communication and sends a message.
 * The watchdog timer is disabled to prevent resets during development.
 * The code is written in C and is intended for use with AVR-GCC.
*/

/*
    Function: initSerial
    Description: Initializes the serial communication with the specified baud rate.
    Input: 
    unsigned int baudrate: the desired baud rate for serial communication
    Output: there is no return value, but the serial communication will be initialized
            with the specified baud rate.
*/
void initSerial(baudrate) {
    UCSR0A = (1 << U2X0); // This one corresponds to U2Xn on the table. 0 for half speed, 1 for double speed, we prefer double speed since its more accurate.
    /*
    UBRR0L, same as UBRRn on the table, this is for setting the baud rate.
    Common values for double speed, 103 = 9600 baud rate, 51 = 19200 baud rate, 25 = 38400 baud rate, 16 = 57600 baud rate, 12 = 115200 baud rate.
    Common values for normal speed, 207 = 9600 baud rate, 103 = 19200 baud rate, 51 = 38400 baud rate, 34 = 57600 baud rate, 16 = 115200 baud rate.
    */
    UBRR0L = 16; 
    UBRR0H = 0; 
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
void serialWrite(unsigned char c) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}
void serialWriteString(const char * str) {
    while ( * str) {
        serialWrite( * str++);
    }
}

int main() {
    /*
    I am disabling the watchdog timer.
    the arduino in some cases wont work if the watchdog timer is enabled.
    this is seen when it flashes three times in quick succession.
    */
    wdt_disable();
    // Optional: Disable global interrupts for more precise timing if needed
    // cli();
    // Initialize the serial communication
    initSerial();
    serialWriteString("\r\nATMEGA328P Ready !!!\r\n");
    return 0; // End of the line
}