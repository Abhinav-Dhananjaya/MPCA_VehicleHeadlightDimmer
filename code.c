#include <reg51.h> // Standard 8051 Header

// Define Headlight Pins
sbit Left_Headlight = P2^0;
sbit Right_Headlight = P2^1;

// Define Sensor Pins (Using P1.0 to P1.3)
// Note: In hardware, if using LDRs without an external ADC, 
// they are usually connected to an LM358 comparator first.
sbit Sensor1 = P1^0;
sbit Sensor2 = P1^1;
sbit Sensor3 = P1^2;
sbit Sensor4 = P1^3;

void delay(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++); // Approximation for 1ms at 11.0592 MHz
}

void main() {
    // Initialize Ports
    P1 = 0xFF; // Set Port 1 as Input
    P2 = 0x00; // Set Port 2 as Output (Initial state: OFF)

    while(1) {
        /* Logic: Sensors are Active High (Input = 1 when light is detected).
           If any sensor detects high-intensity light (OR Logic), 
           turn OFF the headlights.
        */
        if (Sensor1 == 1 || Sensor2 == 1 || Sensor3 == 1 || Sensor4 == 1) {
            // Glare detected: Switch to Low Beam (Headlights OFF)
            Left_Headlight = 0;
            Right_Headlight = 0;
        } 
        else {
            // No glare: Keep High Beam ON
            Left_Headlight = 1;
            Right_Headlight = 1;
        }
        
        delay(10); // Small stability delay
    }
}
