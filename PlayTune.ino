/*
 * Play a Tune
 */

#include "PlayTune.h"
#include "tunes.h"

#include <MusicBox.h>

#include <LiquidCrystal.h>
#define PLAYPIN 15

LiquidCrystal Lcd(8,9,4,5,6,7);

MusicBox MusicPlayer;


/*
 * Read a button from the VMA203
 */
Button readButton()
{
   Button theButton=NullButton;
   int keyValue=analogRead(0);

   while(keyValue < 900)  // Do not read value on a button already pressed.
      keyValue=analogRead(0);
      
   while(theButton == NullButton) {
      keyValue=analogRead(0);
 
      if(keyValue < 64)
         theButton=Right;
      else if (keyValue < 128)
         theButton=Up;
      else if (keyValue < 300)
         theButton=Down;
      else if (keyValue < 500)
         theButton=Left;
      else if (keyValue < 900)
         theButton = Select;
   }
   
   return theButton;
}

/*
 * Wait for a button
 */
void waitForButton()
{
   int pressed=-1;
   int keyValue = analogRead(0);
   while(-1 == pressed)
   {
      keyValue=analogRead(0);
      if(keyValue < 900)
         pressed=0;
   }
}


/*
 * Main Line Setup
 */
void setup()
{
   Serial.begin(9600);
   Serial.println("Begin");
   Lcd.begin(1,2);
   MusicPlayer.begin(PLAYPIN);
   MusicPlayer.loadATune(StartSong,STARTSONG);
   MusicPlayer.loadATune(FailSong,FAILSONG);
   MusicPlayer.loadATune(SuccessSong,SUCCESSSONG);
}


/*
 * Main Line Loop
 */
void loop()
{
  Button theButton = readButton();
  switch(theButton) {
     case Up:
     case Select:
        MusicPlayer.playATune(SUCCESSSONG);
	break;
     case Down:
        MusicPlayer.playATune(FAILSONG);
        break;
     case Left:
        MusicPlayer.playATune(STARTSONG);
	break;
     default:  // Right
        MusicPlayer.playATune(-1);
	break;
  }
  
  theButton=NullButton;
}

