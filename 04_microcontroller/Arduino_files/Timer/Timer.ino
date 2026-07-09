int potPin = A0;

int motorForward = D8;
int motorReverse = D6;

int buttonPin = D1;

bool running = false;
bool resetting = false;

bool lastButtonState = HIGH;

int potVal;
int timerVal;

int motorSpeed = 225;
int reverseSpeed = 225;

unsigned long startTime;
unsigned long resetTime = 0;

unsigned long forwardTime;
unsigned long reverseTime;

const int freq = 5000;
const int resolution = 8;

void setup() {

  Serial.begin(9600);

  pinMode(potPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(motorForward, OUTPUT);
  pinMode(motorReverse, OUTPUT);

  ledcAttach(motorForward, freq, resolution);
  ledcAttach(motorReverse, freq, resolution);

}


void loop() {

  int buttonState = digitalRead(buttonPin);


  // Button press starts a new cycle
  if (!running && !resetting && lastButtonState == HIGH && buttonState == LOW) {

    running = true;

    startTime = millis();

    potVal = analogRead(potPin);

    Serial.println(potVal);

    // Potentiometer sets timer: 1 second -> 60 seconds
    timerVal = map(potVal, 3, 4095, 1000, 60000);

    Serial.println(timerVal);

  }


  // -------------------------
  // Forward running phase
  // -------------------------

  if (running) {

    if (millis() - startTime < timerVal) {

      ledcWrite(motorForward, motorSpeed);
      ledcWrite(motorReverse, 0);

    }

    else {

      // Stop motor
      ledcWrite(motorForward, 0);
      ledcWrite(motorReverse, 0);


      // Record how long it moved forward
      forwardTime = millis() - startTime;


      // Calculate reverse time needed for same revolutions
      reverseTime = forwardTime * motorSpeed / reverseSpeed;


      running = false;

      resetting = true;

      resetTime = millis();

    }
  }

  if (resetting) {

    if (millis() - resetTime < 2000) {

      ledcWrite(motorForward, 0);
      ledcWrite(motorReverse, 0);

    }

    else if (millis() - resetTime < 2000 + reverseTime) {

      ledcWrite(motorForward, 0);
      ledcWrite(motorReverse, reverseSpeed);

    }

    else {

      ledcWrite(motorForward, 0);
      ledcWrite(motorReverse, 0);

      resetting = false;

    }

  }

  lastButtonState = buttonState;

}