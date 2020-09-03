#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);


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

#define BAUD 115200

byte value;

 

const int irPin = 2;
const int tsDelay = 833; // us, as estimated
byte incomingByte = 0;
 

void delayTs(unsigned int slices) {
  delayMicroseconds(tsDelay * slices); 
}

void initRFNano()
{
  
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"FGHIJ"); //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();
  Serial.println("Listening...");  //Start listening to received data
  
}

void writeCommand(int cmd)
{
  //digitalWrite(3, HIGH);
  //delay(5000);
  //digitalWrite(3, LOW);
 
  /*
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
  */
  
}

void processCommand(byte iCmd)
{
  iCmd = iCmd - '0'; // ascii to int

     Serial.print("cmd ");
    Serial.println(iCmd, DEC);
  switch(iCmd)
  {
    case 1:
    {
      Serial.println("Sending 1");
      writeCommand(0xC4);
    }break;
    case 2:
    {
      Serial.println("Sending 2");
      writeCommand(0xCC);
    }break;
    case 3:
    {
      Serial.println("Sending 3");
      writeCommand(0xC7);
    }break;
    case 4:
    {
      Serial.println("Sending 4");
      writeCommand(0xCE);
    }break;
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(BAUD); // open the serial port at 9600 bps:
   pinMode(LED_BUILTIN, OUTPUT);
   
  initRFNano();
                          
}

// the loop function runs over and over again forever
void loop() {

    if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData(&value);
    Serial.print("recg data: ");
    Serial.println(value);
  }
}
