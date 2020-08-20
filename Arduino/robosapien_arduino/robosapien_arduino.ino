


#define RSTurnRight       0x80
#define RSRightArmUp      0x81
#define RSRightArmOut     0x82
#define RSTiltBodyRight   0x83
#define RSRightArmDown    0x84
#define RSRightArmIn      0x85
#define RSWalkForward     0x86
#define RSWalkBackward    0x87
#define RSTurnLeft        0x88
#define RSLeftArmUp       0x89
#define RSLeftArmOut      0x8A
#define RSTiltBodyLeft    0x8B
#define RSLeftArmDown     0x8C
#define RSLeftArmIn       0x8D
#define RSStop            0x8E
#define RSWakeUp          0xB1
#define RSBurp            0xC2
#define RSRightHandStrike 0xC0
#define RSNoOp            0xEF

#define BAUD 9600

 

const int irPin = 2;
const int tsDelay = 833; // us, as estimated

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(BAUD); // open the serial port at 9600 bps:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
   pinMode(irPin, OUTPUT);
  digitalWrite(irPin, HIGH); 
                        
}

void delayTs(unsigned int slices) {
  delayMicroseconds(tsDelay * slices); 
}


void writeCommand(int cmd) // this is type 'int' not 'roboCommand' due to an Arduino environment annoyance
{
  // preamble
  digitalWrite(irPin, LOW);
  delayTs(8);
    
  for(char b = 7; b>=0; b--) {
    digitalWrite(irPin, HIGH);
    delayTs( (cmd & 1<<b) ? 4 : 1 );
    digitalWrite(irPin, LOW);
    delayTs(1);        
  } 
  
  digitalWrite(irPin, HIGH);
}

// the loop function runs over and over again forever
void loop() {
/*
  if (Serial.available() > 0) {
    // read the incoming byte:
    byte incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  */
  delay(2000);                        
  writeCommand(RSBurp);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN,LOW);
  
}
