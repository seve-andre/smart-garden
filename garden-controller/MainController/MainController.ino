/* SENSORS */
int pinPhotoresistance = A0;
int LED0 = 3;
int LED1 = 4;
int LED2 = 5;
int LED3 = 6;

/* LOGICS */
int brightnessValue = 0;


void setup() {
  Serial.begin(9600);
  pinMode(pinPhotoresistance, INPUT);
  pinMode (LED0, OUTPUT);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);

}
 
void loop() {
  brightnessValue = analogRead(pinPhotoresistance);
  int brightnessMapped = (unsigned int) map(brightnessValue, 0, 1023, 1, 9);
  Serial.print("sensor = " );
  Serial.println(brightnessMapped);

  if (brightnessMapped < 5) {
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);

    
  } else if (brightnessMapped <= 2) {
     //Parte Servo Motore 
  } else {
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
 
  delay(1000);
}
