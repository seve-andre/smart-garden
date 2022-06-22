#include "ServoTask.h"
#include "Arduino.h"

bool firstTimerInit;
bool activeServo;
unsigned int contCycle;
unsigned int n_drink;
unsigned long tStop;
unsigned long tServo;

ServoTask::ServoTask(int pin) {
  pos = 0;
  pMotor = new ServoMotorImpl(pin);
  firstTimerInit = false;
  this->pMotor->on();  // attaches the servo on pin 9 to the servo object
  //beginningDrinkOut();
  tStop = millis();
  tServo = millis();
  startServoTo180 = true; 
  startServoTo0 = false; 
  activeServo = false;
}

void ServoTask::startServo() {
  if (!firstTimerInit) {
    pos = 0;
    firstTimerInit = true;
  }
  
  if (startServoTo180) {
    moveServoTo180();
  }
}

void ServoTask::moveServoTo180() {
  if (pos < 180 && activeServo) {
    activeServo = false;                       // tell servo to go to position in variable 'pos'
    noInterrupts();
    pos += 3;
    interrupts();
    pMotor->setPosition(pos);
    //delay(15);                                // waits 90ms for the servo to reach the position
  } else if(pos >= 180){
      startServoTo180 = false;
      startServoTo0 = true;  
  }
}

void ServoTask::tick() {
  startServo();
  stopServo();
  timerServo();
}


//Timer per fine rotazione a 180° di Servo
void ServoTask::stopServo() {  
  //Interrupt
  if ((millis() - tStop) >= 10000) {
      pMotor->off();
      tStop = millis();
      Serial.println("Tempo Finito");
  }
}


//Timer per tick di Servo
void ServoTask::timerServo() {  
  //Interrupt
  if ((millis() - tServo) >= 165) {
      Serial.println("active servo");
      tServo = millis();
      activeServo = true;
  }
}
