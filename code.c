// LDR sensor pin assignments
const int ldr1 = A0;
const int ldr2 = A1;
const int ldr3 = A2;
const int ldr4 = A3;

// Headlight LED pin assignments
const int led1 = 3;
const int led2 = 5;

// Calibration Constants
int threshold = 800; // Trigger point for dimming
bool ledState = true; // High beam status (true = ON)

/**
 * Filters sensor noise by taking 5 consecutive samples.
 * This prevents the headlights from reacting to tiny sparks or light glitches.
 */
int readLDR(int pin) {
  int total = 0;
  for (int i = 0; i < 5; i++) {
    total += analogRead(pin);
    delay(3);
  }
  return total / 5;
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Capture smoothed readings from all 4 sensors
  int v1 = readLDR(ldr1);
  int v2 = readLDR(ldr2);
  int v3 = readLDR(ldr3);
  int v4 = readLDR(ldr4);

  // Compute the spatial average across the sensor array
  int avg = (v1 + v2 + v3 + v4) / 4;

  // Debugging output for Serial Plotter
  Serial.print("Sensor_Average: ");
  Serial.println(avg);

  /**
   * HYSTERESIS LOGIC:
   * Prevents "chatter" or rapid ON/OFF switching.
   * Headlights turn OFF only when avg > 850.
   * Headlights turn back ON only when avg < 750.
   */
  if (ledState && avg > threshold + 50) {
    ledState = false;   // Turn OFF (Oncoming glare detected)
  } 
  else if (!ledState && avg < threshold - 50) {
    ledState = true;    // Turn ON (Road is clear)
  }

  // Actuate Headlights
  digitalWrite(led1, ledState ? HIGH : LOW);
  digitalWrite(led2, ledState ? HIGH : LOW);

  delay(100);
}
