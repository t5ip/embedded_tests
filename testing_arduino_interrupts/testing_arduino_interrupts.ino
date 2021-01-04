/* Using interrupts with Arduino Duemilanove 
 * Schematic: https://github.com/t5ip/electronics_testing/blob/main/NE555-Arduino_interrupt_source/NE555_Arduino_interrupt_source.sch
 */

/// Digital pins 2 and 3 support interrupts
int digitalPin = 2;
// https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
int interruptPin = digitalPinToInterrupt(digitalPin);
unsigned int uPreviousCounterValue;
unsigned long ulPreviousTime;
volatile unsigned int uCounter;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(interruptPin, INPUT);
  uCounter = 0;
  uPreviousCounterValue = 0;
  ulPreviousTime = 0;
  attachInterrupt(interruptPin, updateCounter, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long ulTimeNow = millis();
  unsigned long ulTimeSinceLast = ulTimeNow - ulPreviousTime;
  ulPreviousTime = ulTimeNow;
  
  unsigned int uCounterNow = uCounter;
  unsigned int uPulsesSinceLast = uCounterNow - uPreviousCounterValue;
  uPreviousCounterValue = uCounterNow;
  // Frequency in Hertz. Time in milliseconds.
  double dFrequency = 1000*((double) uPulsesSinceLast) / ((double) ulTimeSinceLast);
  Serial.println(dFrequency, DEC);
  delay(1000);
}

void updateCounter() {
  uCounter++;
}
