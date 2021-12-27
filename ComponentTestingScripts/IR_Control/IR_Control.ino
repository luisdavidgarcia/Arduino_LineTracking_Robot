#include <IRremote.hpp>

int IRpin = 12;

//IR object to use IR
IRrecv IR(IRpin);
//Object to Process Data from IR
decode_results cmd;

void setup() {
  Serial.begin(9600);
  IR.enableIRIn();
  IR.blink13(true);
}

void loop() {

  while(IR.decode(&cmd) == 0){}

  Serial.println(cmd.value,HEX);
  
  delay(500);
  IR.resume();

  //if (cmd.value == FF){
  //  forward(1,1.2);
  //}

}
