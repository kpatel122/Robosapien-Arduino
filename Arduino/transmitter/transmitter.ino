//Transmitter program
#include <ezButton.h>
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);
byte value;

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


typedef struct
{
  ezButton *button;
  byte valueToSend;
}TTransmitterButton;


#define BUTTON_DEBOUNCE_TIME 50

#define MAX_BUTTONS 14

TTransmitterButton buttons[MAX_BUTTONS];

void initButtons()
{


  buttons[0].button = new ezButton(2);
  buttons[0].valueToSend = 2;

  buttons[1].button = new ezButton(3);
  buttons[1].valueToSend = 3;

  buttons[2].button = new ezButton(4);
  buttons[2].valueToSend = 4;

  buttons[3].button = new ezButton(5);
  buttons[3].valueToSend = 5;

  buttons[4].button = new ezButton(6);
  buttons[4].valueToSend = 6;

  buttons[5].button = new ezButton(7);
  buttons[5].valueToSend = 7;

  buttons[6].button = new ezButton(8);
  buttons[6].valueToSend = 8;
  
  buttons[7].button = new ezButton(A0);
  buttons[7].valueToSend = 13;

  buttons[8].button = new ezButton(A1);
  buttons[8].valueToSend = 14;

  buttons[9].button = new ezButton(A2);
  buttons[9].valueToSend = 15;

  buttons[10].button = new ezButton(A3);
  buttons[10].valueToSend = 16;

  buttons[11].button = new ezButton(A4);
  buttons[11].valueToSend = 17;

  buttons[12].button = new ezButton(A5);
  buttons[12].valueToSend = 18;

  buttons[13].button = new ezButton(0);
  buttons[13].valueToSend = 0;

  
  for(int i=0;i<MAX_BUTTONS;i++)
  {
    buttons[i].button->setDebounceTime(BUTTON_DEBOUNCE_TIME);
  }
}

void updateButtons()
{
  for(int i=0;i<MAX_BUTTONS;i++)
  {
    buttons[i].button->loop();
  }
}

void sendRF(byte iValue)
{

  Mirf.send(&iValue);
  Serial.print("Wait for sending.....");
  while (Mirf.isSending())//Until you send successfully, exit the loop
  delay(1);        
  Serial.print("Send success:");
  Serial.println(value);
  
}

void processButtonPress()
{
  for(int i=0;i<MAX_BUTTONS;i++)
  {
    if(buttons[i].button->isPressed())
    {
      Serial.println(buttons[i].valueToSend);
      
      sendRF(buttons[i].valueToSend);
    }
     
    
  }
}


void initRF()
{
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (sender address) using 5 characters
  Mirf.setRADDR((byte *)"ABCDE");
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();
  Mirf.setTADDR((byte *)"FGHIJ");           //Set the receiver address
}

void setup()
{
  Serial.begin(BAUD);
  initRF();
  initButtons();
  
  
}

void loop()
{


  updateButtons();
  processButtonPress();
}
