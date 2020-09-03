//Transmitter program
#include <ezButton.h>
#include <SPI.h>
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

#define MAX_BUTTONS 2
#define BUTTON_DEBOUNCE_TIME 10
 
TTransmitterButton buttons[MAX_BUTTONS];

void initButtons()
{
  buttons[0].button = new ezButton(2);
  buttons[0].valueToSend = 0xC7;
  
  buttons[1].button = new ezButton(3);
  buttons[1].valueToSend = 3;
  
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
      
      Serial.print("button Sending ");
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
