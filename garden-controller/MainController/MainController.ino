int pinPhotoresistance = A0;
int led0 = 3;
int led1 = 4;
int led2 = 5;
int led3 = 6;

int brightnessValue = 0;


void setup() {
  Serial.begin(9600);
  pinMode(pinPhotoresistance, INPUT);
  pinMode (led0, OUTPUT);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);

}
 
void loop() {
  brightnessValue = analogRead(pinPhotoresistance);
  Serial.print("sensor = " );
  Serial.println(brightnessValue);
 
  delay(1000);
}
