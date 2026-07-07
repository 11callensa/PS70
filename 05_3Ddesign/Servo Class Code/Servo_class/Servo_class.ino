# include <ESP32Servo.h>

Servo myservo;

class Sweeper 
{
  Servo servo;

  int pos;
  int increment;
  int updateInterval;

  unsigned long lastUpdate;

  public: 
    Sweeper (int interval)
    {
      updateInterval = interval;
      increment = 1;
    }

  void Attach (int pin)
  {
    servo.attach(pin);
  }

  void Detach (int pin)
  {
    servo.detach();
  }

  void Update()
  {
    if (millis() - lastUpdate > updateInterval)
    {
      lastUpdate = millis();
      pos += increment;

      servo.write(pos);
      
      Serial.println(pos);

      if ((pos >= 180) || (pos <= 0))
      {
        increment -= increment;
      }

    }
  }

};

Sweeper sweeper1(15);
Sweeper sweeper2(25)

void setup()
{
  Serial.begin(9600);
  sweeper1.Attach(D0);
  sweeper2.Attach(D1);
}

void loop()
{
  sweeper1.Update();
  sweeper2.Update();
}
