#include <ESP32Servo.h>
    
// Set your pin variables
int switchPin = D0;
int switchServoPin = D6;
int lidServoPin = D5;

class Switch {
  private:
    int pin;

  public:
    Switch(int pin) {
      this->pin = pin;
      pinMode(this->pin, INPUT_PULLUP);
    }

    bool isOn() {
      return digitalRead(pin) == LOW;
    }
};

class UselessServo {
	private:
	Servo servo;

	int pos;
	int increment;
	int interval;
	unsigned long lastUpdate;

	int home;
	int target;

	public:
	UselessServo(int interval, int home, int target) {
		this->interval = interval;
		this->home = home;
    this->target = target;
		
    increment = -1;

    pos = home;

		// Set the pos instance variable to be home (notice no this-> because a constructor parameter doesn't have the same name)
	}

	void Attach(int pin) {
		servo.attach(pin);
		servo.write(pos);
	}

	void Detach() {
		servo.detach();
	}

  void toTarget() {

      if (millis() - lastUpdate >= interval && pos != target)
      {
          lastUpdate = millis();
          pos += increment;
          servo.write(pos);
      }

  }

	void returnHome() {

    if (millis() - lastUpdate >= interval && pos != home)
    {
        lastUpdate = millis();
        pos -= increment;
        servo.write(pos);
    }

  }
};

// Create a Switch object with the correct pin
// Create a UselessServo object for your switch servo. Set the interval to 2, home to 180, target to 0
// Create a UselessServo object for your lid servo. Set the interval to 1, home to 110, target to 0

UselessServo switchServo(2000, 100, 0);
UselessServo lidServo(1000, 110, 0);

Switch boxSwitch(switchPin);

void setup() {
	Serial.begin(9600);
	switchServo.Attach(switchServoPin);
	lidServo.Attach(lidServoPin);
}

void loop() {
  Serial.println(digitalRead(switchPin));

  if (boxSwitch.isOn()) {
    Serial.println("PRESSED");
    lidServo.toTarget();
    switchServo.toTarget();
  } 
  else {
    Serial.println("NOT PRESSED");
    lidServo.returnHome();
    switchServo.returnHome();
  }
}
