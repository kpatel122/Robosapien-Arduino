//Transmitter program
#include <ezButton.h>
#include <SPI.h>
#include "commands.h"
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);
byte value;


#define BAUD 115200


typedef struct
{
  ezButton *button;
  byte valueToSend;
}TTransmitterButton;


#define BUTTON_DEBOUNCE_TIME 50

#define MAX_BUTTONS 14

TTransmitterButton buttons[MAX_BUTTONS];

#define MAX_RANDOM_COMMANDS 14
byte randomCommands[MAX_RANDOM_COMMANDS] = 
{ RSRightHandStrike1,  
  RSRightHandSweep, 
  RSBurp, 
  RSRightHandStrike2,
  RSHigh5,
  RSBulldozer,
  RSFart,
  RSWhistle,
  RSTalkback,
  RSRoar,
  RSAllDemo, 
  RSDemo1, 
  RSDemo2,
  RSDance
};

void initButtons()
{


  buttons[0].button = new ezButton(2);
  buttons[0].valueToSend = RSRightArmDown;//2;

  buttons[1].button = new ezButton(3);
  buttons[1].valueToSend = RSRightArmUp;//3;

  buttons[2].button = new ezButton(4);
  buttons[2].valueToSend = RSLeftArmIn;//4;

  buttons[3].button = new ezButton(5);
  buttons[3].valueToSend = RSTurnLeft;//5;

  buttons[4].button = new ezButton(6);
  buttons[4].valueToSend = RSStop;//6;

  buttons[5].button = new ezButton(7);
  buttons[5].valueToSend = RSLeftArmOut;//7;

  buttons[6].button = new ezButton(8);
  buttons[6].valueToSend = RSRightArmIn;//8;
  
  buttons[7].button = new ezButton(A0);
  buttons[7].valueToSend = RSLeftArmDown;//13;

  buttons[8].button = new ezButton(A1);
  buttons[8].valueToSend = RSRightArmOut;//14;

  buttons[9].button = new ezButton(A2);
  buttons[9].valueToSend = RSWalkBackward;//15;

  buttons[10].button = new ezButton(A3);
  buttons[10].valueToSend = RSRandom;//16;

  buttons[11].button = new ezButton(A4);
  buttons[11].valueToSend = RSLeftArmUp;//17;

  buttons[12].button = new ezButton(A5);
  buttons[12].valueToSend = RSWalkForward;//18;

  buttons[13].button = new ezButton(0);
  buttons[13].valueToSend = RSTurnRight; //0;

  
  for(int i=0;i<MAX_BUTTONS;i++)
  {
    buttons[i].button->setDebounceTime(BUTTON_DEBOUNCE_TIME);
  }
}

byte getRandomCommand()
{
  byte randNumber = (byte)random(0,MAX_RANDOM_COMMANDS);
  return randomCommands[randNumber];
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
      
      if(buttons[i].valueToSend == RSRandom)
      {
        byte cmd = getRandomCommand(); 
        Serial.println(cmd);
        sendRF(cmd);
      }
      else
      {
        sendRF(buttons[i].valueToSend);
        Serial.println(buttons[i].valueToSend);   
      }
      
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
  randomSeed(analogRead(A6)); 
  
}

void loop()
{


  updateButtons();
  processButtonPress();
}
