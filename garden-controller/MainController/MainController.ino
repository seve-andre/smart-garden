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
  int brightnessMapped = (unsigned int) map(brightnessValue, 0, 1023, 1, 8);
  Serial.print("sensor = " );
  Serial.println(brightnessMapped);
 
  delay(1000);
}
