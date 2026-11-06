// INTERRUPTS:
// NOTE NOT ALL PINS ON A MIRCO CONTROLLER ARE INTERRURPT PINS 
// SO CHECK THAT BEFORE ASSIGNING PINS

//FOR ESP32 S3 DEV BOARD
int led1 = 7;
int led2 = 4;
int btnPin = 5;
volatile int mode = 0; // "volatile" basically tells the CPU/Complier
//                        to Not optimize this away were're gonna
//                        use right away
volatile bool interruptTriggered = false;
unsigned long lastInterrupt = 0;
int delayTime = 500;

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  // This 'attachInterrupt()' below tells us were're gonna be using an
  // interrupt, it also takes in three arguements the pin,the
  // Interrupt function and how we want the interrupt
  // digitalPinToInterrupt() passes the pin to the Interrupt function
  attachInterrupt(digitalPinToInterrupt(btnPin), interruptHandler, FALLING);
}

void loop() {
  
  if (mode == 0) {
    pattern1();
  } else {
    pattern2();
  }

  if (interruptTriggered) {
    interruptTriggered = false;
    Serial.println("Interrupt Called");
  }
}

void pattern1() {
  digitalWrite(led1, HIGH);
  delay(1000);
  digitalWrite(led1, LOW);
  delay(1000);
}

void pattern2() {
  digitalWrite(led2, HIGH);
  delay(2000);
  digitalWrite(led2, LOW);
  delay(2000);
}

void interruptHandler() {// 
  if (millis() - lastInterrupt > delayTime) {// it debounces the button
    lastInterrupt = millis();
    interruptTriggered = true;
    mode++;
    mode %= 2;// important make sure we keep values of mode under 2 intergers
  }
}



/* MENT FOR ARDUINO UNO R3
int led1 = 3;
int led2 = 4;
int btnPin = 2;
volatile int mode = 0; // "volatile" basically tells the CPU/Complier
//                        to Not optimize this away were're gonna
//                        use right away
unsigned long lastInterrupt = 0;
int delayTime = 500;

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  // This 'attachInterrupt()' below tells us were're gonna be using an
  // interrupt, it also takes in three arguements the pin,the
  // Interrupt function and how we want the interrupt
  // digitalPinToInterrupt() passes the pin to the Interrupt function
  attachInterrupt(digitalPinToInterrupt(btnPin), interruptHandler, FALLING);
}

void loop() {
  
  if (mode == 0) {
    pattern1();
  } else {
    pattern2();
  }

  if (interruptTriggered) {
    interruptTriggered = false;
    Serial.println("Interrupt Called");
  }
}

void pattern1() {
  digitalWrite(led1, HIGH);
  delay(1000);
  digitalWrite(led1, LOW);
  delay(1000);
}

void pattern2() {
  digitalWrite(led2, HIGH);
  delay(2000);
  digitalWrite(led2, LOW);
  delay(2000);
}

void interruptHandler() {// 
  if (millis() - lastInterrupt > delayTime) {// it debounces the button
    lastInterrupt = millis();
    interruptTriggered = true;
    mode++;
    mode %= 2;// important make sure we keep values of mode under 2 intergers
  }
}
*/