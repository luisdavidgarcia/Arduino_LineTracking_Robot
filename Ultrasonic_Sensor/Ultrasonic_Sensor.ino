int Trig = A5;
int Echo = A4;
int pingT = 0;

float distance_between_objects = 0, distance_sound = 0, velocity_sound = 0;

void setup() {
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  Serial.begin(9600);
}

void loop() {
  pingT = pingTime();
  //Serial.println(pingT);
  //delay(500);
  velocity_sound = 331.4 + 0.6*20.56;
  distance_sound = velocity_sound * pingT * .000001;
  distance_between_objects = 0.5 * distance_sound * 0.0254;
  Serial.println(distance_between_objects);
  delay(500);
}

int pingTime(){
  int pingTravelTime = 0;
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig,LOW);
  pingTravelTime = pulseIn(Echo,HIGH);
  return pingTravelTime;
}
