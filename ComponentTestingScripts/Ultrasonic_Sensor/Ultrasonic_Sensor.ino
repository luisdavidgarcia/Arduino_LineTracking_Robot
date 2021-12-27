int Trig = A5, Echo = A4;
float distance = 0;

void setup() {
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  Serial.begin(9600);
}

void loop() {
  distance = measureDistance();
  Serial.println(distance);
  delay(500);
}

float pingTime(){
  float pingTravelTime = 0;
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig,LOW);
  pingTravelTime = pulseIn(Echo,HIGH);
  return pingTravelTime;
}

float measureDistance(){
  float pingTravelTime = pingTime();
  float distance_sound = 0, distance_between_objects = 0;
  //speed of sound is 761 mi/hr
  distance_sound = ((761.0 * 63360.0 * pingTravelTime)/3600000000.0);
  distance_between_objects = 0.5*distance_sound;
  //distance is in inches
  return distance_between_objects;
}
