/*
 * Play a Tune
 */

#include "PlayTune.h"

#include "pitches.h"
#include <LiquidCrystal.h>

LiquidCrystal Lcd(8,9,4,5,6,7);
note SuccessSong[] =  {
{NOTE_F4,   8},{NOTE_E4,  16},{NOTE_D4,   8},{NOTE_CS4,  16},
{NOTE_C4,   8},{NOTE_B3,  16},{NOTE_AS3,   8},{NOTE_A3,  16},
{NOTE_G3,  16},{NOTE_A3,  16},{NOTE_AS3,  16},{NOTE_A3,   8},
{NOTE_G3,  16},{NOTE_C4,   8},{0,   3,},{NOTE_C4,  12},
{NOTE_A3,  16},{NOTE_A3,  16},{NOTE_A3,  16},{NOTE_GS3,   8},
{NOTE_A3,  16},{NOTE_F4,   8},{NOTE_C4,  16},{NOTE_C4,   8},
{NOTE_A3,  16},{NOTE_AS3,   8},{NOTE_AS3,  16},{NOTE_AS3,   8},
{NOTE_C4,  16},{NOTE_D4,  4},{0,    12},{NOTE_AS3,  12},
{NOTE_G3,  16},{NOTE_G3,  16},{NOTE_G3,  16},{NOTE_FS3,   8},
{NOTE_G3,  16},{NOTE_E4,   8},{NOTE_D4,  16},{NOTE_D4,   8},
{NOTE_AS3,  16},{NOTE_A3,   8},{NOTE_A3,  16},{NOTE_A3,   8},
{NOTE_AS3,  16},{NOTE_C4,  4},{0,  12},{NOTE_C4,  12},
{NOTE_A3,  16},{NOTE_A3,  16},{NOTE_A3,  16},{NOTE_GS3,   8},
{NOTE_A3,  16},{NOTE_A4,   8},{NOTE_F4,  16},{NOTE_F4,   8},
{NOTE_C4,  16},{NOTE_B3,   8},{NOTE_G4,  16},{NOTE_G4,   8},
{NOTE_G4,  16},{NOTE_G4,  4},{0,  16},{NOTE_G4,  12},
{NOTE_E4,  17},{NOTE_G4,  17},{NOTE_G4,  17},{NOTE_FS4,   8},
{NOTE_G4,  12},{NOTE_D4,  17},{NOTE_G4,  17}, {NOTE_G4,  17},
{NOTE_FS4,   8},{NOTE_G4,  16},{NOTE_C4,   8},{ NOTE_B3,  16},
{NOTE_C4,   8},{NOTE_B3,  16},{NOTE_C4,   8},{0,1},
{-1,-1}
};


// Shave and a Hair Cut...
note ShaveandHaircutSong[] =
{
  {NOTE_C4,4},  {NOTE_G3,8},  {NOTE_G3,8},  {NOTE_A3,4},
  {NOTE_G3,4},  {0,4},  {NOTE_B3,4},  {NOTE_C4,4},
  {-1,-1}
};

note StartSong[] = {
  {NOTE_C4,8},  {NOTE_D4,8},  {NOTE_E4,8},  {NOTE_G4,8},
  {0,8},  {NOTE_E4,8},  {NOTE_G4,4},  {-1,-1}
};


note FailSong[] = {
   {NOTE_C6,4},   {NOTE_B5,4},   {NOTE_A5,4},   {NOTE_G5,4},
   {NOTE_C4,2},
   {-1,-1}
};


#define PLAYPIN 15


note *NotePtr = StartSong;


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

void playATune(note *theTune)
{
  int thePause;
  
   while(theTune->duration != -1) {
     tone(PLAYPIN,theTune->pitch,(unsigned long)(1000/(theTune->duration)));
     delay(( (1000/(theTune->duration)) * 1.30));
     ++theTune;
   }
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
   pinMode(PLAYPIN,OUTPUT);
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
        playATune(SuccessSong);
	break;
     case Down:
        playATune(FailSong);
        break;
     case Left:
        playATune(StartSong);
	break;
     default:  // Right
        playATune(ShaveandHaircutSong);
	break;
  }
  theButton=NullButton;
}

