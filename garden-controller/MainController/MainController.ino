#include "Scheduler.h"
#include "Task.h"
#include "ServoTask.h"

/* SENSORS */
int pinPhotoresistance = A0;
int pinTemperature = A1;

int LED0 = 3;
int LED1 = 4;
int LED2 = 5;
int LED3 = 6;

/* LOGICS */
int brightnessValue = 0;
int temperatureValue = 0;

Scheduler sched;


void setup() {
  Serial.begin(9600);
  pinMode(pinTemperature, INPUT);
  pinMode(pinPhotoresistance, INPUT);
  pinMode (LED0, OUTPUT);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);

  sched.init(10);
  Task* servoTask = new ServoTask(9);
  servoTask->init(40);

  sched.addTask(servoTask); 

}
 
void loop() {
  brightnessValue = analogRead(pinPhotoresistance);
  int brightnessMapped = (unsigned int) map(brightnessValue, 0, 1023, 1, 8);
  //Serial.print("sensor = " );
  //Serial.println(brightnessMapped);
  temperatureValue = analogRead(pinTemperature);
  float valueInVolt = temperatureValue*5/1023;  
  float valueInCelsius = valueInVolt/0.01;
  int temperatureMapped = (unsigned int) map(valueInCelsius, 0, 30, 1, 5);
  
  Serial.println(temperatureMapped);

  if (brightnessMapped < 5) {
    int fadeMapped = (unsigned int) map(brightnessMapped, 1, 5, 0, 4);
    
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    
    Serial.print("fade value = ");
    Serial.println(fadeMapped); 

    // set the fade of pins:
    analogWrite(LED0, fadeMapped);
    analogWrite(LED1, fadeMapped);
  } else if (brightnessMapped <= 2) {
     //Parte Servo Motore 
  } else {
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }

  // change the brightness for next time through the loop:
  //brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  //if (brightness <= 0 || brightness >= 255) {
    //fadeAmount = -fadeAmount;
  //}

  sched.schedule();
 
  delay(50);
}
