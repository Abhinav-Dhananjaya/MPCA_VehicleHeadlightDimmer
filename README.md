# MPCA_VehicleHeadlightDimmer

An embedded system project designed to enhance road safety by automatically detecting oncoming high-beam glare and adjusting vehicle headlights to prevent driver distraction and accidents.

Automatic Vehicle Headlight Dimmer SystemCourse: Microprocessor & Computer Architecture (MPCA)

Student IDs: PES1UG24AM011 , PES1UG24AM012, PES1UG24AM032

Description :-

This project implements an intelligent lighting control system for vehicles. 
The primary goal is to mitigate the "glare effect" caused by high-beam headlights during night-time driving. By using a multi-sensor array, the system detects high-intensity light from oncoming traffic (simulated with a mobile flashlight) and automatically dims the vehicle's own headlights to ensure mutual road safety.

Features :-

Multi-Point Sensing: Uses a 4-photosensor configuration to cover a wide angular field of view.
Automated Response: Eliminates the need for manual high-beam switching.
Adaptive Logic: Distinguishes between ambient light and direct glare based on configurable thresholds
Safety Oriented: Prevents temporary blindness for oncoming drivers.

Hardware Specification :-

Processor: Atmel ATmega328P (Arduino Architecture)
Sensors: 4x Light Dependent Resistors (LDRs)
Indicators: 2x High-Lumen White LEDs (Headlight simulation)
Logic Type: Analog-to-Digital Conversion (ADC) with Comparator Logic
Input Voltage: 5V DC from laptop via RFID cable

Circuit Connection :-

Component                 Pin (Arduino/Microcontroller)             Description 
LDR 1                     Analog Pin A0                             Front-Left Sensor
LDR 2                     Analog Pin A1                             Front-Right Sensor 
LDR 3                     Analog Pin A2                             Offset-Left Sensor 
LDR 4                     Analog Pin A3                             Offset-Right Sensor 
LED 1                     Digital Pin 9                             Left Headlight
LED 2                     Digital Pin 10                            Right Headlight

Software Implementation :-

The system runs on a polling-based loop that monitors the ADC values from all four sensors simultaneously.
const int THRESHOLD = 700; 

void loop() {
    int s1 = analogRead(A0);
    int s2 = analogRead(A1);
    int s3 = analogRead(A2);
    int s4 = analogRead(A3);

    // If any sensor detects a flash, dim the lights
    if (s1 > THRESHOLD || s2 > THRESHOLD || s3 > THRESHOLD || s4 > THRESHOLD) {
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
    } else {
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
    }
}
